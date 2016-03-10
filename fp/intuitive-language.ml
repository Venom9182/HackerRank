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
  let alnum = pred (fun c -> 'a' <= c && c <= 'z' || '0' <= c && c <= '9')
  let drop x = x >> zero
  let space = pred (fun c -> c = ' ' || c = '\t' || c = '\r' || c = '\n')
  let ident = lower >>= fun a -> many alnum >>= fun b -> unit (a::b)

  let token x = x << drop (many space)
  let char_ c = char c |> token
  let str_ s = str s |> token
  let ident_ = token ident

  let (>>::) x y =
    x >>= fun a ->
    y >>= fun b ->
    unit (a::b)

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

  let rec chainr1 x op =
    let go a =
      (op >>= fun f ->
      chainr1 x op >>= fun b ->
      unit (f a b)) <|> unit a
    in
    x >>= go

  let parse x s =
    match LazyList.force ((drop (many space) >> x) { s; pos = 0 }) with
    | LazyList.Nil -> None
    | LazyList.Cons ((x, _), _) -> Some x
end

module R = struct
  type t = R of int64 * int64
  let rec gcd a b =
    if b = 0L then
      Int64.abs a
    else
      gcd b (Int64.rem a b)
  let r a b =
    let d = gcd a b in
    let d = if b < 0L then Int64.neg d else d in
    R (Int64.div a d, Int64.div b d)
  let add (R (a,b)) (R (c,d)) = r Int64.(add (mul a d) (mul b c)) Int64.(mul b d)
  let sub (R (a,b)) (R (c,d)) = r Int64.(sub (mul a d) (mul b c)) Int64.(mul b d)
  let mul (R (a,b)) (R (c,d)) = r Int64.(mul a c) Int64.(mul b d)
  let div (R (a,b)) (R (c,d)) = r Int64.(mul a d) Int64.(mul b c)
  let print (R (a,b)) =
    if b = 1L then
      Printf.printf "%Ld" a
    else
      Printf.printf "%Ld/%Ld" a b
end

type value =
  | Value of R.t
  | Fun of R.t list

type expr =
  | Num of int64
  | Var of string
  | Apply of expr * expr
  | Mul of expr * expr
  | Div of expr * expr
  | Add of expr * expr
  | Sub of expr * expr

type stmt =
  | Assign of assign_chain
  | Do of expr * stmt
  | What of what_chain
  | Define of string * expr list
and assign_chain =
  | Assign_single of string * expr
  | Assign_chain of assign_chain * assign_chain
and what_chain =
  | What_single of expr
  | What_chain of what_chain * what_chain

