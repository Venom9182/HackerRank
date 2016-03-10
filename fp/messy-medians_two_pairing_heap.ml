let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d " (fun x -> x)
let flip f x y = f y x

module PairingHeap(S : sig type key val max_key : key val compare : key -> key -> int end) = struct
  type node = {key: S.key; child: node; sibling: node}

  let rec nil = {key = S.max_key; child = nil; sibling = nil}
  let is_nil a = a.key = S.max_key

  let merge a b =
    if S.compare a.key b.key < 0 then
      {a with child = {b with sibling = a.child}}
    else
      {b with child = {a with sibling = b.child}}

  let merge_list x =
    let rec go acc x =
      if is_nil x then
        acc
      else
        if is_nil x.sibling then
          x::acc
        else
          go (merge x x.sibling::acc) x.sibling.sibling
    in
    match go [] x with
    | [] -> nil
    | u::us -> List.fold_left (fun u v -> merge u v) u us

  let singleton k = {key = k; child = nil; sibling = nil}
  let pop x = merge_list x.child
  let top x = x.key
  let push k x = merge x (singleton k)
end

module Min = PairingHeap(struct type key = int let max_key = max_int let compare = compare end)
module Max = PairingHeap(struct type key = int let max_key = min_int let compare = flip compare end)

let add x (s1,s2,h1,h2) =
  if s1 = 0 then
    (s1+1, s2, Max.push x h1, h2)
  else
    let mx1 = Max.top h1 in
    if s1 = s2 then
      let mn2 = Min.top h2 in
      if x <= mn2 then
        (s1+1, s2, Max.push x h1, h2)
      else
        (s1+1, s2, Max.push mn2 h1, Min.pop h2 |> Min.push x)
    else
      if x >= mx1 then
        (s1, s2+1, h1, Min.push x h2)
      else
        (s1, s2+1, Max.pop h1 |> Max.push x, Min.push mx1 h2)

let median (_,_,h1,_) = Max.top h1

let () =
  let n = read_int 0 in
  let a = Array.make (n+1) (0, 0, Max.nil, Min.nil) in
  for i = 1 to n do
    let x = read_int 0 in
    a.(i) <- if x < 0 then a.(i+x) else add x a.(i-1);
    median a.(i) |> Printf.printf "%d\n"
  done
