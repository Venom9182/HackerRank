let (%) f g x = f x |> g

let nub xs =
  let rec go acc = function
    | [] -> List.rev acc
    | [x] -> x::acc |> List.rev
    | x::(y::zs as ys) ->
        if x = y then
          go acc ys
        else
          go (x::acc) ys
  in
  go [] xs

let split_at c xs =
  let rec go acc c xs =
    if c <= 0 then
      List.rev acc, xs
    else
      match xs with
      | [] ->
          List.rev acc, []
      | x::xs' ->
          go (x::acc) (c-1) xs'
  in
  go [] c xs

let zip xs ys =
  let rec go acc xs ys =
    match xs, ys with
    | [], []
    | [], _::_
    | _::_, [] -> List.rev acc
    | x::xs, y::ys -> go ((x,y)::acc) xs ys
  in
  go [] xs ys

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
  let (>>::) x y = x >>= fun a -> y >>= fun b -> unit (a::b)

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

  let eof s =
    if s.pos = String.length s.s then
      LazyList.singleton ((), s)
    else
      LazyList.empty

  let char c = pred (fun c' -> c = c')
  let str s =
    let rec go = function
      | [] -> zero
      | h::t -> char h >>= fun b -> go t >>= fun bs -> unit (b::bs)
    in
    Str.explode s |> go
  let alnum = pred (fun c -> '0' <= c && c <= '9' || 'a' <= c && c <= 'z' || 'A' <= c && c <= 'Z' || c = '-')
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
    match LazyList.force ((drop (many space) >> x << eof) { s; pos = 0 }) with
    | LazyList.Nil -> None
    | LazyList.Cons ((x, _), _) -> Some x
end

type 'a assign = { lhs : 'a simple_term; rhs : 'a simple_term }
and 'a simple_term = Var of string * 'a | Relation of string * 'a simple_term list
type 'a complex_term = Simple of 'a simple_term | Eq of 'a assign | Neq of 'a assign
type 'a rule = { eq : 'a assign list; neq : 'a assign list; premiss : 'a simple_term list; conclusion : 'a simple_term }
type query = { qeq : unit assign list; qneq : unit assign list; goals : unit simple_term list }
type op = Rule of unit rule | Query of query | Nop | Quit

module Parser = struct
  include ParserCombinators

  let partition_complex =
    let rec go eq neq premiss = function
      | [] -> List.rev eq, List.rev neq, List.rev premiss
      | Eq x::xs -> go (x::eq) neq premiss xs
      | Neq x::xs -> go eq (x::neq) premiss xs
      | Simple x::xs -> go eq neq (x::premiss) xs
    in
    go [] [] []
  let simple_term =
    let name = (Str.implode % (fun x -> Relation (x,[]))) <$> token (many1 alnum) in
    let var = (Str.implode % (fun x -> Var (x,()))) <$> token (char_ '#' >>:: many1 alnum) in
    let rec relational = lazy (char_ '[' >> token (many1 alnum) << char_ ':' >>= fun n ->
      sep_by (fun s -> Lazy.force e s) (char_ ',') << char_ ']' >>= fun ts ->
      Relation (Str.implode n, ts) |> unit
    )
    and e = lazy (var <|> name <|> Lazy.force relational)
    in
    Lazy.force e <|> var <|> name
  let complex_term =
    let eq = char_ '<' >> simple_term >>= fun t1 ->
      char_ '=' >> simple_term << char_ '>' >>= fun t2 ->
      Eq {lhs=t1; rhs=t2} |> unit
    in
    let neq = char_ '<' >> simple_term >>= fun t1 ->
      str_ "/=" >> simple_term << char_ '>' >>= fun t2 ->
      Neq {lhs=t1; rhs=t2} |> unit
    in
    eq <|> neq <|> ((fun x -> Simple x) <$> simple_term)
  let rule =
    let imp = str_ "{(" >> sep_by complex_term (char_ ',') >>= fun terms ->
      char_ ')' >> str_ "=>" >> simple_term << char_ '}' >>= fun conclusion ->
      let eq, neq, premiss = partition_complex terms in
      {eq; neq; premiss; conclusion} |> unit
    in
    (imp <|> ((fun conclusion -> {eq=[]; neq=[]; premiss=[]; conclusion}) <$> simple_term)) << char_ '.'
  let query =
    char_ '(' >> sep_by complex_term (char_ ',') << str_ ")?" >>= fun terms ->
      let qeq, qneq, goals = partition_complex terms in
      {qeq; qneq; goals} |> unit
  let op =
    ((fun x -> Query x) <$> query) <|>
    ((fun x -> Rule x) <$> rule) <|>
    (str_ "quit!" >> unit Quit) <|>
    (char_ '%' >> many (pred (fun _ -> true)) >> unit Nop) <|>
    (unit Nop)
end

