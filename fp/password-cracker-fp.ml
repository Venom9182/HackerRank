let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d " (fun x -> x)
let read_str _ = Scanf.bscanf Scanf.Scanning.stdib " %s " (fun x -> x)

let () =
  for cc = 1 to read_int 0 do
    let n = read_int 0 in
    let ps = Array.init n read_str in
    let a = read_str 0 in
    let m = String.length a in
    let prev = Array.make (m+1) (-1) in
    prev.(0) <- 0;
    for i = 1 to m do
      for j = 0 to n-1 do
        let l = String.length ps.(j) in
        if i >= l && prev.(i-l) >= 0 && String.sub a (i-l) l = ps.(j) then
          prev.(i) <- j
      done
    done;
    if prev.(m) = -1 then
      print_endline "WRONG PASSWORD"
    else (
      let rec trace i =
        if i = 0 then
          ()
        else (
          let id = prev.(i) in
          trace (i-String.length ps.(id));
          Printf.printf "%s " ps.(id)
        )
      in
      trace m;
      print_char '\n'
    )
  done
