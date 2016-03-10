let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d" (fun x -> x)

let lower_bound a l h x =
  let rec f l h =
    if l < h then (
      let m = (l+h)/2 in
      if a.(m) < x then f (m+1) h else f l m
    ) else
      l
  in
  f l h

let ilog2_ceil x =
  let rec f i =
    if 1 lsl i >= x then
      i
    else
      f (i+1)
  in
  f 0

type wavelet = {sorted: int array; rnk: int array array}

module UncompressedWaveletTree = struct
  let rec build a aa sorted rnk d l h =
    if h-l > 1 then (
      let m = (l+h)/2 in
      let pivot = sorted.(m-1) in
      let eq = ref @@ m - lower_bound sorted l h pivot in
      let j0 = ref l and j1 = ref m in
      for i = l to h-1 do
        let x = a.(i) in
        rnk.(d).(i) <- !j0-l;
        if x < pivot || x == pivot && !eq > 0 then (
          if x = pivot then
            decr eq;
          aa.(!j0) <- x;
          incr j0
        ) else (
          aa.(!j1) <- x;
          incr j1
        )
      done;
      ignore @@ build aa a sorted rnk (d+1) l m;
      ignore @@ build aa a sorted rnk (d+1) m h
    );
    {sorted=sorted; rnk=rnk}

  let make a =
    let n = Array.length a in
    let b = Array.make n 0 in
    let nn = ilog2_ceil n in
    let sorted = Array.copy a in
    Array.sort compare sorted;
    let rnk = Array.make_matrix nn n 0 in
    build a b sorted rnk 0 0 n

  let kth w l h k =
    let rec f d l h ll hh k =
      if h-l = 1 then
        w.sorted.(l)
      else (
        let m = (l+h)/2 in
        let cl = w.rnk.(d).(ll)
        and ch =
          if h = hh then m-l
          else w.rnk.(d).(hh) in
        if k < ch-cl then
          f (d+1) l m (l+cl) (l+ch) k
        else
          f (d+1) m h (m+ll-l-cl) (m+hh-l-ch) (k-ch+cl)
      )
    in
    f 0 0 (Array.length w.sorted) l h k
end

module W = UncompressedWaveletTree

let () =
  let n = read_int() in
  let m = read_int() in
  let a = Array.init n read_int in
  let b = Array.init m read_int in
  let wa = W.make a in
  let wb = W.make b in
  let rec median i0 i1 j0 j1 =
    let m = i1-i0
    and n = j1-j0 in
    let rec f k i j =
      if k > 0 then (
        let p = (k-1) lsr 1 in
        if j+p >= n || i+p < m && W.kth wa i0 i1 (i+p) < W.kth wb j0 j1 (j+p) then
          f (k-p-1) (i+p+1) j
        else
          f (k-p-1) i (j+p+1)
      ) else
        i, j
    in
    let i, j = f ((m+n-1)/2) 0 0 in
    let i = ref i and j = ref j in
    let ans = ref 0.0 in
    if !j >= n || !i < m && W.kth wa i0 i1 !i < W.kth wb j0 j1 !j then (
      ans := float_of_int (W.kth wa i0 i1 !i);
      incr i
    ) else (
      ans := float_of_int (W.kth wb j0 j1 !j);
      incr j
    );
    if (m+n) mod 2 <> 0 then
      !ans
    else
      (!ans +. float_of_int (if !j >= n || !i < m && W.kth wa i0 i1 !i < W.kth wb j0 j1 !j then W.kth wa i0 i1 !i else W.kth wb j0 j1 !j)) /. 2.0
  in

  for _ = 1 to read_int() do
    let la = read_int() in
    let ra = read_int() in
    let lb = read_int() in
    let rb = read_int() in
    Printf.printf "%f\n" @@ median (la-1) ra (lb-1) rb
  done
