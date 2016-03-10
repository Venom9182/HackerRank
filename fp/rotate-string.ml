let () =
  for i = 1 to read_int () do
    let a = read_line () in
    let n = String.length a in
    let aa = a ^ a in
    let rec go i j =
      if j < n then (
        print_char aa.[i];
        go (i+1) (j+1)
      )
    in
    for j = 0 to n-1 do
      go ((j+1) mod n) 0;
      print_char (if j = n-1 then '\n' else ' ')
    done
  done
