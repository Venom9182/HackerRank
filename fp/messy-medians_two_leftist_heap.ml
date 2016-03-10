let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d " (fun x -> x)
let flip f x y = f y x

module LeftistHeap(S : sig type key val compare : key -> key -> int end) = struct
  type t = E | N of S.key * int * t * t

  let compare = S.compare

  let rank = function
    | E -> -1
    | N (_,r,_,_) -> r

  let make x l r =
    if rank l >= rank r then
      N (x,rank r+1,l,r)
    else
      N (x,rank l+1,r,l)

  let rec merge h1 h2 = match h1, h2 with
    | E, _ -> h2
    | _, E -> h1
    | N (x,_,l1,r1), N (y,_,l2,r2) ->
        if compare x y < 0 then
          make x l1 (merge r1 h2)
        else
          make y l2 (merge r2 h1)

  let top (N (x,_,_,_)) = x
  let pop (N (_,_,l,r)) = merge l r
  let push x h = merge h (N (x,0,E,E))
end

module Min = LeftistHeap(struct type key = int let compare = compare end)
module Max = LeftistHeap(struct type key = int let compare = flip compare end)

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
  let a = Array.make (n+1) (0, 0, Max.E, Min.E) in
  for i = 1 to n do
    let x = read_int 0 in
    a.(i) <- if x < 0 then a.(i+x) else add x a.(i-1);
    median a.(i) |> Printf.printf "%d\n"
  done
