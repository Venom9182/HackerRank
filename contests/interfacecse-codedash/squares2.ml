let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d" (fun x -> x)

let () =
  let f x = int_of_float @@ floor @@ sqrt @@ float_of_int x in
  for i = 1 to read_int 0 do
    let x = read_int 0 in
    let y = read_int 0 in
    Printf.printf "%d\n" (f y - f (x-1))
  done
