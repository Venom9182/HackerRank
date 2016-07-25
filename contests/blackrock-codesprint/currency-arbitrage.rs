use std::io::stdin;
use std::f64;

fn read_line() -> String {
  let mut s = String::new();
  let _ = stdin().read_line(&mut s);
  s.trim_right().to_string()
}

fn read_isize() -> isize {
  read_line().parse().unwrap()
}

fn main() {
  for _ in 0..read_isize() {
    let line = read_line();
    let mut it = line.split(" ");
    let a = it.next().unwrap().parse::<f64>().unwrap();
    let b = it.next().unwrap().parse::<f64>().unwrap();
    let c = it.next().unwrap().parse::<f64>().unwrap();
    println!("{}", ((1./a/b/c-1.)*100000.).floor().max(0.));
  }
}
