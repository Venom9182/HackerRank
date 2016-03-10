use std::cmp::max;
use std::io::stdin;

fn read_line() -> String {
  let mut s = String::new();
  stdin().read_line(&mut s);
  s.trim_right().to_string()
}

fn main() {
  let mut a = vec![vec![0; 6]; 6];
  for i in 0..6 {
    let line = read_line();
    let mut it = line.split(" ");
    for j in 0..6 {
      a[i][j] = it.next().unwrap().parse::<i64>().unwrap();
    }
  }
  let mut mx = std::i64::MIN;
  for i in 1..5 {
    for j in 1..5 {
      mx = max(mx, a[i][j]+a[i-1][j-1]+a[i-1][j]+a[i-1][j+1]+a[i+1][j-1]+a[i+1][j]+a[i+1][j+1]);
    }
  }
  println!("{}", mx);
}
