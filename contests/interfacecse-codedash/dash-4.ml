let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d" (fun x -> x)

let () =
  for cc = 1 to read_int 0 do
    let n = read_int 0 in
    let a = Array.make_matrix n n 0 in
    let x = ref 0 in
    for i = 0 to (n-1)/2 do
      for j = i to n-1-i do
        incr x;
        a.(j).(i) <- !x
      done;
      for j = i+1 to n-1-i do
        incr x;
        a.(n-1-i).(j) <- !x
      done;
      for j = n-2-i downto i do
        incr x;
        a.(j).(n-1-i) <- !x
      done;
      for j = n-2-i downto i+1 do
        incr x;
        a.(i).(j) <- !x
      done
    done;
    for i = 0 to n-1 do
      for j = 0 to n-1 do
        Printf.printf "%d%c" a.(i).(j) (if j = n-1 then '\n' else ' ')
      done;
      print_endline ""
    done
  done
