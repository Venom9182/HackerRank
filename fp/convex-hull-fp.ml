let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d " (fun x -> x)
let (|>) x f = f x

let rep n f =
  let rec go n f acc =
    if n = 0 then
      acc
    else
      go (n-1) f (f () :: acc)
  in go n f []

let cw (x0,y0) (x1,y1) (x2,y2) = (x1-x0)*(y2-y0)-(x2-x0)*(y1-y0) < 0

let andrew_monotone_chain ps : (int*int) list =
  let rec half ps st = match ps, st with
    | ([], st) -> st
    | (p::ps, ([] as st)) | (p::ps, (_::[] as st)) ->
        half ps (p::st)
    | (p::ps, (p0::p1::st' as st)) ->
        if cw p0 p1 p then
          half ps (p::st)
        else
          half (p::ps) (p1::st')
  in
  let ps = List.sort compare ps in
  let _::upper = half ps [] in
  let _::lower = half (List.rev ps) [] in
  upper @ lower

let dist (x0,y0) (x1,y1) =
  let x = float_of_int (x0-x1) in
  let y = float_of_int (y0-y1) in
  sqrt (x*.x+.y*.y)

let perimeter ps =
  let rec go us acc = match us with
  | [u] -> acc +. dist (List.hd ps) u
  | u::v::us' -> go (v::us') (acc +. dist u v)
  in go ps 0.0

let () =
  let n = read_int 0 in
  let ps = rep n (fun () -> let x = read_int () in let y = read_int () in (x,y)) in
  andrew_monotone_chain ps |> perimeter |> Printf.printf "%.1f\n"
