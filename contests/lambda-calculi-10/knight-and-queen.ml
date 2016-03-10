let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d" (fun x -> x)

let n = 50

let () =
  let nimn = Array.make_matrix n n 0
  and nimq = Array.make_matrix n n 0 in
  let mex = Array.make (n*n) 0 in
  let tick = ref 0 in
  let rec get_mex ii =
    if mex.(ii) = !tick then
      get_mex @@ ii+1
    else
      ii
  in

  for i = 0 to n-1 do
    for j = 0 to n-1 do
      incr tick;
      for ii = 1 to i do mex.(nimq.(i-ii).(j)) <- !tick done;
      for ii = 1 to j do mex.(nimq.(i).(j-ii)) <- !tick done;
      for ii = 1 to min i j do mex.(nimq.(i-ii).(j-ii)) <- !tick done;
      nimq.(i).(j) <- get_mex 0
    done
  done;

  for i = 0 to n-1 do
    for j = 0 to n-1 do
      incr tick;
      let g ii jj =
        if 0 <= i-ii && 0 <= j-jj then
          mex.(nimn.(i-ii).(j-jj)) <- !tick
      in
      g 1 2;
      g 2 1;
      nimn.(i).(j) <- get_mex 0
    done
  done;

  (*for i = 0 to n-1 do*)
    (*for j = 0 to n-1 do*)
      (*Printf.printf "%d " nimq.(i).(j)*)
    (*done;*)
    (*print_newline()*)
  (*done;*)
  (*print_endline "===";*)
  (*for i = 0 to n-1 do*)
    (*for j = 0 to n-1 do*)
      (*Printf.printf "%d " nimn.(i).(j)*)
    (*done;*)
    (*print_newline()*)
  (*done*)

  for _ = 1 to read_int() do
    let nx = read_int() in
    let ny = read_int() in
    let qx = read_int() in
    let qy = read_int() in
    print_endline @@ if nimn.(nx).(ny) <> nimq.(qx).(qy) then "WIN" else "LOSE"
  done
