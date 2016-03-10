let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d" (fun x -> x)

module Fenwick_tree = struct
  let create n = Array.make n 0

  let rec add a i x =
    let n = Array.length a in
    let rec go i =
      if i < n then (
        a.(i) <- a.(i) + x;
        go (i lor (i+1))
      )
    in
    go i

  let get_sum a i =
    let rec go acc i =
      if i = 0 then
        acc
      else
        go (a.(i-1) + acc) (i land (i-1))
    in
    go 0 i
end

module F = Fenwick_tree

let n = 100000
let maxl = 16
let l = Array.make n (-1)
let r = Array.make n (-1)
let dep = Array.make n (-1)
let posl = Array.make n (-1)
let posr = Array.make n (-1)
let anc = Array.make_matrix (maxl+1) n 0

let rec preorder d tick x =
  if x = -1 then
    tick
  else (
    dep.(x) <- d;
    posl.(x) <- tick;
    let tick = preorder (d+1) (tick+1) l.(x) in
    let tick = preorder (d+1) tick r.(x) in
    posr.(x) <- tick;
    tick
  )

let get_lca xx yy =
  let x = ref @@ if dep.(xx) > dep.(yy) then xx else yy
  and y = ref @@ if dep.(xx) > dep.(yy) then yy else xx in
  for d = maxl downto 0 do
    if 1 lsl d <= dep.(!x)-dep.(!y) then
      x := anc.(d).(!x)
  done;
  if !x = !y then
    !x
  else (
    for d = maxl downto 0 do
      if anc.(d).(!x) <> anc.(d).(!y) then (
        x := anc.(d).(!x);
        y := anc.(d).(!y)
      )
    done;
    anc.(0).(!x)
  )

let () =
  let n = read_int() in
  for i = 1 to n-1 do
    let p = read_int()-1 in
    if l.(p) = -1 then
      l.(p) <- i
    else
      r.(p) <- i;
    anc.(0).(i) <- p
  done;
  ignore @@ preorder 0 0 0;
  for d = 1 to maxl do
    for i = 0 to n-1 do
      anc.(d).(i) <- if anc.(d-1).(i) = -1 then -1 else anc.(d-1).(anc.(d-1).(i))
    done
  done;

  let fenwick = F.create n in
  for _ = 1 to read_int() do
    if read_int() = 1 then (
      let x = read_int()-1 in
      F.add fenwick posl.(x) 1;
      if posr.(x) < n then
        F.add fenwick posr.(x) (-1)
    ) else (
      let x = read_int()-1 in
      let y = read_int()-1 in
      let lca = get_lca x y in
      let ans =
        F.get_sum fenwick (posl.(lca)+1) +
        (
          if x = lca then
            if posl.(l.(x)) <= posl.(y) && posl.(y) < posr.(l.(x)) then 1 else 0 (* y in left subtree of x *)
          else if y = lca then
            if posl.(l.(y)) <= posl.(x) && posl.(x) < posr.(l.(y)) then 0 else 1 (* x in left subtree of y *)
          else
            if posl.(x) < posl.(y) then 0 else 1 (* x precedes y in pre-order *)
        ) in
      print_endline @@ if ans mod 2 = 0 then "L" else "R"
    )
  done
