let is_lower c =
  'a' <= c && c <= 'z'

type ast =
  | Lit of char
  | Star of ast
  | Cat of ast*ast
  | Or of ast*ast

module Parser = struct
  type state = Ret of ast | Cont of char list * ast list

  let parse re =
    let isp_tbl = Hashtbl.create 10 in
    let icp_tbl = Hashtbl.create 10 in
    List.iter (fun (c,x) -> Hashtbl.replace isp_tbl c x)
      ['\x00',0; '(',1; '|',3; '%',5; '*',7; ')',7];
    List.iter (fun (c,x) -> Hashtbl.replace icp_tbl c x)
      ['\x00',0; ')',1; '|',2; '%',4; '*',6; '(',6];

    let n = String.length re in
    let rec go ops vs i =
      let implicit_cat = 0 < i && i < n && (re.[i] = '(' || is_lower re.[i]) &&
        (re.[i-1] <> '(' && re.[i-1] <> '|') in
      let incoming implicit_cat ops vs =
        let ic = if implicit_cat then '%' else if i = n then '\x00' else re.[i] in
        if is_lower ic then
          Cont (ops, Lit ic::vs)
        else
          let icp = Hashtbl.find icp_tbl ic in
          let rec pop_go (op::ops' as ops) vs =
            if Hashtbl.find isp_tbl op > icp then
              match op with
              | '*' ->
                  let x::vs' = vs in
                  pop_go ops' (Star x::vs')
              | '%' ->
                  let y::x::vs' = vs in
                  pop_go ops' (Cat (x,y)::vs')
              | '|' ->
                  let y::x::vs' = vs in
                  pop_go ops' (Or (x,y)::vs')
              | c ->
                  Printf.printf "+ c: %c %c\n" op ic;
                  ops ,vs
            else
              ops, vs
          in
          let (op::ops' as ops), vs = pop_go ops vs in
          if Hashtbl.find isp_tbl op = icp then (
            if ic = '\x00' then
              Ret (List.hd vs)
            else
              Cont (ops', vs)
          ) else
            Cont (ic::ops, vs)
      in
      match incoming implicit_cat ops vs with
      | Ret _ as ret -> ret
      | Cont (ops,vs) ->
          if not implicit_cat then
            go ops vs (i+1)
          else
            let Cont (ops,vs) = incoming false ops vs in
            go ops vs (i+1)
    in
    let Ret ret = go ['\x00'] [] 0 in
    ret
end

let generate len =
  let rec go = function
    | Lit lit ->
        let a = Array.make (len+1) "#" in
        a.(1) <- String.make 1 lit;
        a
    | Star x ->
        let b = go x in
        let a = Array.make (len+1) "#" in
        a.(0) <- "";
        for i = 1 to len do
          let rec fill j =
            if j > 0 then
              if b.(j) <> "#" && a.(i-j) <> "#" then
                a.(i) <- a.(i-j) ^ b.(j)
              else
                fill (j-1)
          in
          fill i
        done;
        a
    | Cat (x,y) ->
        let b = go x and c = go y in
        let a = Array.make (len+1) "#" in
        for i = 0 to len do
          for j = 0 to len-i do
            if a.(i+j) = "#" && b.(i) <> "#" && c.(j) <> "#" then
              a.(i+j) <- b.(i) ^ c.(j)
          done
        done;
        a
    | Or (x,y) ->
        let b = go x in
        let c = go y in
        Array.init (len+1) (fun i -> if b.(i) <> "#" then b.(i) else c.(i))
  in
  go

let () =
  let len = read_int () in
  let re = read_line () in
  let ast = Parser.parse re in
  let a = generate len ast in
  let s = a.(len) in
  print_endline (if s <> "#" then s else "NIL")
