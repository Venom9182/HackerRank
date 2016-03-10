let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d" (fun x -> x)
let inf = max_int

let dijkstra n e src =
  let d = Array.make (n+1) inf in
  let h = Array.init n (fun i -> i) in
  let lkp = Array.init (n+1) (fun i -> i) in
  let up i =
    let x = h.(i) in
    let rec go i =
      if i > 0 then (
        let j = (i-1)/2 in
        if d.(x) < d.(h.(j)) then (
          h.(i) <- h.(j);
          lkp.(h.(i)) <- i;
          go j
        ) else
          i
      ) else
        i
    in
    let i = go i in
    h.(i) <- x;
    lkp.(x) <- i
  in
  let down i =
    let x = h.(i) in
    let rec go i =
      let j = i*2+1 in
      if j < n then (
        let j =
          if j+1 < n && d.(h.(j+1)) < d.(h.(j)) then j+1
          else j
        in
        if d.(h.(j)) < d.(x) then (
          h.(i) <- h.(j);
          lkp.(h.(i)) <- i;
          go j
        ) else
          i
      ) else
        i
    in
    let i = go i in
    h.(i) <- x;
    lkp.(x) <- i
  in
  d.(src) <- 0;
  up src;
  while d.(h.(0)) < inf do
    let x = h.(0) in
    h.(0) <- n;
    down 0;
    List.iter (fun (y,w) ->
        if d.(x) + w < d.(y) then (
          d.(y) <- d.(x) + w;
          up lkp.(y)
        )
      ) e.(x)
  done;
  d

let () =
  let n = read_int 0 in
  let e = Array.init n (fun _ -> []) in
  for _ = 1 to read_int 0 do
    let x = read_int 0 - 1 in
    let y = read_int 0 - 1 in
    let z = read_int 0 in
    e.(x) <- (y,z) :: e.(x);
    e.(y) <- (x,z) :: e.(y)
  done;
  let d0 = dijkstra n e 0 in
  let d1 = dijkstra n e (n-1) in
  let dist = d1.(0) in
  Array.sort compare d0;
  Array.sort compare d1;
  let open Int64 in
  let rec go i j s c =
    if i < 0 then
      c
    else
      let x = dist-1-d0.(i) in
      if j < n && d1.(j) < x then
        go i (j+1) (add s @@ of_int d1.(j)) c
      else
        go (i-1) j s (add c @@ sub (mul (of_int x) (of_int j)) s)
  in
  Printf.printf "%Ld\n" @@ go (n-1) 0 0L 0L
