let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d" (fun x -> x)

let () =
  let n = read_int 0 in
  let l = Array.make (n+1) 0 in
  let r = Array.make (n+1) 0 in
  for i = 1 to n do l.(i) <- read_int 0; r.(i) <- read_int 0 done;
  let rec go n =
    if n > 0 then (
      let k = read_int 0 in
      let rec f d x =
        if x > 0 then (
          if d mod k = 0 then (
            let t = l.(x) in
            l.(x) <- r.(x);
            r.(x) <- t
          );
          f (d+1) l.(x);
          Printf.printf "%d " x;
          f (d+1) r.(x)
        )
      in
      f 1 1;
      print_char '\n';
      go (n-1)
    )
  in
  go @@ read_int 0
