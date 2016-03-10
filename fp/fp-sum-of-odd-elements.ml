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
  let rec go xs sum =
    match xs with
    | [] -> sum
    | x::xs' -> go xs' (if x land 1 = 1 then sum+x else sum)
  in
  go xs 0

let () =
  let xs = read_lines 0 in
  List.map int_of_string xs |> f |> string_of_int |> print_endline
