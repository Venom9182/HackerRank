let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d" (fun x -> x)

let tarjan_lca n ~es ~qs ~ps ~ans =
  let djs = Array.make n (-1) in
  let rec find x =
    if djs.(x) <> x then (
      djs.(x) <- djs.(djs.(x));
      find (djs.(x))
    ) else
      x
  in

  let fenwick = Array.make n 0 in
  let rec add i x =
    if i < n then (
      fenwick.(i) <- fenwick.(i) + x;
      add (i lor (i+1)) x
    )
  in
  let get_sum i =
    let rec go acc i =
      if i = 0 then
        acc
      else
        go (fenwick.(i-1) + acc) (i land (i-1))
    in
    go 0 i
  in

  let rec go x =
    djs.(x) <- x;
    List.iter (fun (i,y,a,b) ->
      if djs.(y) >= 0 then
        let lca = find djs.(y) in
        qs.(lca) <- (lnot i,-1,a,b) :: qs.(lca)
    ) qs.(x);
    add x 1;
    List.iter (fun y ->
      go y;
      djs.(y) <- x
    ) es.(x);
    List.iter (fun (i,_,a,b) ->
      let r = get_sum b - get_sum a in
      if i >= 0 then
        ans.(i) <- ans.(i) + r
      else
        ans.(lnot i) <- ans.(lnot i) - r * 2 + (if a <= x && x < b then 1 else 0)
    ) qs.(x);
    add x (-1)
  in
  go 0

let () =
  let n = read_int 0 in
  let m = read_int 0 in
  let es = Array.make n [] in
  let qs = Array.make n [] in
  let ps = Array.make n 0 in
  for i = 1 to n-1 do
    let p = read_int 0 in
    ps.(i) <- p;
    es.(p-1) <- i :: es.(p-1)
  done;
  for i = 0 to m-1 do
    let x = read_int 0 - 1 in
    let y = read_int 0 - 1 in
    let a = read_int 0 - 1 in
    let b = read_int 0 in
    qs.(x) <- (i,y,a,b) :: qs.(x);
    qs.(y) <- (i,x,a,b) :: qs.(y);
  done;

  let ans = Array.make m 0 in
  tarjan_lca n ~es ~qs ~ps ~ans;
  Array.iter (Printf.printf "%d\n") ans
