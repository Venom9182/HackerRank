let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d " (fun x -> x)
let (|>) x f = f x
let rec times n f x =
  if n = 0 then
    x
  else
    times (n-1) f (f (n-1) x)

let modulo = 100000007

let pow x y =
  let rec go x y r =
    if y = 0 then
      r
    else if y land 1 = 1 then
      go (x*x mod modulo) (y/2) (r*x mod modulo)
    else
      go (x*x mod modulo) (y/2) r
  in go x y 1

let inv x = pow x (modulo-2)

let binom n m =
  times m (fun i x -> x * (n-i) mod modulo * inv (i+1) mod modulo) 1

let () =
  for i = 1 to read_int 0 do
    let n = read_int 0 in
    let m = read_int 0 in
    binom n m |> string_of_int |> print_endline
  done
