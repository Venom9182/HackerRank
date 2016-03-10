let isdigit c = '0' <= c && c <= '9'

let explode s =
  let len = String.length s in
  let a = ref @@ Array.make 16 0 in
  let rec go i j =
    if i >= len then
      j
    else if isdigit s.[i] then (
      let rec f acc i =
        if i >= len || not (isdigit s.[i]) then
          acc, i
        else
          f (acc*10+int_of_char s.[i]-48) (i+1)
      in
      if j >= Array.length !a then (
        let nn = Array.length !a * 2 in
        let aa = Array.make nn 0 in
        Array.blit !a 0 aa 0 (Array.length !a);
        a := aa
      );
      let num, i = f 0 i in
      (!a).(j) <- num;
      go i (j+1)
    ) else
      go (i+1) j
  in
  let n = go 0 0 in
  Array.sub !a 0 n

let rec f xs ys =
  match xs, ys with
  | x::xx::xs', y::yy::ys' ->
      if x < y then
        f xs' ys
      else if x > y then
        f xs ys'
      else
        x::min xx yy::f xs' ys'
  | _ -> []

let () =
  let q = read_int() in
  let module IM = Map.Make(struct type t = int let compare = compare end) in
  let a = ref [] in
  for i = 1 to q do
    let b = Array.to_list @@ explode @@ read_line() in
    if i = 1 then
      a := b
    else
      a := f !a b
  done;
  List.iter (Printf.printf "%d ") !a;
  print_endline ""
