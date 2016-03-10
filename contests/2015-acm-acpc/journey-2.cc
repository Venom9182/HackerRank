use std::cmp::min;
use std::io::stdin;

fn read_line() -> String {
  let mut s = String::new();
  stdin().read_line(&mut s);
  s.trim_right().to_string()
}

fn read_usize() -> usize {
  read_line().parse().unwrap()
}

const MOD: usize = 1000000007;

fn main() {
  for _ in 0..read_usize() {
    let line = read_line();
    let mut it = line.split(" ");
    let n = it.next().unwrap().parse::<usize>().unwrap();
    let k = min(n, it.next().unwrap().parse::<usize>().unwrap());
    let mut a = vec![0; n+1];
    let mut s = vec![0; n+2];
    let mut two = 1;
    for i in 0..k+1 {
      a[i] = two;
      s[i+1] = (s[i]+a[i]) % MOD;
      two = two*2 % MOD;
    }
    for i in k+1..n+1 {
      a[i] = (MOD+s[i]-s[i-k]) % MOD;
      s[i+1] = (s[i]+a[i]) % MOD;
    }
    println!("{}", a[n]);
  }
}
