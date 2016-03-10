let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d" (fun x -> x)

let ( +% ) = Int64.add
let ( *% ) = Int64.mul
let ( %% ) = Int64.rem

let sieve n nn =
  let a = Array.make (n+1) true in
  let p = Array.make nn 0 in
  let m = ref 0 in
  a.(0) <- false;
  a.(1) <- false;
  for i = 2 to n do
    let rec f j =
      if j < !m && p.(j) <= n/i then (
        a.(p.(j)*i) <- false;
        if i mod p.(j) <> 0 then
          f (j+1)
      )
    in
    if a.(i) then (
      p.(!m) <- i;
      incr m
    );
    f 0
  done;
  !m, p, a

let modulus = 1000000007L

let () =
  let nn, p, a = sieve 1000000 540000 in
  for cc = 1 to read_int() do
    let x = read_int() in
    let y = read_int() in
    let ans0 = ref 0 in
    let ans1 = ref 1L in
    for i = x to y do
      if i mod 2 <> 0 then (
        if a.(i-2) then (
          incr ans0;
          (*Printf.printf "+ %d %d\n" 2 (i-2);*)
          ans1 := Int64.(!ans1 *% (of_int @@ i-2) *% 2L %% modulus)
        )
      ) else if i >= 8 then (
        let rec f j =
          if a.(i-p.(j)) then (
            if p.(j) < i-p.(j) then (
              (*Printf.printf "+ %d %d\n" p.(j) (i-p.(j));*)
              incr ans0;
              ans1 := Int64.(!ans1 *% (of_int p.(j)) %% modulus *% (of_int @@ i-p.(j)) %% modulus)
            )
          ) else
            f (j+1)
        in
        f 0
      );
    done;
    Printf.printf "%d %Ld\n" !ans0 !ans1
  done
