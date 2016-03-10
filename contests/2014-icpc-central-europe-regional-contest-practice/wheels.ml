open Int64

let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d" (fun x -> x)
let read_int64 _ = Scanf.bscanf Scanf.Scanning.stdib " %Ld" (fun x -> x)
let pow2 x = x * x

let rec gcd x y =
  if y = 0L then
    x
  else
    gcd y (rem x y)

let () =
  for i = 1 to read_int 0 do
    let n = read_int 0 in
    let x = Array.make n 0 in
    let y = Array.make n 0 in
    let r = Array.make n 0 in
    for i = 0 to n-1 do
      x.(i) <- read_int 0;
      y.(i) <- read_int 0;
      r.(i) <- read_int 0
    done;
    let es = Array.init n (fun i ->
        let ret = ref [] in
        for j = 0 to n-1 do
          if pow2 (x.(i)-x.(j)) + pow2 (y.(i)-y.(j)) = pow2 (r.(i)+r.(j)) then
            ret := j :: !ret
        done;
        !ret
      ) in
    let p = Array.make n 0L in
    let q = Array.make n 1L in
    p.(0) <- 1L;
    let rec dfs = function
      | [] -> ()
      | v::vs ->
        List.fold_left (fun vs u ->
            if p.(u) = 0L then (
              let pp = mul p.(v) (of_int r.(v))
              and qq = mul q.(v) (of_int r.(u)) in
              let d = gcd pp qq in
              p.(u) <- div (neg pp) d;
              q.(u) <- div qq d;
              u::vs
            ) else
              vs
          ) vs es.(v) |> dfs
    in
    dfs [0];
    for i = 0 to n-1 do
      if p.(i) = 0L then
        print_endline "not moving"
      else (
        if q.(i) < 0L then (
          p.(i) <- neg p.(i);
          q.(i) <- neg q.(i)
        );
        Printf.printf "%Ld" (abs p.(i));
        if q.(i) > 1L then
          Printf.printf "/%Ld" q.(i);
        print_endline (if p.(i) < 0L then " counterclockwise" else " clockwise")
      )
    done
  done
