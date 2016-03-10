let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d " (fun x -> x)
let (|>) x f = f x

module IntMap = Map.Make(struct type t = int let compare = compare end)

type 'a queue = Queue of 'a list * 'a list

let enqueue x (Queue (fr,re)) = Queue (fr,x::re)

let dequeue = function
  | Queue (x::fr,re) -> (x, Queue (fr,re))
  | Queue ([], re) ->
      let (x::fr) = List.rev re in
      (x, Queue (fr,[]))

let empty = Queue ([],[])

let is_empty = function
  | Queue ([],[]) -> true
  | _ -> false

let () =
  let n = read_int 0 in
  let m = read_int 0 in
  let a = Array.init m read_int in
  Array.sort compare a;
  let rec bfs q st =
    if is_empty q then
      (false,st)
    else
      let (cur,q') = dequeue q in
      if cur = n then
        (true,st)
      else
        let (q'',st') = Array.fold_left (fun (q,st) x ->
            let suc = cur*x in
            if suc > n || IntMap.mem suc st then
              (q,st)
            else
              (enqueue suc q, IntMap.add suc cur st)
          ) (q',st) a
        in
        bfs q'' st'
  in

  let (tak,st) = bfs (enqueue 1 empty) (IntMap.singleton 1 0) in
  if tak then
    let rec trace cur acc =
      if cur = 1 then
        1::acc
      else
        let x = IntMap.find cur st in
        trace x (cur::acc)
    in
    List.iter (Printf.printf "%d ") (trace n []);
    print_endline ""
  else
    print_endline "-1"