module Parser = struct
  include ParserCombinators

  let num x = Num x
  let is v e = Assign (Assign_single (v,e))
  let add x y = Add (x,y)
  let sub x y = Sub (x,y)
  let mul x y = Mul (x,y)
  let div x y = Div (x,y)
  let single x y = y,x
  let do_ x y = Do (x,y)
  let assign x = Assign x
  let assign_chain x y = Assign_chain (x,y)
  let what x = What x
  let what_chain x y = What_chain (x,y)
  let is_function v ps =
    let rec init acc = function
      | [] -> []
      | [x] -> x :: List.rev acc
      | h::t -> init (h::acc) t
    in
    Define (v, init [] ps)

  let int64 = (fun x -> Str.implode x |> Int64.of_string) <$> token (many1 digit <|> (char '-' >>:: many1 digit))

  let rec expr =
    let rec fvalue = lazy (
      let rec go a =
        (char_ '[' >> (fun s -> Lazy.force e s) >>= fun b ->
        char_ ']' >> go (Apply (a,b))) <|> unit a
      in
      Str.implode <$> ident_ >>= fun b -> go (Var b))
    and fact = lazy (num <$> int64 <|> Lazy.force fvalue <|> (fun s -> (char_ '(' >> Lazy.force e << char_ ')') s))
    and term = lazy (chainl1 (Lazy.force fact) ((mul <$ char_ '*') <|> (div <$ char_ '/')))
    and e = lazy (chainl1 (Lazy.force term) ((add <$ char_ '+') <|> (sub <$ char_ '-')))
    in
    Lazy.force e

  let rec stmt =
    let rec sis = lazy (Str.implode <$> ident_ <**> (is <$ str_ "is") <*> expr)
    and sfunction = lazy (Str.implode <$> ident_ <**> (is_function <$ str_ "is") << str_ "function" << str_ "of" << int64 << char_ ':' <*> sep_by expr (char_ ',') << char '.')
    and sdo = lazy (do_ <$ str_ "do" << char_ '{' <*> expr << char_ '}' <*> Lazy.force sassign)
    and sassign = lazy (
      let single = expr >>= fun x -> str_ "to" >> ident_ >>= fun v -> Assign_single (Str.implode v, x) |> unit in
      assign <$> (str_ "assign" >> chainl1 single (assign_chain <$ str_ "and") << char_ '!')
    )
    and swhat = lazy (
      let single = expr >>= fun a -> unit (What_single a) in
      what <$> (str_ "what" >> str_ "is" >> chainl1 single (what_chain <$ str_ "and") << char_ '?')
    )
    and s0 = lazy (Lazy.force sdo <|> Lazy.force swhat <|> Lazy.force sfunction <|> Lazy.force sis <|> Lazy.force sassign)
    in
    Lazy.force s0
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
  let rec map f = function
    | [] -> unit []
    | h::t -> f h >>= fun a -> map f t >>= fun b -> unit (a::b)
  let liftM2 f x y s =
    let x' = x s in
    let y' = y s in
    f x' y'
  let rec loop cnt body =
    if cnt = 0 then
      unit ()
    else
      body >> loop (cnt-1) body

  let singleton x = [x]
  let value x = Value x
  let unvalue = function
    | Value x -> x
    | Fun _ -> assert false
  let fun_ xs =
      Fun (List.map unvalue xs)

  let rec eval_e = function
    | Num n -> Value (R.r n 1L) |> unit
    | Var v -> fun tbl -> Hashtbl.find tbl v
    | Apply (f,x) ->
        fun tbl ->
          (match eval_e x tbl with
          | Fun _ -> failwith "parameter is Fun"
          | Value x ->
            match eval_e f tbl with
            | Value _ | Fun [] | Fun [_] ->
                failwith "ill-formed function"
            | Fun [a;b] ->
                Value R.(add a (mul b x))
            | Fun (a::b::cs) ->
                Fun (R.(add a (mul b x))::cs))
    | Add (x,y) -> value <$> liftM2 R.add (unvalue <$> eval_e x) (unvalue <$> eval_e y)
    | Sub (x,y) -> value <$> liftM2 R.sub (unvalue <$> eval_e x) (unvalue <$> eval_e y)
    | Mul (x,y) -> value <$> liftM2 R.mul (unvalue <$> eval_e x) (unvalue <$> eval_e y)
    | Div (x,y) -> value <$> liftM2 R.div (unvalue <$> eval_e x) (unvalue <$> eval_e y)

  let rec eval_assign = function
    | Assign_single (v,e) ->
        fun tbl ->
          Hashtbl.replace tbl v (eval_e e tbl)
    | Assign_chain (c1,c2) ->
        eval_assign c1 >> eval_assign c2

  let rec eval_what = function
    | What_single e ->
        (function
          | Value n -> R.print n; print_char '\n'
          | Fun (p::ps) ->
              List.iter (fun n -> R.print n; print_string ", ") ps;
              R.print p; print_char '\n'
          | _ -> assert false) <$> eval_e e
    | What_chain (c1,c2) ->
        eval_what c1 >> eval_what c2

  let rec eval_s = function
    | Assign assign -> eval_assign assign
    | Do (c,body) ->
        eval_e c >>= (function
          | Value (R.R (c,1L)) ->
              if c < 0L then
                failwith "loop counter is negative"
              else
                loop (Int64.to_int c) (eval_s body)
          | _ ->
              failwith "loop counter is not integer")
    | What what -> eval_what what
    | Define (v,ps) ->
        fun tbl ->
          let ps = List.map unvalue (map eval_e ps tbl) in
          let x = if List.length ps = 1 then Value (List.hd ps) else Fun ps in
          Hashtbl.replace tbl v x
end

let () =
  let tbl = Hashtbl.create 13 in
  let rec go _ =
    try
      let s = read_line () |> String.lowercase in
      match Parser.parse Parser.stmt s with
      | None -> go ()
      | Some ast -> Eval.eval_s ast tbl; go ()
    with End_of_file ->
      ()
  in
  go ()
