open Int32

let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d" (fun x -> x)

let () =
  let n = read_int 0 in
  let a = Array.init n read_int in
  let st1 = Array.make_matrix 16 n 0 in
  let st2 = Array.make_matrix 16 n 0 in
  let rec fill k =
    if 1 lsl k > n then
      ()
    else (
      for i = 0 to n-1 lsl k do
        st1.(k).(i) <- min st1.(k-1).(i) st1.(k-1).(i+1 lsl (k-1));
        st2.(k).(i) <- max st2.(k-1).(i) st2.(k-1).(i+1 lsl (k-1))
      done;
      fill (k+1)
    )
  in
  for i = 0 to n-1 do
    st1.(0).(i) <- a.(i);
    st2.(0).(i) <- a.(i)
  done;
  fill 1;

  let rec rmq l r k =
    if 1 lsl k <= r-l then
      min st1.(k).(l) st1.(k).(r-1 lsl k),
      max st2.(k).(l) st2.(k).(r-1 lsl k)
    else
      rmq l r (k-1)
  in

  for i = 1 to read_int 0 do
    let x = read_int 0 in
    let d = read_int 0 in
    let rec lext y k =
      if k < 0 then
        y
      else (
        let yy = max 0 (y-1 lsl k) in
        let mi, ma = rmq yy (x+1) 15 in
        if a.(x) <= mi && of_int ma <= add (of_int a.(x)) (of_int d) then
          lext yy (k-1)
        else
          lext y (k-1)
      ) in
    let rec rext y k =
      if k < 0 then
        y
      else (
        let yy = min n (y+1 lsl k) in
        let mi, ma = rmq x yy 15 in
        if a.(x) <= mi && of_int ma <= add (of_int a.(x)) (of_int d) then
          rext yy (k-1)
        else
          rext y (k-1)
      ) in
    rext x 15 - lext x 15 |> Printf.printf "%d\n"
  done
