let () =
  let n = read_int () in
  let a = Array.init 32 (fun _ -> String.make 63 '_') in
  for i = 0 to 31 do
    for j = 31-i to 31+i do
      a.(i).[j] <- '1'
    done
  done;
  let rec go n (ux,uy as u) (blx,bly as bl) (brx,bry as br) =
    if n > 0 then (
      let bx, by as b = blx, (bly+bry)/2 in
      let lx, ly as l = (ux+blx+1)/2, (bly+by)/2 in
      let rx, ry as r = (ux+brx+1)/2, (bry+by+1)/2 in
      for i = lx to blx do
        for j = ly+i-lx+1 to ry-i+lx-1 do
          a.(i).[j] <- '_'
        done
      done;
      go (n-1) u (lx-1,ly+1) (rx-1,ry-1);
      go (n-1) l bl (bx,by-1);
      go (n-1) r (bx,by+1) br
    )
  in
  go n (0,31) (31,0) (31,62);
  for i = 0 to 31 do
    print_endline a.(i)
  done
