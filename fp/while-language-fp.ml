module Str = struct
  let implode l =
    let s = String.make (List.length l) ' ' in
    let rec go i = function
      | [] -> s
      | h::t -> s.[i] <- h; go (i+1) t
    in
    go 0 l

  let explode s =
    let rec go acc i =
      if i = String.length s then
        List.rev acc
      else
        go (s.[i]::acc) (i+1)
    in
    go [] 0
end

module LazyList = struct
  type 'a node = Nil  | Cons of 'a * 'a t and 'a t = 'a node Lazy.t
  let empty = lazy Nil
  let singleton x = lazy (Cons (x, empty))
  let cons h t = lazy (Cons (h, t))
  let force = Lazy.force
  let rec map f l = lazy (
    match force l with
    | Nil -> Nil
    | Cons (h, t) -> Cons (f h, map f t)
    )
  let rec append l1 l2 = lazy (
    match force l1 with
    | Nil -> force l2
    | Cons (h, t) -> Cons (h, append t l2)
    )
  let rec concat ll = lazy (
    match force ll with
    | Nil -> Nil
    | Cons (h, t) -> append h (concat t) |> force
    )
  let is_empty l =
    match force l with
    | Nil -> true
    | Cons _ -> false
end

module ParserCombinators = struct
  type input = { s: string; pos: int }
  type 'a t = input -> ('a * input) LazyList.node Lazy.t

  let unit x s = LazyList.singleton (x, s)
  let zero = unit []
  let (>>=) (type a) (type b) (x : a t) (f : a -> b t) s = LazyList.map (fun (a,s') -> f a s') (x s) |> LazyList.concat
  let (>>) x y = x >>= fun _ -> y
  let (<<) x y = x >>= fun b -> y >> unit b
  let (<|>) x y s = let r = x s in if LazyList.is_empty r then y s else r
  let fail s = LazyList.empty
  let (<$>) f x = x >>= fun b -> unit (f b)
  let (<$) b x = x >> unit b
  let (<*>) f x = f >>= fun g -> x >>= fun b -> unit (g b)
  let (<**>) x f = x >>= fun b -> f >>= fun g -> unit (g b)

  let rec many x =
    let go = x >>= fun b ->
      many x >>= fun bs ->
      unit (b::bs)
    in
    go <|> zero

  let many1 x =
    x >>= fun b ->
    many x >>= fun bs ->
    unit (b::bs)

  let next s =
    if s.pos = String.length s.s then
      None
    else
      Some (s.s.[s.pos], { s with pos = s.pos + 1 })

  let pred f = (fun s -> match next s with
    | None -> LazyList.empty
    | Some x -> LazyList.singleton x) >>= fun b ->
        if f b then unit b else fail

  let char c = pred (fun c' -> c = c')
  let str s =
    let rec go = function
      | [] -> zero
      | h::t -> char h >>= fun b -> go t >>= fun bs -> unit (b::bs)
    in
    Str.explode s |> go
  let digit = pred (fun c -> '0' <= c && c <= '9')
  let lower = pred (fun c -> 'a' <= c && c <= 'z')
  let drop x = x >> zero
  let space = pred (fun c -> c = ' ' || c = '\t' || c = '\r' || c = '\n')
  let token x = x << drop (many space)
  let char_ c = char c |> token
  let str_ s = str s |> token

  let sep_by x sep =
    let go = x >>= fun b ->
      many (drop sep >> x) >>= fun bs ->
      unit (b::bs)
    in
    go <|> zero

  let chainl1 x op =
    let rec go a =
      (op >>= fun f ->
      x >>= fun b ->
      go (f a b)) <|> unit a
    in
    x >>= go

  let parse x s =
    match LazyList.force ((drop (many space) >> x) { s; pos = 0 }) with
    | LazyList.Nil -> None
    | LazyList.Cons ((x, _), _) -> Some x
end

type aexpr =
  | Num of int64
  | Var of string
  | Add of aexpr * aexpr
  | Sub of aexpr * aexpr
  | Mul of aexpr * aexpr
  | Div of aexpr * aexpr

type bexpr =
  | Bool of bool
  | Not of bexpr
  | And of bexpr * bexpr
  | Or of bexpr * bexpr
  | Lt of aexpr * aexpr
  | Gt of aexpr * aexpr

type stmt =
  | Chain of stmt list
  | Assign of string * aexpr
  | If of bexpr * stmt * stmt
  | While of bexpr * stmt

module Parser = struct
  include ParserCombinators

  let add x y = Add (x,y)
  let sub x y = Sub (x,y)
  let mul x y = Mul (x,y)
  let div x y = Div (x,y)
  let num l = Num (Str.implode l |> Int64.of_string)
  let var l = Var (Str.implode l)
  let chain xs = Chain xs
  let if_ b t e = If (b,t,e)
  let while_ b t = While (b,t)
  let assign x y = Assign (x,y)
  let and_ x y = And (x,y)
  let or_ x y = Or (x,y)
  let lt x y = Lt (x,y)
  let gt x y = Gt (x,y)

  let rec aexpr =
    let rec e0 = lazy ((num <$> token (many1 digit)) <|> (var <$> token (many1 lower)) <|> (fun s -> (char_ '(' >> Lazy.force e2 << char_ ')') s))
    and e1 = lazy (chainl1 (Lazy.force e0) ((mul <$ char_ '*') <|> (div <$ char_ '/')))
    and e2 = lazy (chainl1 (Lazy.force e1) ((add <$ char_ '+') <|> (sub <$ char_ '-')))
    in
    Lazy.force e2

  let rec bexpr =
    let rec e0 = lazy ((Bool false <$ str_ "false") <|> (Bool true <$ str_ "true") <|>
      (fun s -> (char_ '(' >> Lazy.force e3 << char_ ')') s)
      )
    and e1 = lazy ((aexpr <**> ((lt <$ char_ '<') <|> (gt <$ char_ '>')) <*> aexpr) <|> Lazy.force e0)
    and e2 = lazy (chainl1 (Lazy.force e1) ((and_ <$ str_ "and")))
    and e3 = lazy (chainl1 (Lazy.force e2) ((or_ <$ str_ "or")))
    in
    Lazy.force e3

  let rec stmt =
    let rec sassign = lazy (Str.implode <$> token (many1 lower) <**> (assign <$ str_ ":=") <*> aexpr)
    and sif = lazy ((if_ <$ str_ "if") <*> bexpr << str_ "then" <*> Lazy.force sb << str_ "else" <*> Lazy.force sb)
    and sb = lazy (char_ '{' >> (fun s -> Lazy.force s1 s) << char_ '}')
    and swhile = lazy ((while_ <$ str_ "while") <*> bexpr << str_ "do" <*> Lazy.force sb)
    and s0 = lazy (Lazy.force sif <|> Lazy.force swhile <|> Lazy.force sb <|> Lazy.force sassign)
    and s1 = lazy (chain <$> sep_by (Lazy.force s0) (char_ ';'))
    in
    Lazy.force s1
end

module Eval = struct
  type store = (string, int64) Hashtbl.t
  type 'a t = store -> 'a

  let unit a s = a
  let (>>=) x f s = f (x s) s
  let (>>) x y = x >>= fun _ -> y
  let (<$>) f x s = x s |> f
  let rec map_ f = function
    | [] -> unit ()
    | h::t -> f h >> map_ f t
  let liftM2 f x y s =
    let x' = x s in
    let y' = y s in
    f x' y'

  let rec eval_a = function
    | Num n -> unit n
    | Var v -> fun tbl -> Hashtbl.find tbl v
    | Add (x,y) -> liftM2 Int64.add (eval_a x) (eval_a y)
    | Sub (x,y) -> liftM2 Int64.sub (eval_a x) (eval_a y)
    | Mul (x,y) -> liftM2 Int64.mul (eval_a x) (eval_a y)
    | Div (x,y) -> liftM2 Int64.div (eval_a x) (eval_a y)

  let rec eval_b = function
    | Bool b -> unit b
    | Not x -> not <$> eval_b x
    | And (x,y) -> liftM2 (&&) (eval_b x) (eval_b y)
    | Or (x,y) -> liftM2 (||) (eval_b x) (eval_b y)
    | Lt (x,y) -> liftM2 (<) (eval_a x) (eval_a y)
    | Gt (x,y) -> liftM2 (>) (eval_a x) (eval_a y)

  let rec eval_s = function
    | Assign (v,x) -> fun tbl -> Hashtbl.replace tbl v (eval_a x tbl)
    | Chain xs -> map_ eval_s xs
    | If (b,t,e) -> eval_b b >>= fun b' -> eval_s (if b' then t else e)
    | While (b,t) as w -> eval_b b >>= fun b' -> if b' then eval_s t >> eval_s w else unit ()

  let interpret ast =
    let tbl = Hashtbl.create 13 in
    eval_s ast tbl;
    Hashtbl.fold (fun k v xs -> (k,v)::xs) tbl [] |> List.sort compare |> List.iter (fun (k,v) ->
      Printf.printf "%s %Ld\n" k v
    )
end

let read _ =
  let rec go acc =
    try
      let s = read_line () in
      go (s::acc)
    with End_of_file ->
      String.concat "\n" (List.rev acc)
  in
  go []

let () =
  match Parser.parse Parser.stmt (read 0) with
  | None -> ()
  | Some ast -> Eval.interpret ast
