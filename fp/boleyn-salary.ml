let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d" (fun x -> x)

type key = int * int
type treap = E | N of key * int * int * treap * treap

let size = function
  | E -> 0
  | N (_,_,s,_,_) -> s

let singleton x = N (x, Random.int (1 lsl 29), 1, E, E)

let rotate_left (N (x,pri,s,l,N (y,pri',s',rl,rr))) =
  N (y,pri',s,N (x,pri,s-size rr-1,l,rl),rr)

let rotate_right (N (x,pri,s,N (y,pri',s',ll,lr),r)) =
  N (y,pri',s,ll,N (x,pri,s-size ll-1,lr,r))

let rec add x = function
  | E -> singleton x
  | N (y,pri,s,l,r) ->
      if x < y then
        let N (_,pri',_,_,_) as l' = add x l in
        if pri' < pri then
          N (y,pri,s+1,l',r) |> rotate_right
        else
          N (y,pri,s+1,l',r)
      else
        let N (_,pri',_,_,_) as r' = add x r in
        if pri' < pri then
          N (y,pri,s+1,l,r') |> rotate_left
        else
          N (y,pri,s+1,l,r')

let rec kth k (N (x,_,_,l,r)) =
  let ls = size l in
  if k < ls then
    kth k l
  else if k > ls then
    kth (k-ls-1) r
  else
    x

let rec fold f acc = function
  | E -> acc
  | N (x,_,_,l,r) ->
      fold f (f (fold f acc l) x) r

let merge t1 t2 =
  let t1,t2 = if size t1 < size t2 then t2,t1 else t1,t2 in
  fold (fun acc x -> add x acc) t1 t2

let dfs es ss ts =
  let rec go x =
    let r = List.fold_left (fun t y ->
      merge t (go y)) E es.(x)
    in
    ts.(x) <- r;
    add ss.(x) r
  in
  go 0 |> ignore

let () =
  let n = read_int 0 in
  let m = read_int 0 in
  let es = Array.make n [] in
  for i = 1 to n-1 do
    let x = read_int 0 - 1 in
    let y = read_int 0 - 1 in
    es.(y) <- x :: es.(y)
  done;
  let ss = Array.init n (fun i -> read_int 0, i) in
  let ts = Array.make n (Obj.magic 0) in
  dfs es ss ts;
  let rec go i d =
    if i > 0 then (
      let v = read_int 0 in
      let k = read_int 0 in
      let d' = kth (k-1) ts.(d+v) |> snd in
      Printf.printf "%d\n" (d'+1);
      go (i-1) d'
    )
  in
  go m (-1)
