let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d " (fun x -> x)
let (|>) x f = f x
let flip f x y = f y x

type t = Leaf | Node of int * int * int * t * t

let empty = Leaf

let size = function
  | Leaf -> 0
  | Node (_,s,_,_,_) -> s

let rec add_aux key pri t =
  match t with
  | Leaf ->
      Node (key,1,pri,Leaf,Leaf)
  | Node (x,s,p,l,r) ->
      if key < x then
        let Node (y,s',p',l',r') as left = add_aux key pri l in
        if p' < p then
          Node (y,s+1,p',l',Node(x,s-size l',p,r',r))
        else
          Node (x,s+1,p,left,r)
        else
          let Node (y,s',p',l',r') as right = add_aux key pri r in
          if p' < p then
            Node (y,s+1,p',Node(x,s-size r',p,l,l'),r')
          else
            Node (x,s+1,p,l,right)

let add key = add_aux key (Random.int 0x3fffffff)

let rec kth k (Node (x,_,_,l,r)) =
  let ls = size l in
  if k < ls then
    kth k l
  else if k > ls then
    kth (k-ls-1) r
  else
    x

let median t = kth ((size t-1)/2) t


let rec print_treap d = function
  | Leaf ->
      ()
  | Node (x,s,p,l,r) ->
      print_treap (d+1) l;
      for i = 1 to d do
        print_string "  "
      done;
      Printf.printf "%d(%d,%d)\n" x s p;
      print_treap (d+1) r

let () =
  let n = read_int 0 in
  let a = Array.make (n+1) empty in
  let b = Array.make (n+1) 0 in
  for i = 1 to n do
    let x = read_int 0 in
    if x < 0 then (
      a.(i) <- a.(i+x);
      b.(i) <- b.(i+x)
    ) else (
      a.(i) <- add x a.(i-1);
      b.(i) <- median a.(i)
    );
    print_endline (string_of_int b.(i))
  done

  (*
let () =
  List.fold_left (flip IntTreap.add) IntTreap.empty (List.map Int32.of_int
  [8;12;1;3;10;2;9;0;6;11;7;4;5]) |> print_treap 0
  *)
