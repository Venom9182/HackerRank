let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d" (fun x -> x)
let read_int64 _ = Scanf.bscanf Scanf.Scanning.stdib " %Ld" (fun x -> x)
let read_str _ = Scanf.bscanf Scanf.Scanning.stdib " %s" (fun x -> x)

open Int64
let ( +% ) = add
let ( -% ) = sub

let () =
  for _ = 1 to read_int 0 do
    let n = read_int 0 in
    let a = Array.init n (fun _ -> Array.make_matrix n n 0L) in
    let b = Array.init n (fun _ -> Array.make_matrix n n 0L) in
    for _ = 1 to read_int 0 do
      if read_str 0 = "UPDATE" then
        let x = read_int 0 - 1 in
        let y = read_int 0 - 1 in
        let z = read_int 0 - 1 in
        let w = read_int64 0 in
        let dlt = w -% b.(x).(y).(z) in
        let rec f xx yy zz =
          if xx < n then
            if yy < n then
              if zz < n then (
                a.(xx).(yy).(zz) <- a.(xx).(yy).(zz) +% dlt;
                f xx yy (zz lor (zz+1))
              ) else
                f xx (yy lor (yy+1)) z
            else
              f (xx lor (xx+1)) y z
        in
        f x y z;
        b.(x).(y).(z) <- w
      else
        let x = read_int 0 - 1 in
        let y = read_int 0 - 1 in
        let z = read_int 0 - 1 in
        let xx = read_int 0 in
        let yy = read_int 0 in
        let zz = read_int 0 in
        let rec f x y z =
          let rec go xx yy zz s =
            if xx = 0 then
              s
            else if yy = 0 then
              go (xx land (xx-1)) y z s
            else if zz = 0 then
              go xx (yy land (yy-1)) z s
            else
              go xx yy (zz land (zz-1)) (s +% a.(xx-1).(yy-1).(zz-1))
          in
          go x y z 0L
        in
        Printf.printf "%Ld\n" @@ f xx yy zz -% f xx yy z -% f xx y zz -% f x yy zz +% f xx y z +% f x yy z +% f x y zz -% f x y z
    done
  done
