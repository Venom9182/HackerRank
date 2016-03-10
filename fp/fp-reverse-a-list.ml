let (|>) x f = f x

let read_lines _ =
  let rec go acc =
    try
      let line = read_line () in
      go (line::acc)
    with End_of_file ->
      List.rev acc
  in
  go []

let reverse xs =
  let rec go xs ys =
    match xs with
    | [] -> ys
    | x::xs' -> go xs' (x::ys)
  in
  go xs []

let () =
  let xs = read_lines 0 in
  reverse xs |> String.concat "\n" |> print_endline
