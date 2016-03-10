let queen n =
  let rec go i l m r c0 c1 =
    if i = 0 then
      1
    else
      let mask = (1 lsl n - 1) land lnot (l lor m lor r) in
      let rec f j acc =
        if j < 0 then
          acc
        else
          let jj = 1 lsl j in
          if jj land mask <> 0 && abs (j-c0) <> 2 && abs (j-c1) <> 1 then
            f (j-1) (acc + go (i-1) ((l lor jj) lsr 1) (m lor jj) ((r lor jj) lsl 1) j c0)
          else
            f (j-1) acc
      in f (n-1) 0
  in go n 0 0 0 (-3) (-3)

let () =
  read_int () |> queen |> Printf.printf "%d\n"
