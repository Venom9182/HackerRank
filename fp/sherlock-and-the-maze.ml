let read_int () = Scanf.bscanf Scanf.Scanning.stdib " %d " (fun x -> x)

let modulo = 1000000007

let main () =
  let n = read_int () in
  let m = read_int () in
  let k = read_int () in
  let r = Array.make_matrix n m 0 in
  let d = Array.make_matrix n m 0 in
  for j = 1 to m-1 do
    r.(0).(j) <- 1
  done;
  for i = 1 to n-1 do
    d.(i).(0) <- 1
  done;
  let rec iter k ans =
    let res = (r.(n-1).(m-1)+d.(n-1).(m-1)) mod modulo in
    if k > 0 then (
      let rr = Array.make_matrix n m 0 in
      let dd = Array.make_matrix n m 0 in
      for i = 0 to n-1 do
        let rec go j s =
          if j < m then (
            rr.(i).(j) <- s;
            go (j+1) ((s+d.(i).(j)) mod modulo)
          ) in
        go 0 0
      done;
      for j = 0 to m-1 do
        let rec go i s =
          if i < n then (
            dd.(i).(j) <- s;
            go (i+1) ((s+r.(i).(j)) mod modulo)
          ) in
        go 0 0
      done;
      for i = 0 to n-1 do
        for j = 0 to m-1 do
          r.(i).(j) <- rr.(i).(j);
          d.(i).(j) <- dd.(i).(j);
        done
      done;
      iter (k-1) ((ans+res) mod modulo)
    ) else
      (ans+res) mod modulo
  in
  print_endline (string_of_int (if n == 1 && m == 1 then 1 else iter k 0))

let () =
  for i = 1 to read_int () do
    main ()
  done
