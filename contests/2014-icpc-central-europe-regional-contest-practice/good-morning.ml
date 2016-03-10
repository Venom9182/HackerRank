let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d" (fun x -> x)

let () =
  for i = 1 to read_int 0 do
    let n = read_int 0 in
    let rec g x q =
      if x = 0 then
        true
      else (
        let p = x mod 10 in
        if q < 0 then
          g (x/10) p
        else if p = 0 then
          if q > 0 then
            false
          else
            g (x/10) p
        else if q = 0 then
          if p mod 3 = 0 then
            false
          else
            g (x/10) p
        else if (p-1) mod 3 > (q-1) mod 3 || (p-1)/3 > (q-1)/3 then
          false
        else
          g (x/10) p
      ) in
    let rec f x =
      if g (n+x) (-1) then n+x
      else if g (n-x) (-1) then n-x
      else f (x+1)
    in
    f 0 |> Printf.printf "%d\n"
  done