let rec lift_term i = function
  | Var (x,()) -> Var (x,i)
  | Relation (x,ts) -> Relation (x, List.map (lift_term i) ts)

let lift_assign i { lhs; rhs } =
  { lhs = lift_term i lhs; rhs = lift_term i rhs }

let lift_rule i { eq; neq; premiss; conclusion } =
  { eq = List.map (lift_assign i) eq;
    neq = List.map (lift_assign i) neq;
    premiss = List.map (lift_term i) premiss;
    conclusion = lift_term i conclusion }

let rec occurs (v,iv) = function
  | Var (w,iw) -> v = w && iv = iw
  | Relation (n,ts) -> List.exists (occurs (v,iv)) ts

let rec substitute (v,iv) t = function
  | Var (w,iw) as w' ->
      if v = w && iv = iw then
        t
      else
        w'
  | Relation (n,ts) ->
      Relation (n, List.map (substitute (v,iv) t) ts)

let rec substitute_assign v' t { lhs; rhs } =
  { lhs = substitute v' t lhs;
    rhs = substitute v' t rhs }

let rec fine { lhs; rhs } =
  match lhs, rhs with
  | Var (v,iv), Var (w,iw) ->
      v <> w || iv <> iw
  | Relation (l,lts), Relation (r,rts) ->
      l <> r || List.length lts <> List.length rts ||
      List.exists2 (fun lhs rhs -> fine {lhs; rhs}) lts rts
  | _ ->
      true

let rec reduce qs neq =
  function
  | [] ->
      if List.for_all fine neq then
        Some (qs,neq)
      else
        None
  | e::eq ->
      match e.lhs, e.rhs with
      | Var (v,iv), Var (w,iw) when v = w && iv = iw ->
          reduce qs neq eq
      | Var (v,iv), y ->
          if occurs (v,iv) y then
            None
          else
            reduce
              (List.map (substitute (v,iv) y) qs)
              (List.map (substitute_assign (v,iv) y) neq)
              (List.map (substitute_assign (v,iv) y) eq)
      | Relation (l,lts), Relation (r,rts) ->
          if l = r && List.length lts = List.length rts then
            reduce qs neq (List.fold_left2 (fun ts lhs rhs -> {lhs;rhs}::ts) eq lts rts)
          else
            None
      | x, y -> reduce qs neq ({lhs=y; rhs=x}::eq)

let rec search i rules neq eq gs vars =
  match gs with
  | [] ->
      (match reduce vars neq eq with
      | Some (r,_) -> [r]
      | None -> [])
  | g::gs' ->
      let f r =
        let eq' = {lhs=g; rhs=r.conclusion}::r.eq @ eq in
        let neq' = r.neq @ neq in
        if List.for_all fine r.neq then
          (match reduce (vars@r.premiss@gs') neq' eq' with
          | None -> []
          | Some (vpg,neq'') ->
              let vars', goals' = split_at (List.length vars) vpg in
              search (i+1) rules neq'' [] goals' vars')
        else
          []
      in
      List.map (lift_rule i % f) rules |> List.concat

let infer rules q =
  let rec collect_simple acc = function
    | Var (v,()) ->
        v::acc
    | Relation (_,ts) ->
        List.fold_left collect_simple acc ts
  in
  let collect { lhs; rhs } =
    collect_simple (collect_simple [] lhs) rhs
  in
  let vs = List.concat [List.map collect q.qeq; List.map collect q.qneq;
    List.map (collect_simple []) q.goals] |> List.concat |> List.sort compare |>
    nub
  in
  let vs' = List.map (fun v -> Var (v,0)) vs in
  search 1 rules
    (List.map (lift_assign 0) q.qneq)
    (List.map (lift_assign 0) q.qeq)
    (List.map (lift_term 0) q.goals)
    vs' |> List.map (zip vs)

let print_sol (n, t) =
  let rec f = function
    | Var _ ->
        print_char '?'
    | Relation (n,[]) ->
        print_string n
    | Relation (n, t::ts) ->
        Printf.printf "[%s: " n;
        f t;
        List.iter (fun t' ->
          print_string ", ";
          f t'
        ) ts;
        print_char ']'
  in
  Printf.printf "%s := " n;
  f t;
  print_endline ""

let () =
  let rec go rules =
    let s = read_line () in
    match Parser.parse Parser.op s with
    | None ->
        print_endline "+ parse error";
        go rules
    | Some Nop ->
        go rules
    | Some Quit ->
        print_endline "Bye."
    | Some (Rule r) ->
        print_endline "Ok.";
        go (r::rules)
    | Some (Query q) ->
        (match infer (List.rev rules) q with
        | [] ->
            print_endline "UNSAT"
        | []::_ ->
            print_endline "SAT"
        | sols ->
            List.iter (fun sol ->
              print_endline "SAT:";
              print_endline "=====";
              List.iter print_sol sol
            ) sols
        );
        print_endline "Ready.";
        go rules
  in
  go []
