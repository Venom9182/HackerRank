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

let length xs =
  let rec go xs n =
    match xs with
    | [] -> n
    | x::xs' -> go xs' (n+1)
  in
  go xs 0

let () =
  let xs = read_lines 0 in
  length xs |> string_of_int |> print_endline
