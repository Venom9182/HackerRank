let modulus = 1000000007

let isdigit c = '0' <= c && c <= '9'

let inv x =
  let rec f r x n =
    if n = 0 then
      r
    else
      let x' = Int64.(rem (mul x x) (of_int modulus)) in
      if n mod 2 = 0 then
        f r x' (n/2)
      else
        f Int64.(rem (mul r x) (of_int modulus)) x' (n/2)
  in
  f 1L x (modulus-2)

let () =
  let a = read_line () in
  let isp_tbl = Hashtbl.create 10 in
  let icp_tbl = Hashtbl.create 10 in
  List.iter (fun (c,x) -> Hashtbl.replace isp_tbl c x)
    ['\x00',0; '(',1; '+',3; '-',3; '*',5; '/',5; '=',7; '_',7];
  List.iter (fun (c,x) -> Hashtbl.replace icp_tbl c x)
    ['\x00',0; ')',1; '+',4; '-',4; '*',6; '/',6; '(',9; '=',8; '_',8];

  let n = String.length a in
  let rec go st ops vs i =
    if i < n && isdigit a.[i] then
      let rec f x i =
        if i < n && isdigit a.[i] then
          f (x*10+int_of_char a.[i]-48) (i+1)
        else
          x, i
      in
      let x, i = f 0 i in
      go false ops (x::vs) i
    else
      let ic = if i = n then '\x00' else a.[i] in
      let ic =
        if st && ic = '+' then
          '='
        else if st && ic = '-' then
          '_'
        else
          ic
      in
      try
        let icp = Hashtbl.find icp_tbl ic in
        let rec pop_go (op::ops' as ops) vs =
          if Hashtbl.find isp_tbl op > icp then
            match op with
            | '=' ->
                pop_go ops' vs
            | '_' ->
                let x::vs' = vs in
                pop_go ops' @@ (modulus-x) mod modulus::vs'
            | '+' ->
                let y::x::vs' = vs in
                pop_go ops' @@ (x+y) mod modulus::vs'
            | '-' ->
                let y::x::vs' = vs in
                pop_go ops' @@ (x-y+modulus) mod modulus::vs'
            | '*' ->
                let y::x::vs' = vs in
                pop_go ops' @@ Int64.(rem (mul (of_int x) (of_int y)) (of_int modulus) |> to_int)::vs'
            | '/' ->
                let y::x::vs' = vs in
                pop_go ops' @@ Int64.(rem (mul (of_int x) (of_int y |> inv)) (of_int modulus) |> to_int)::vs'
          else
            ops, vs
        in
        let (op::ops' as ops), vs = pop_go ops vs in
        if Hashtbl.find isp_tbl op = icp then (
          if ic = '\x00' then
            List.hd vs
          else
            go false ops' vs (i+1)
        ) else
          go true (ic::ops) vs (i+1)
      with Not_found ->
        go st ops vs (i+1)
  in
  Printf.printf "%d\n" @@ go true ['\x00'] [] 0
