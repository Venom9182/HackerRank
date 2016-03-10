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

module ParserCombinators(S : sig type store end) = struct
  type store = S.store
  type input = { s: string; pos: int; store: store }
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
  let drop x = x >> zero
  let space = pred (fun c -> c = ' ' || c = '\t' || c = '\r' || c = '\n')
  let ident = Str.implode <$> many1 (pred (fun c -> 'a' <= c && c <= 'z' || 'A' <= c && c <= 'Z' || '0' <= c && c <= '9' || c = '_'))

  let token x = x << drop (many space)
  let char_ c = char c |> token
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

  let parse x store s =
    match LazyList.force ((drop (many space) >> x) { s; pos = 0; store }) with
    | LazyList.Nil -> None
    | LazyList.Cons ((x, _), _) -> Some x
end

module LeftistHeap = struct
  type t = E | N of int * int * int * t * t

  let empty = E

  let is_empty = function
    | E -> true
    | _ -> false

  let singleton x = N (x,0,0,E,E)

  let rank = function
    | E -> -1
    | N (_,_,rk,_,_) -> rk

  let make x l r =
    if rank l >= rank r then
      N (x,0,rank r+1,l,r)
    else
      N (x,0,rank l+1,r,l)

  let add i = function
    | E -> E
    | N (x,d,rk,l,r) -> N (x+i,d+i,rk,l,r)

  let rec merge h1 h2 = match h1, h2 with
    | E, _ -> h2
    | _, E -> h1
    | N (x,d1,_,l1,r1), N (y,d2,_,l2,r2) ->
        if x < y then
          make x (add d1 l1) (merge (add d1 r1) h2)
        else
          make y (add d2 l2) (merge (add d2 r2) h1)

  let top = function
    | E -> invalid_arg "empty"
    | N (x,_,_,_,_) -> x

  let pop = function
    | E -> invalid_arg "empty"
    | N (_,d,_,l,r) -> merge (add d l) (add d r)

  let push h x = merge h (N (x,0,0,E,E))
end

type term =
  | Var of LeftistHeap.t * int
  | Abs of LeftistHeap.t * term
  | App of LeftistHeap.t * term * term
  | S
  | K
  | I
  | B
  | C

module List = struct
  include List

  let fold_left1 f xs =
    List.fold_left f (List.hd xs) (List.tl xs)

  let rec drop c = function
    | [] -> []
    | _::xs' as xs ->
        if c = 0 then
          xs
        else
          drop (c-1) xs'
end

let get_dh = function
  | Var (dh,_) -> dh
  | App (dh,_,_) -> dh
  | Abs (dh,_) -> dh
  | _ -> LeftistHeap.empty

let rec cut dh =
  if LeftistHeap.is_empty dh then
    dh
  else if LeftistHeap.top dh < 0 then
    cut (LeftistHeap.pop dh)
  else
    dh

(*let rec free l = function*)
  (*| Var (dh, c) -> c = l*)
  (*| App (dh,x,y) -> free l x || free l y*)
  (*| Abs (dh,x) -> free (l+1) x*)
  (*| _ -> false*)

let free x = match x with
  | Var (_,_)
  | App (_,_,_)
  | Abs (_,_) ->
      let dh = get_dh x in
      not (LeftistHeap.is_empty dh) && LeftistHeap.top dh = 0
  | _ -> false

let rec shift = function
  | Var (dh,c) as v -> Var (LeftistHeap.add (-1) dh |> cut, c-1)
  | App (dh,x,y) -> App (LeftistHeap.add (-1) dh |> cut, shift x, shift y)
  | Abs _ -> assert false
  | c -> c

let var x = Var (LeftistHeap.singleton x, x)

let abstract x = Abs (LeftistHeap.add (-1) (get_dh x) |> cut, x)

let app x y = App (LeftistHeap.merge (get_dh x) (get_dh y), x, y)

let rec nest lv t =
  if lv = 0 then
    t
  else
    nest (lv-1) (abstract t)

let print t =
  let rec go r = function
  | Var (_,c) ->
      Printf.printf "%d" c
  | Abs _ ->
      assert false
  | App (_,x,y) ->
      if r then print_char '(';
      go false x;
      go true y;
      if r then print_char ')'
  | S -> print_char 'S'
  | K -> print_char 'K'
  | I -> print_char 'I'
  | B -> print_char 'B'
  | C -> print_char 'C'
  in
  go false t

let rec tr =
  let e = LeftistHeap.empty in function
  | App (_,x,y) -> app (tr x) (tr y)
  | Abs (_, Var (_, 0)) -> I
  | Abs (_, App (_, x, Var (_, 0))) when not (free x) ->
      tr x |> shift
  | Abs (_, x) ->
      if not (free x) then
        app K (tr x |> shift)
      else (
        match x with
        | Abs (_, y) ->
            tr (abstract (tr x))
        | App (_,x,y) ->
            (*App (App (S, tr (Abs x)), tr (Abs y))*)
            let f1 = free x
            and f2 = free y in
            if not f1 then
              app (app B (tr x |> shift)) (tr (abstract y))
            else if not f2 then
              app (app C (tr (abstract x))) (tr y |> shift)
            else
              app (app S (tr (abstract x))) (tr (abstract y))
        | _ ->
            assert false
      )
  | t -> t

module Parser = struct
  include ParserCombinators(struct type store = string list end)

  let update f = fun s -> LazyList.singleton ((), { s with store = f s.store })

  let lookup v =
    let rec find i = function
      | [] -> failwith "not found"
      | v'::t ->
          if v = v' then
            i
          else
            find (i+1) t
    in
    fun s -> LazyList.singleton (find 0 s.store, s)

  let term =
    let rec pvar = lazy (ident_ >>= fun v -> var <$> lookup v)
    and pabstract = lazy (
      char_ '\\' >> many1 ident_ >>= fun vs ->
      let l = List.length vs in
      char_ '.' >>
      update (fun ctx -> List.fold_left (fun ctx v -> v::ctx) ctx vs) >>
      (nest l <$> Lazy.force term) <<
      update (List.drop l)
    )
    and term0 = lazy ((char_ '(' >> (fun s -> Lazy.force term s) << char_ ')' <|> Lazy.force pabstract <|> Lazy.force pvar))
    and term = lazy (List.fold_left1 app <$> many1 (Lazy.force term0))
    in
    Lazy.force term
end

let () =
  let n = read_int () in
  for i = 1 to n do
    let s = read_line () in
    match Parser.parse Parser.term [] s with
    | None -> ()
    | Some t -> tr t |> print; print_endline ""
  done
