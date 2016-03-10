let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d" (fun x -> x)
let read_float _ = Scanf.bscanf Scanf.Scanning.stdib " %f" (fun x -> x)
let read_str _ = Scanf.bscanf Scanf.Scanning.stdib " %s" (fun x -> x)

let () =
  let y = read_int() in
  let a = Array.make y 0.0 in
  let b = Array.make y false in
  for i = 0 to y-1 do
    a.(i) <- read_float();
    b.(i) <- read_str() = "Yes"
  done;

  let rec trisect l h =
    let rec f x s i =
      if i = y then
        s
      else
        let t =
          if b.(i) then
            1.0 -. (1.0-.1.0/.a.(i)) ** x
          else
            (1.0-.1.0/.a.(i)) ** x
        in
        f x (s*.t) (i+1)
    in
    if l >= h then
      l
    else (
      let third = (h-l)/3 in
      let ll = l+third and hh = h-third in
      (*Printf.printf "+%d %d %f %f\n" ll hh (f (float_of_int ll) 1.0 0) (f (float_of_int hh) 1.0 0);*)
      if f (float_of_int ll) 1.0 0 < f (float_of_int hh) 1.0 0 then
        trisect (ll+1) h
      else
        trisect l (hh-1)
    )
  in

  Printf.printf "%d\n" @@ trisect 2 99999999
