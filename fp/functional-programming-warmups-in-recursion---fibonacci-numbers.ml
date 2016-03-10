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

let fib n =
  let rec go n a b =
    if n = 0 then
      a
    else
      go (n-1) b (a+b)
  in go n 1 0

let () =
  read_int 0 |> fib |> string_of_int |> print_endline
