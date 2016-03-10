let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d" (fun x -> x)

let () =
  for cc = 1 to read_int 0 do
    let n = read_int 0 in
    let a = read_int 0 in
    let b = read_int 0 in
    let a, b =
      if a < b then
        a, b
      else
        b, a
    in
    let rec f l i =
      if i >= 0 then (
        let x = a*i+b*(n-1-i) in
        if x <> l then
          Printf.printf "%d " x;
        f x (i-1)
      )
    in
    f (-1) (n-1);
    print_char '\n'
  done
