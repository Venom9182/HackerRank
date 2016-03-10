open Int64

let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d" (fun x -> x)
let read_int64 _ = Scanf.bscanf Scanf.Scanning.stdib " %Ld" (fun x -> x)

let () =
  for i = 1 to read_int 0 do
    let n = read_int64 0 in
    let n2 = add n n in
    let rec f x =
      if mul x x > n2 then
        0
      else if rem n2 x = 0L then (
        let y = div n2 x in
        if logand (sub x y) 1L <> 0L then
          to_int x
        else
          f (add x 1L)
      ) else
        f (add x 1L)
    in
    let x = f 2L in
    if x = 0 then
      print_endline "IMPOSSIBLE"
    else (
      let y = div n2 (of_int x) |> to_int in
      Printf.printf "%Ld = %d" n ((y-x+1)/2);
      for i = (y-x+1)/2+1 to (y+x)/2 do
        Printf.printf " + %d" i
      done;
      print_endline ""
    )
  done
