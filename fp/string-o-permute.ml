let rec iter () =
  try
    let s = read_line () in
    let rec go i =
      if i+1 >= String.length s then
        ()
      else (
        let t = s.[i] in
        s.[i] <- s.[i+1];
        s.[i+1] <- t;
        go (i+2)
      )
    in
    go 0;
    print_endline s;
    iter ()
  with End_of_file ->
    ()

let () =
  read_line ();
  iter ()
