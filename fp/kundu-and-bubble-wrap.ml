let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d " (fun x -> x)
let (|>) x f = f x

let () =
  let n = read_int () * read_int () in
  let rec go n sum =
    if n = 0 then
      sum
    else
      go (n-1) (sum+.(1.0/.float_of_int n))
  in
  float_of_int n *. go n 0.0 |> string_of_float |> print_endline
