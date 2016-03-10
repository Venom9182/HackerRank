let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d " (fun x -> x)
let read_float _ = Scanf.bscanf Scanf.Scanning.stdib " %f " (fun x -> x)

let myexp x =
  let rec go n y s =
    if n >= 10 then
      s
    else
      go (n+1) (y*.x/.float_of_int (n+1)) (s+.y)
  in
  go 0 1.0 0.0

let () =
  for i = 1 to read_int 0 do
    let x = read_float 0 in
    myexp x |> Printf.printf "%.4f\n"
  done
