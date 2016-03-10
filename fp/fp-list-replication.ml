let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d " (fun x -> x)
let (|>) x f = f x

let () =
  let n = read_int 0 in
  let rec go2 t x acc =
    if t = 0 then
      acc
    else
      go2 (t-1) x (x::acc) in
  let rec go acc =
    try
      let x = read_int 0 in
      go (go2 n x acc)
    with End_of_file ->
      acc
  in
  go [] |> List.rev |> List.map string_of_int |> String.concat "\n" |> print_endline
