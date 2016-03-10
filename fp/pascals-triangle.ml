let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d " (fun x -> x)
let (|>) x f = f x

let rec map2 f xs ys =
  match xs,ys with
  | ([],_) -> []
  | (_,[]) -> []
  | (x::xs',y::ys') -> f x y :: map2 f xs' ys'

let rec pascal xs = function
  | 0 -> ()
  | n ->
      List.map string_of_int xs |> String.concat " " |> print_endline;
      pascal (1::(map2 (+) (List.tl xs) xs)@[1]) (n-1)

let () = read_int 0 |> pascal [1]
