let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d " (fun x -> x)
let flip f x y = f y x

module IntMap = Map.Make(struct type t = int let compare = compare end)

let add x m =
  let cnt = try IntMap.find x m with Not_found -> 0 in
  IntMap.add x (cnt+1) m

let remove x m =
  let cnt = try IntMap.find x m with Not_found -> 0 in
  IntMap.add x (cnt-1) m

let () =
  let n = read_int 0 in
  let a = Array.init n read_int in
  let bag = Array.fold_left (flip remove) IntMap.empty a in
  let n = read_int 0 in
  let a = Array.init n read_int in
  let bag = Array.fold_left (flip add) bag a in
  IntMap.iter (fun x c ->
    let rec go c =
      if c <= 0 then
        ()
      else
        Printf.printf "%d " x
    in go c
  ) bag
