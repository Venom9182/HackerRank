open Lazy

let modulo = 100000007

type 'a inf_list = Cons of 'a * 'a inf_list lazy_t
let read_int _ = Scanf.bscanf Scanf.Scanning.stdib " %d " (fun x -> x)
let (|>) x f = f x
let (%) f g x = g (f x)
let rec rep n f =
  if n = 0 then
    ()
  else (
    f();
    rep (n-1) f
  )

let tl (Cons (_, t)) = force t

let rec map2 f (Cons (h,t)) (Cons (h',t')) =
  Cons (f h h', lazy (map2 f (force t) (force t')))

let rec nth (Cons (h,t)) = function
  | 0 -> h
  | n when n > 0 -> nth (force t) (n-1)

let iter xs =
  let a = Array.make 10001 0 in
  let rec go i (Cons (h,t)) =
    if i = 10001 then
      ()
    else (
      a.(i) <- h;
      go (i+1) (force t)
    )
  in
  go 0 xs;
  a

let rec fibs = Cons (0, lazy (Cons (1, lazy (map2 (fun x y -> (x+y) mod modulo) fibs (tl fibs)))))

let () =
  let n = read_int 0 in
  let a = iter fibs in
  rep n (read_int % Array.get a % string_of_int % print_endline)
