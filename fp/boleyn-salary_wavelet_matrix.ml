let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d" (fun x -> x)
let flip f x y = f y x

let euler_tour n es root =
  let dfn1 = Array.make n 0
  and dfn2 = Array.make n 0 in
  let rec dfs i x =
    dfn1.(x) <- i;
    dfn2.(x) <- List.fold_left dfs (i+1) es.(x);
    dfn2.(x)
  in
  dfs root 0 |> ignore;
  dfn1, dfn2

module Wavelet_matrix = struct
  let create nbit a =
    let n = Array.length a in
    let rnks = Array.make_matrix nbit n 0 in
    for bit = nbit-1 downto 0 do
      for i = 0 to n-1 do
        rnks.(bit).(i) <- (if i > 0 then rnks.(bit).(i-1) else 0) + (a.(i) lsr bit land 1)
      done;
      Array.stable_sort (fun x y -> (x lsr bit land 1) - (y lsr bit land 1)) a
    done;
    rnks

  let select rnks l r k =
    let nbit = Array.length rnks in
    let n = Array.length rnks.(0) in
    let rec go bit l r k v =
      let rank b i =
        let c = if i = 0 then 0 else rnks.(bit).(i-1) in
        if b then c
        else i-c
      in
      if bit < 0 then
        v
      else
        let lc = rank false r - rank false l in
        let ln = n-rnks.(bit).(n-1) in
        let dir = k >= lc in
        let l' = rank dir l in
        let r' = rank dir r in
        if dir then
          go (bit-1) (ln+l') (ln+r') (k-lc) (v*2+1)
        else
          go (bit-1) l' r' k (v*2)
    in
    go (nbit-1) l r k 0
end

let () =
  let n = read_int 0 in
  let m = read_int 0 in
  let es = Array.make n [] in
  for i = 1 to n-1 do
    let x = read_int 0 - 1 in
    let y = read_int 0 - 1 in
    es.(y) <- x :: es.(y)
  done;
  let dfn1,dfn2 = euler_tour n es 0 in

  let salary = Array.init n read_int in
  let h = Hashtbl.create n in
  let a = Array.make n 0 in
  Array.iteri (Hashtbl.replace h |> flip) salary;
  Array.iteri (fun i x -> a.(dfn1.(i)) <- x) salary;
  let rnks = Wavelet_matrix.create 30 a in

  let rec go i d =
    if i > 0 then (
      let x = read_int 0 + d in
      let k = read_int 0 in
      let v = Wavelet_matrix.select rnks (dfn1.(x)+1) dfn2.(x) (k-1) in
      let d' = Hashtbl.find h v in
      Printf.printf "%d\n" (d'+1);
      go (i-1) d'
    )
  in
  go m (-1)
