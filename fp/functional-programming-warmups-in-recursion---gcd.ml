let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d " (fun x -> x)
let (|>) x f = f x
let (%) f g x = g (f x)
let rec rep n f =
  if n = 0 then
    ()
  else (
    f();
    rep (n-1) f
  )

let rec gcd a b =
  if b = 0 then
    a
  else
    gcd b (a mod b)

let () =
  gcd (read_int 0) (read_int 0) |> string_of_int |> print_endline
