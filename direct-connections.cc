let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d" (fun x -> x)
let read_int64 _ = Scanf.bscanf Scanf.Scanning.stdib " %Ld" (fun x -> x)

open Int64
let ( +% ) = add
let ( -% ) = sub
let ( *% ) = mul
let ( %% ) = rem

let modulus = 1000000007L

let rec ceil_pow2 x =
  if x land (x-1) = 0 then
    x
  else
    ceil_pow2 @@ x + (x land -x)

let seg_add nn seg i v =
  let rec go i =
    if i > 0 then (
      seg.(i) <- (seg.(i) +% v) %% modulus;
      go (i/2)
    )
  in
  go (nn+i)

let seg_ask nn seg i j =
  let rec go i j s =
    if i < j then
      let ss = s +% (if i land 1 <> 0 then seg.(i) else 0L) +% (if j land 1 <> 0 then seg.(j-1) else 0L) in
      go ((i+1)/2) (j/2) @@ ss %% modulus
    else
      s
  in
  go (nn+i) (nn+j) 0L

let () =
  for cc = 1 to read_int 0 do
    let n = read_int 0 in
    let a = Array.init n read_int64 in
    let b = Array.init n read_int64 in
    let paa = Array.init n (fun i -> i) in
    let aa = Array.make n 0 in
    let bb = Array.init n (fun i -> i) in
    Array.sort (fun i j -> compare a.(i) a.(j)) paa;
    Array.sort (fun i j -> compare b.(i) b.(j)) bb;
    for i = 0 to n-1 do
      aa.(paa.(i)) <- i
    done;

    let nn = ceil_pow2 n in
    let seg_cnt = Array.make (2*nn) 0L in
    let seg_sum = Array.make (2*nn) 0L in
    let ans = ref 0L in
    for i = 0 to n-1 do
      let j = bb.(i) in
      let r = aa.(j) in
      let lc = seg_ask nn seg_cnt 0 r in
      let ls = seg_ask nn seg_sum 0 r in
      let rc = seg_ask nn seg_cnt r n in
      let rs = seg_ask nn seg_sum r n in
      ans := (!ans +% (a.(j) *% (lc -% rc) +% rs -% ls) %% modulus *% b.(j)) %% modulus;
      seg_add nn seg_cnt r 1L;
      seg_add nn seg_sum r a.(j)
    done;
    Printf.printf "%Ld\n" @@ (!ans +% modulus) %% modulus
  done
