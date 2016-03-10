let () =
  let b = Array.make 256 false in
  let a = read_line() |> Bytes.of_string in
  let n = String.length a in
  let rec go i j =
    if i >= n then
      j
    else (
      let c = Bytes.get a i in
      if b.(c |> int_of_char) then
        go (i+1) j
      else (
        b.(c |> int_of_char) <- true;
        Bytes.set a j c;
        go (i+1) (j+1)
      )
    )
  in
  let n = go 0 0 in
  Bytes.sub_string a 0 n |> print_endline;
