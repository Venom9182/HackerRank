let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d " (fun x -> x)
let flip f x y = f y x

module IntMap = Map.Make(struct type t = int let compare = compare end)

let modulo = 1000000007

let factorize x map =
  let rec go p x map =
    let cnt p = try IntMap.find p map with Not_found -> 0 in
    if x = 1 then
      map
    else if p*p > x then
      IntMap.add x (cnt x + 1) map
    else if x mod p = 0 then
      go p (x/p) (IntMap.add p (cnt p + 1) map)
    else
      go (p+1) x map
  in go 2 x map

let gcd a b =
  let rec go p r =
    if p > 10000 then
      r
    else
      let acnt = try IntMap.find p a with Not_found -> 0 in
      let bcnt = try IntMap.find p b with Not_found -> 0 in
      let rcnt = min acnt bcnt in
      let r' = if rcnt = 0 then r else IntMap.add p rcnt r in
      go (p+1) r'
  in go 2 IntMap.empty

let pow x y =
  let rec go x y r =
    if y = 0 then
      r
    else if y land 1 = 1 then
      go (x*x mod modulo) (y/2) (r*x mod modulo)
    else
      go (x*x mod modulo) (y/2) r
  in go x y 1

let () =
  let n = read_int 0 in
  let a = Array.init n read_int in
  let m = read_int 0 in
  let b = Array.init m read_int in
  let afac = Array.fold_left (flip factorize) IntMap.empty a in
  let bfac = Array.fold_left (flip factorize) IntMap.empty b in
  IntMap.fold (fun x y r -> pow x y * r mod modulo) (gcd afac bfac) 1 |> string_of_int |> print_endline
