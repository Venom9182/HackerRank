let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d " (fun x -> x)
let () =
  for i = 1 to read_int () do
    print_endline "Hello World"
  done
