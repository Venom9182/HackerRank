let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d" (fun x -> x)
let read_str _ = Scanf.bscanf Scanf.Scanning.stdib " %s" (fun x -> x)

let inf = max_int/2

let read () =
  let buf = Buffer.create 0 in
  let rec go () =
    try
      let s = read_str() in
      if s <> "" then (
        Buffer.add_string buf s;
        go()
      )
    with End_of_file ->
      ()
  in
  go();
  Buffer.contents buf

let () =
  let n = read_int 0 in
  let k = read_int 0 in
  let a = Array.init n read_str in
  let nn = read_int 0 in
  let kk = read_int 0 in
  let aa = Array.init nn read_str in
  let bm = Array.make_matrix (1 lsl (k-1)) 2 (-1) in

  let recv = read() in
  let len = String.length recv in

  let f n k a hist =
    let r = ref 0 in
    for i = 0 to n-1 do
      for j = 0 to k-1 do
        let v = if a.(i).[j] = '0' then 0 else (hist lsr (k-1-j) land 1) in
        r := !r lxor (v lsl i)
      done
    done;
    !r
  in
  for i = 0 to (1 lsl (k-1)) - 1 do
    bm.(i).(0) <- f n k a i;
    bm.(i).(1) <- f n k a @@ i lor (1 lsl (k-1))
  done;

  let hamming pat pos =
    let rec go acc pat i =
      if i >= n then
        acc
      else
        let v = if recv.[pos+i] = '0' then 0 else 1 in
        let v = (pat land 1) lxor v in
        go (acc+v) (pat lsr 1) (i+1)
    in
    go 0 pat 0
  in

  let dp = Array.make_matrix (len/n+1) (1 lsl (k-1)) inf in
  let plan = Array.make_matrix (len/n+1) (1 lsl (k-1)) (-1) in
  dp.(0).(0) <- 0;
  for i = 0 to len/n-1 do
    (*let cur = dp.(i land 1) and suc = dp.((i+1) land 1) in*)
    let cur = dp.(i) and suc = dp.(i+1) in
    let sucp = plan.(i+1) in
    Array.fill suc 0 (1 lsl (k-1)) inf;
    for j = 0 to (1 lsl (k-1)) - 1 do
      let j0 = j lsr 1
      and j1 = (j lor (1 lsl (k-1))) lsr 1 in
      let o0 = bm.(j).(0)
      and o1 = bm.(j).(1) in

      let t = cur.(j) + hamming o0 (i*n) in
      if t < suc.(j0) then (
        suc.(j0) <- t;
        sucp.(j0) <- j
      );
      let t = cur.(j) + hamming o1 (i*n) in
      if t < suc.(j1) then (
        suc.(j1) <- t;
        sucp.(j1) <- j
      )
    done
  done;

  let rec get_ans ans ansj j =
    if j >= 1 lsl (k-1) then
      ans, ansj
    else if dp.((len/n)).(j) < ans then
      get_ans dp.((len/n)).(j) j (j+1)
    else
      get_ans ans ansj (j+1)
  in
  let ans, ansj = get_ans inf (-1) 0 in
  (*Printf.printf "%d\n" ans;*)

  let send = Bytes.make (len/n) ' ' in
  let rec trace i j =
    if i > 0 then (
      Bytes.set send (i-1) (if j land (1 lsl (k-2)) = 0 then '0' else '1');
      trace (i-1) plan.(i).(j)
    )
  in
  trace (len/n) ansj;
  (*Printf.printf "= %s\n" (Bytes.to_string send);*)

  let rec recode i j =
    if i < len/n-(k-1) then (
      let v = if send.[i] = '0' then 0 else 1 lsl (kk-1) in
      let j' = j lor v in
      let pat = f nn kk aa j' in
      let rec pr pat nn =
        if nn > 0 then (
          print_char @@ if pat land 1 = 0 then '0' else '1';
          pr (pat lsr 1) (nn-1)
        )
      in
      pr pat nn;
      recode (i+1) (j' lsr 1)
    )
  in
  recode 0 0;
  print_endline ""
