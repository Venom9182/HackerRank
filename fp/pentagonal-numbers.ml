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

let () =
  rep (read_int 0) (read_int % (fun n -> (3*n*n-n)/2) % string_of_int % print_endline)
