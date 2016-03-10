let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d " (fun x -> x)
let (|>) x f = f x

let maxn = 1000
let modulo = 100000007

let () =
  let a = Array.make (maxn+1) 1 in
  for i = 1 to maxn do
    let rec go j r =
      if j >= i then
        r
      else
        go (j+1) ((r+a.(j)*a.(i-1-j)) mod modulo)
    in
    a.(i) <- go 0 0
  done;
  for i = 1 to read_int 0 do
    a.(read_int 0) |> string_of_int |> print_endline
  done
