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

let rec filter pred = function
  | [] -> []
  | x::xs ->
      if pred x then
        x::filter pred xs
      else
        filter pred xs

let () =
  let x::xs = read_lines 0 |> List.map int_of_string in
  filter ((>) x) xs |> List.map string_of_int |> String.concat "\n" |> print_endline
