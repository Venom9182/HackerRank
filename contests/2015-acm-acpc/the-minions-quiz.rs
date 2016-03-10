use std::io::stdin;

fn read_line() -> String {
  let mut s = String::new();
  stdin().read_line(&mut s);
  s.trim_right().to_string()
}

fn read_usize() -> usize {
  read_line().parse().unwrap()
}

fn main() {
  for _ in 0..read_usize() {
    let mut line = read_line();
    let mut line2 = read_line();
    let mut it = line.split(" ");
    let m: usize = it.next().unwrap().parse().unwrap();
    let n: usize = it.next().unwrap().parse().unwrap();
    it = line2.split(" ");
    let mut x: usize = it.next().unwrap().parse().unwrap();
    for i in 0..m+n {
      let y = it.next().unwrap().parse().unwrap();
      if i < m {
        x &= y;
      } else {
        x |= y;
      }
    }
    println!("{}", x);
  }
}
