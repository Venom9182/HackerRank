let read_string _ = Scanf.bscanf Scanf.Scanning.stdib " %s " (fun x -> x)

let rec f () =
  let s = read_string() in
  if s <> "" then (
    print_char s.[0];
    f()
  )

let () =
  f();
  print_newline()
