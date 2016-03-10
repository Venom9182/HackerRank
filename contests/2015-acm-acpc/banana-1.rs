use std::collections::HashMap;
use std::io::stdin;

fn read_i64() -> i64 {
  let mut s = String::new();
  stdin().read_line(&mut s);
  return s.trim_right().parse().unwrap();
}

fn main() {
  let n = read_i64();
  let mut map = HashMap::new();
  for _ in 0..n {
    let mut s = String::new();
    stdin().read_line(&mut s);
    let v: Vec<String> = s.trim_right().split(" = ").map(|x| x.to_string()).collect();
    map.insert(v[0].clone(), v[1].clone());
  }
  for _ in 0..read_i64() {
    let mut s = String::new();
    stdin().read_line(&mut s);
    s = String::new();
    stdin().read_line(&mut s);
    let v: Vec<String> = s.trim_right().split(" ").map(|x| map.get(x).unwrap().clone()).collect();
    println!("{}", v.join(" "));
  }
}
