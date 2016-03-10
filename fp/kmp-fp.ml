let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d " (fun x -> x)
let read_string _ = Scanf.bscanf Scanf.Scanning.stdib " %s " (fun x -> x)

let morris_pratt pat text =
  let n = String.length pat in
  let m = String.length text in
  let pi = Array.make n 0 in

  let rec go i j =
    let rec go2 j =
      if j > 0 && pat.[i] <> pat.[j] then
        go2 pi.(j-1)
      else if pat.[i] <> pat.[j] then
        j
      else
        j+1 in
    if i = n then
      ()
    else
      let j' = go2 j in (
        pi.(i) <- j';
        go (i+1) j'
      )
  in
  go 1 0;

  let rec go i j =
    let rec go2 j =
      if j > 0 && text.[i] <> pat.[j] then
        go2 pi.(j-1)
      else if text.[i] <> pat.[j] then
        (false,j)
      else if j+1 = n then
        (true,j+1)
      else
        (false,j+1) in
    if i = m then
      false
    else
      let (ans,j') = go2 j in
      ans || go (i+1) j'
  in go 0 0

let () =
  let n = read_int () in
  for i = 1 to n do
    let text = read_string () in
    let pat = read_string () in
    if morris_pratt pat text then
      print_endline "YES"
    else
      print_endline "NO"
  done
