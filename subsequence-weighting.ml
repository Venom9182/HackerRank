let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d" (fun x -> x)
let read_int64 _ = Scanf.bscanf Scanf.Scanning.stdib " %Ld" (fun x -> x)

let ( +% ) = Int64.add

let fenwick_add n a i v =
  let rec go i =
    if i < n then (
      if v > a.(i) then
        a.(i) <- v;
      go @@ i lor (i+1)
    )
  in
  go i

let fenwick_get_max a i =
  let rec go i mx =
    if i > 0 then
      go (i land (i-1)) (max mx a.(i-1))
    else
      mx
  in
  go i 0L

let () =
  for cc = 1 to read_int 0 do
    let n = read_int 0 in
    let a = Array.init n (fun i -> read_int 0, - i) in
    Array.sort compare a;
    let b = Array.init n read_int64 in
    let s = Array.make n 0L in
    for i = 0 to n-1 do
      let j = - snd a.(i) in
      let acc = fenwick_get_max s j +% b.(j) in
      fenwick_add n s j acc
    done;
    Printf.printf "%Ld\n" @@ fenwick_get_max s n
  done
