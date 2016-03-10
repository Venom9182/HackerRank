let read_string _ = Scanf.bscanf Scanf.Scanning.stdib " %s " (fun x -> x)

let rec f () =
  let s = read_string() in
  if s <> "" then (
    let i, s = Scanf.sscanf s "%d%s" (fun x y -> x,y) in
    print_char @@ if i < String.length s then s.[i] else ' ';
    f()
  )

let () =
  f();
  print_newline()
