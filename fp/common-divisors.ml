let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d " (fun x -> x)

let gcd a b =
  let rec go a b =
    if b = 0 then
      a
    else
      go b (a mod b)
  in go a b

let cnt x =
  let rec go p r =
    if p*p > x then
      r
    else if p*p = x then
      r+1
    else if x mod p = 0 then
      go (p+1) (r+2)
    else
      go (p+1) r
  in go 1 0

let () =
  for i = 1 to read_int 0 do
    let a = read_int 0 in
    let b = read_int 0 in
    gcd a b |> cnt |> string_of_int |> print_endline
  done
