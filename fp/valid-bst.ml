let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d " (fun x -> x)

type t = Leaf | Node of int * t * t
exception No

let rec add x = function
  | Leaf -> Node (x,Leaf,Leaf)
  | Node (y,l,r) ->
      if x < y then
        match r with
        | Leaf -> Node (y,add x l,Leaf)
        | _ -> raise No
      else
        Node (y,l,add x r)

let () =
  for i = 1 to read_int 0 do
    let n = read_int 0 in
    let rec go n t ans =
      if n = 0 then
        ans
      else
        let x = read_int 0 in
        if ans then
          try
            go (n-1) (add x t) ans
          with No ->
            go (n-1) t false
        else
          go (n-1) t ans
    in
    print_endline (if go n Leaf true then "YES" else "NO")
  done
