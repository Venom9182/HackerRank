let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d" (fun x -> x)
let read_str _ = Scanf.bscanf Scanf.Scanning.stdib " %s" (fun x -> x)

let () =
  for cc = 1 to read_int 0 do
    let a = read_str 0 in
    let n = String.length a in
    let b = Array.make 26 0 in
    if n mod 2 <> 0 then
      print_endline "-1"
    else (
      for i = 0 to n/2-1 do
        let x = int_of_char a.[i] - 97 in
        b.(x) <- b.(x) + 1
      done;
      for i = n/2 to n-1 do
        let x = int_of_char a.[i] - 97 in
        b.(x) <- b.(x) - 1
      done;
      Printf.printf "%d\n" @@ Array.fold_left (fun s x -> s + abs x) 0 b / 2
    )
  done
