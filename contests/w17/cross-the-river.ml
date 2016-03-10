let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d" (fun x -> x)

let get_y (y,_,_) = y
let get_x (_,x,_) = x
let get_z (_,_,z) = z

let lower_bound xs x =
  let rec go l h =
    if l = h then
      l
    else
      let m = (l+h) lsr 1 in
      if fst xs.(m) < x then
        go (m+1) h
      else
        go l m
  in
  go 0 (Array.length xs)

let upper_bound xs x =
  let rec go l h =
    if l = h then
      l
    else
      let m = (l+h) lsr 1 in
      if fst xs.(m) <= x then
        go (m+1) h
      else
        go l m
  in
  go 0 (Array.length xs)

let rec ceil_pow2 x =
  if x land (x-1) = 0 then
    x
  else
    ceil_pow2 @@ x + (x land -x)

let () =
  let n = read_int 0 in
  let h = read_int 0 in
  let dh = read_int 0 in
  let dw = read_int 0 in
  let ys = Array.init n (fun _ ->
      let y = read_int 0 in
      let x = read_int 0 in
      let z = read_int 0 in
      y,x,z
    ) in
  Array.sort compare ys;
  let xs = Array.mapi (fun i (_,x,_) -> x,i) ys in
  Array.sort compare xs;
  let xi2yi = Array.init n (fun i -> snd xs.(i)) in
  let yi2xi = Array.make n (-1) in
  for i = 0 to n-1 do
    yi2xi.(xi2yi.(i)) <- i
  done;

  let nn = ceil_pow2 n in
  let segment = Array.make (2*nn-1) min_int in
  let segment_modify i v =
    let rec go i =
      if i > 0 then
        let j = (i-1)/2 in
        segment.(j) <- max segment.(2*j+1) segment.(2*j+2);
        go j
    in
    segment.(nn-1+i) <- v;
    go (nn-1+i)
  in
  let segment_query l h =
    let ret = ref min_int in
    let rec go l h =
      if l < h then (
        if l land 1 = 0 then
          ret := max !ret segment.(l);
        if h land 1 = 0 then
          ret := max !ret segment.(h-1);
        go (l/2) ((h-1)/2)
      )
    in
    go (nn-1+l) (nn-1+h);
    !ret
  in

  let ans = ref min_int in
  let i = ref 0 in
  let ii = ref 0 in
  let tmp = Array.make n min_int in
  while !i < n do
    let y = get_y ys.(!i) in
    while y - get_y ys.(!ii) > dh do
      segment_modify yi2xi.(!ii) min_int;
      incr ii
    done;
    let j = ref !i in
    while !j < n && get_y ys.(!j) = y do
      let mx = segment_query
          (lower_bound xs @@ get_x ys.(!j) - dw)
          (upper_bound xs @@ get_x ys.(!j) + dw) in
      let v = max
          (if mx = min_int then mx else mx + get_z ys.(!j))
          (if y <= dh then get_z ys.(!j) else min_int) in
      tmp.(!j) <- v;
      if y >= h-dh then
        ans := max !ans v;
      incr j
    done;
    for j = !i to !j-1 do
      segment_modify yi2xi.(j) tmp.(j)
    done;
    i := !j
  done;
  Printf.printf "%d\n" !ans
