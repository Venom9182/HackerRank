let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d" (fun x -> x)

let ( +% ) = Int64.add
let ( *% ) = Int64.mul

let () =
  let n = read_int 0 in
  let a = Array.init n read_int in
  let rec go i s ans =
    if i = n then
      ans *% 2L
    else
      match s with
      | [] -> go (i+1) [a.(i), 1] ans
      | (x,c)::s' ->
        if a.(i) > x then
          go i s' ans
        else if a.(i) = x then
          go (i+1) ((x,c+1)::s') (ans +% Int64.of_int c)
        else
          go (i+1) ((a.(i),1)::s) ans
  in
  Printf.printf "%Ld\n" @@ go 0 [] 0L
