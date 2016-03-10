let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d" (fun x -> x)
let read_int64 _ = Scanf.bscanf Scanf.Scanning.stdib " %Ld" (fun x -> x)
let flip f x y = f y x

let getb (_,b,_) = b
let geti (_,_,i) = i

let surpass (a1,b1,i1) (a2,b2,i2) =
  let open Int64 in
  let da = sub a1 a2 and db = sub b2 b1 in
  if rem da db <> 0L || i1 > i2 then
    add (div da db) 1L
  else
    div da db

let at (a,b,_) t =
  let open Int64 in
  add a (mul b t)

let () =
  let n = read_int 0 in
  let m = read_int 0 in
  let a = Array.init n read_int64 in
  let b = Array.init n read_int64 in
  let c : (int64*int64*int) array = Array.make n (0L,0L,0) in
  for i = 0 to n-1 do
    c.(i) <- a.(i), b.(i), i
  done;
  Array.sort (flip compare) c;
  let rec compress i j =
    if i >= n then
      j
    else if j = 0 || getb c.(j-1) < getb c.(i) then (
      if j < 2 || surpass c.(j-2) c.(j-1) < surpass c.(j-1) c.(i) then (
        c.(j) <- c.(i);
        compress (i+1) (j+1)
      ) else
        compress i (j-1)
    ) else
      compress (i+1) j
  in
  let n = compress 0 0 in

  let q = Array.init m (fun i -> read_int64 0, i) in
  let ans = Array.make m 0 in
  Array.sort compare q;
  let rec go i j =
    if j < m then (
      if i+1 < n && surpass c.(i) c.(i+1) <= fst q.(j) then
        go (i+1) j
      else (
        ans.(snd q.(j)) <- geti c.(i);
        go i (j+1)
      )
    )
  in
  go 0 0;
  for i = 0 to m-1 do
    Printf.printf "%d\n" (1+ans.(i))
  done
