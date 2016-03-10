let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d" (fun x -> x)

let () =
  for cc = 1 to read_int 0 do
    let rc = read_int 0 in
    let rb = read_int 0 in
    let ra = read_int 0 in
    let tick = ref 0 in
    let x = Array.make (ra+rb+rc) 0 in
    let nim = Array.init (ra+1) (fun _ -> Array.make_matrix (rb+1) (rc+1) 0) in
    for a = 0 to ra do
      for b = a to rb do
        for c = b to rc do
          incr tick;
          for aa = 0 to a-1 do
            x.(nim.(aa).(b).(c)) <- !tick
          done;
          for bb = 0 to b-1 do
            x.(nim.(min a bb).(bb).(c)) <- !tick
          done;
          for cc = 1 to c-1 do
            x.(nim.(min a cc).(min b cc).(cc)) <- !tick
          done;
          let rec go i =
            if x.(i) = !tick then
              go (i+1)
            else
              i
          in
          nim.(a).(b).(c) <- if a = 0 && b = 0 && c = 1 then 0 else go 0
        done
      done
    done;
    print_endline (if nim.(ra).(rb).(rc) > 0 then "WIN" else "LOSE")
  done
