let (~-:) = Int64.neg
let (-:) = Int64.sub
let (&:) = Int64.logand
let (^:) = Int64.logxor
let (|:) = Int64.logor
let (<<:) = Int64.shift_left
let (>>:) = Int64.shift_right

let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d" (fun x -> x)
let read_char _ = Scanf.bscanf Scanf.Scanning.stdib " %c" (fun x -> x)

let bfs m n idx2ch ch2p2pos onet dst (_,a,_ as src) =
  let up = ref 0L and down = ref 0L
  and left = ref 0L and right = ref 0L in
  for i = 0 to n-1 do
    up := !up |: (1L <<: i);
    down := !down |: (1L <<: (m-1)*n+i);
  done;
  for i = 0 to m-1 do
    left := !left |: (1L <<: i*n);
    right := !right |: (1L <<: i*n+n-1);
  done;
  let up = !up and down = !down and left = !left and right = !right in

  let logt = Hashtbl.create 64 in
  for i = 0 to n*m-1 do
    Hashtbl.replace logt (1L <<: i) i
  done;

  let move other p =
    let h = Hashtbl.create 0 in
    let r = ref [] in
    let rec dfs p' =
      Hashtbl.replace h p' ();
      if p <> p' then
        r := p' :: !r;
      if (p' &: up) = 0L then (
        let q = p' >>: n in
        if (q &: other) = 0L && not (Hashtbl.mem h q) then
          dfs q
      );
      if (p' &: down) = 0L then (
        let q = p' <<: n in
        if (q &: other) = 0L && not (Hashtbl.mem h q) then
          dfs q
      );
      if (p' &: left) = 0L then (
        let q = p' >>: 1 in
        if (q &: other) = 0L && not (Hashtbl.mem h q) then
          dfs q
      );
      if (p' &: right) = 0L then (
        let q = p' <<: 1 in
        if (q &: other) = 0L && not (Hashtbl.mem h q) then
          dfs q
      )
    in
    dfs p;
    !r
  in

  let h = Hashtbl.create 0 in
  let visit src i = Hashtbl.replace h src i in
  let visited src = Hashtbl.mem h src in
  let extend (cnt,last,(occ,a,one)) =
    let r = ref [] in
    let don = ref (-1,-1,(-1L,a,-1L)) in
    Array.iteri (fun i p ->
      if i <> last then (
        List.iter (fun p' ->
          let b = Array.copy a in
          b.(i) <- p';
          let s = occ^:p^:p', b, one in
          let st = cnt+1, i, s in
          if not @@ visited s then (
            visit s (last,i,p);
            r := st :: !r;
            if p' = dst && i = 0 then
              don := st
          )
        ) (move (occ ^: p) p)
      )
    ) a;
    let rec move_one p =
      if p > 0L then (
        let x = p &: ~-: p in
        List.iter (fun y ->
          let s = occ^:x^:y, a, one^:x^:y in
          let st = cnt+1, -1, s in
          if not @@ visited s then (
            visit s (last,lnot (Hashtbl.find logt y),x^:y);
            r := st :: !r
          )
        ) (move (occ ^: x) x);
        move_one (p -: x)
      )
    in
    move_one one;
    !don, !r
  in
  let rec go fr re =
    match fr with
    | [] ->
        if re = [] then
          -1,-1,(-1L,[||],-1L)
        else
          go (List.rev re) []
    | x::xs ->
        let (cnt,_,_ as st), ys = extend x in
        if cnt >= 0 then
          st
        else
          go xs (ys @ re)
  in
  visit src (-1,-1,-1L);

  if a.(0) = dst then
    Printf.printf "0\n"
  else (
    let cnt,_,_ as st = go [0,-1,src] [] in
    Printf.printf "%d\n" cnt;
    let rec trace (cnt,last,(occ,a,one as s)) =
      if cnt > 0 then (
        let last', i', p' = Hashtbl.find h s in
        if i' >= 0 then (
          let p = a.(i') in
          let ch = Hashtbl.find idx2ch i' in
          let pos' = Hashtbl.find (Hashtbl.find ch2p2pos ch) p' in
          let pos = Hashtbl.find (Hashtbl.find ch2p2pos ch) p in
          a.(i') <- p';
          trace (cnt-1, last', (occ^:p^:p', a, one));
          Printf.printf "%c (%d,%d) (%d,%d)\n"
          ch (pos'/n) (pos' mod n) (pos/n) (pos mod n)
        ) else (
          trace (cnt-1, last', (occ^:p', a, one^:p'));
          let p = 1L <<: lnot i' in
          let p' = p' ^: p in
          let pos = Hashtbl.find logt p in
          let pos' = Hashtbl.find logt p' in
          let ch = Hashtbl.find onet p' in
          Printf.printf "%c (%d,%d) (%d,%d)\n"
          ch (pos'/n) (pos' mod n) (pos/n) (pos mod n);
          Hashtbl.replace onet p ch
        )
      )
    in
    trace st
  )

let () =
  let m = read_int 0 in
  let n = read_int 0 in
  let map = Hashtbl.create 0 in
  let xmin = Hashtbl.create 0 in
  let ymin = Hashtbl.create 0 in
  let xmax = Hashtbl.create 0 in
  let ymax = Hashtbl.create 0 in
  for i = 0 to m-1 do
    for j = 0 to n-1 do
      let ch = read_char() in
      if ch <> '.' then (
        Hashtbl.replace map ch (
          (try Hashtbl.find map ch with Not_found -> 0L) |: (1L <<: i*n+j));
        Hashtbl.replace xmin ch (
          min i (try Hashtbl.find xmin ch with Not_found -> m));
        Hashtbl.replace ymin ch (
          min j (try Hashtbl.find ymin ch with Not_found -> n));
        Hashtbl.replace xmax ch (
          max i (try Hashtbl.find xmax ch with Not_found -> 0));
        Hashtbl.replace ymax ch (
          max j (try Hashtbl.find ymax ch with Not_found -> 0))
      )
    done
  done;
  let target = read_char 0 in
  let dstx = read_int 0 in
  let dsty = read_int 0 in
  let dst = ref 0L in

  let ch2p2pos = Hashtbl.create 0 in
  let one = ref 0L in
  let idx2ch = Hashtbl.create 0 in
  let onet = Hashtbl.create 0 in
  let occ = ref 0L in
  let a = Array.make (Hashtbl.length map) 0L in
  let i = ref 0 in
  let flag = ref false in
  Hashtbl.iter (fun ch p ->
    let xmi = Hashtbl.find xmin ch in
    let ymi = Hashtbl.find ymin ch in
    let xma = Hashtbl.find xmax ch in
    let yma = Hashtbl.find ymax ch in
    let p2pos =
      try
        Hashtbl.find ch2p2pos ch
      with Not_found ->
        let t = Hashtbl.create (n*m) in
        Hashtbl.replace ch2p2pos ch t;
        t
    in
    let p0 = p >>: xmi*n+ymi in
    for i = 0 to m-1-(xma-xmi) do
      for j = 0 to n-1-(yma-ymi) do
        let q = p0 <<: i*n+j in
        Hashtbl.replace p2pos q (i*n+j);
        if ch = target && i = dstx && j = dsty then
          dst := q;
        (*Printf.printf "+ %c %d,%d %Ld\n" ch i j (p0 <<: i*n+j);*)
      done
    done;

    occ := !occ |: p;
    if ch <> target && xmi = xma && ymi = yma then (
      one := !one |: p;
      Hashtbl.replace onet p ch;
    ) else (
      if ch = target then (
        a.(0) <- p;
        Hashtbl.replace idx2ch 0 ch;
        flag := true
      ) else (
        let i' = if !flag then !i else !i+1 in
        a.(i') <- p;
        Hashtbl.replace idx2ch i' ch
      );
      incr i
    )
  ) map;

  let a = Array.sub a 0 !i in
  bfs m n idx2ch ch2p2pos onet !dst (!occ,a,!one)
