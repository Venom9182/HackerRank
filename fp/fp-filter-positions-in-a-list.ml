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

let f xs =
  let rec go xs ys =
    match xs with
    | [] | [_] -> List.rev ys
    | _::y::xs' -> go xs' (y::ys)
  in
  go xs []

let () =
  let xs = read_lines 0 in
  f xs |> String.concat "\n" |> print_endline
