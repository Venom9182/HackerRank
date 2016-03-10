let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d " (fun x -> x)

let () =
  let n = read_int 0 in
  let m = read_int 0 in
  let a = Array.init n read_int in
  let st = Array.make_matrix 17 n 0 in
  let rec fill k =
    if 1 lsl k > n then
      ()
    else (
      for i = 0 to n-1 lsl k do
        st.(k).(i) <- min st.(k-1).(i) st.(k-1).(i+1 lsl (k-1))
      done;
      fill (k+1)
    )
  in
  for i = 0 to n-1 do
    st.(0).(i) <- a.(i)
  done;
  fill 1;
  for i = 1 to m do
    let l = read_int 0 in
    let r = read_int 0 in
    let rec go k =
      if 1 lsl k <= r-l+1 then
        min st.(k).(l) st.(k).(r-1 lsl k+1)
      else
        go (k-1)
    in
    go 16 |> string_of_int |> print_endline
  done





let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d " (fun x -> x)

type t = Leaf | Node of int * t * t

let () =
  let n = read_int 0 in
  let m = read_int 0 in
  let a = Array.init n read_int in
  let rec segment_build l r =
    if l = r-1 then
      Node (a.(l), Leaf, Leaf)
    else
      let m = (l+r) lsr 1 in
      let Node (lmi,_,_) as left = segment_build l m in
      let Node (rmi,_,_) as right = segment_build m r in
      Node (min lmi rmi, left, right)
  in
  let rec segment_rmq (Node (mi,left,right)) l r ll rr =
    if ll <= l && r <= rr then
      mi
    else
      let m = (l+r) lsr 1 in
      min (if ll < m then segment_rmq left l m ll rr else max_int) (if m < rr then segment_rmq right m r ll rr else max_int)
  in

  let tree = segment_build 0 n in
  for i = 1 to m do
    let l = read_int 0 in
    let r = read_int 0 in
    segment_rmq tree 0 n l (r+1) |> string_of_int |> print_endline
  done





let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d " (fun x -> x)

type t = Leaf | Node of int * t * t

let () =
  let n = read_int 0 in
  let m = read_int 0 in
  let a = Array.init n read_int in
  let q = Array.init m (fun i ->
    let x = read_int () in
    let y = read_int () in
    (i,x,y)) in
  Array.sort (fun (_,_,x) (_,_,y) -> compare x y) q;

  let ans = Array.make m 0 in
  let qid (i,_,_) = i in
  let ql (_,x,_) = x in
  let qr (_,_,x) = x in
  let djs = Array.make n 0 in
  let st = Array.make n 0 in
  let nst = ref 0 in
  let qix = ref 0 in

  let find_set x =
    let rec go x =
      if djs.(x) = x then
        x
      else (
        djs.(x) <- djs.(djs.(x));
        go djs.(x)
      )
    in go x
  in

  for i = 0 to n-1 do
    djs.(i) <- i;
    while !nst > 0 && a.(st.(!nst-1)) >= a.(i) do
      decr nst;
      djs.(st.(!nst)) <- i
    done;
    st.(!nst) <- i;
    incr nst;
    while !qix < m && qr q.(!qix) = i do
      ans.(qid q.(!qix)) <- a.(find_set (ql q.(!qix)));
      incr qix
    done
  done;
  for i = 0 to m-1 do
    print_endline (string_of_int ans.(i))
  done
