type t = Empty | Node of int * t * t

let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d" (fun x -> x)
let read_str _ = Scanf.bscanf Scanf.Scanning.stdib " %s" (fun x -> x)

let fcts x p =
  let rec go acc x =
    if x mod p <> 0 then
      acc
    else
      go (acc+1) (x/p)
  in
  go 0 x

let rec segment_build n a p =
  let rec go l r =
    if l = r-1 then
      Node(fcts a.(l) p, Empty, Empty)
    else
      let m = (l+r) lsr 1 in
      let Node(lmi,_,_) as lt = go l m in
      let Node(rmi,_,_) as rt = go m r in
      Node(max lmi rmi, lt, rt)
  in
  go 0 n

let rec segment_rmq n t ll rr =
  let rec go (Node(ma,lt,rt)) l r =
    if ll <= l && r <= rr then
      ma
    else
      let m = (l+r) lsr 1 in
      max
      (if ll < m then go lt l m else min_int)
      (if m < rr then go rt m r else min_int)
  in
  go t 0 n

let rec segment_add n t x y =
  let rec go (Node(ma,lt,rt)) l r =
    if l = r-1 then
      Node(ma+y, lt, rt)
    else
      let m = (l+r) lsr 1 in
      let (Node(lma,_,_) as lt), (Node(rma,_,_) as rt) =
        if x < m then
          go lt l m, rt
        else
          lt, go rt m r
      in
      Node(max lma rma, lt, rt)
  in
  go t 0 n

open Int64

let modulus = 1000000007L

let pow x n =
  let rec go r x n =
    if n = 0 then
      r
    else
      let x' = rem (mul x x) modulus in
      if n mod 2 = 0 then
        go r x' (n/2)
      else
        go (rem (mul r x) modulus) x' (n/2)
  in
  go 1L (of_int x) n

let () =
  let n = read_int 0 in
  let a = Array.init n read_int in
  let ps = ref [] in
  for i = 2 to 100 do
    let rec go j =
      if j*j > i then
        ps := i :: !ps
      else if i mod j > 0 then
        go (j+1)
    in
    go 2
  done;

  let ts = Array.make 100 Empty in
  List.iter (fun p -> ts.(p) <- segment_build n a p) !ps;

  for i = 1 to read_int 0 do
    let op = read_str 0 in
    if op.[0] = 'Q' then (
      let l = read_int 0 in
      let r = read_int 0 + 1 in
      let ans = ref 1L in
      List.iter (fun p ->
        let c = segment_rmq n ts.(p) l r in
        ans := rem (mul (pow p c) !ans) modulus
      ) !ps;
      Printf.printf "%Ld\n" !ans
    ) else
      let x = read_int 0 in
      let y = read_int 0 in
      List.iter (fun p ->
        let c = fcts y p in
        if c > 0 then
          ts.(p) <- segment_add n ts.(p) x c
      ) !ps
  done
