use std::io::stdin;

fn read_line() -> String {
  let mut s = String::new();
  stdin().read_line(&mut s);
  s.trim_right().to_string()
}

fn read_usize() -> usize {
  read_line().parse().unwrap()
}

fn gcd(mut a: usize, mut b: usize) -> usize {
  let mut t;
  while b != 0 {
    t = a % b;
    a = b;
    b = t;
  }
  a
}

fn lcm(a: usize, b: usize) -> usize {
  a / gcd(a, b) * b
}

fn f(a: &mut usize, b: &mut usize) {
  let r = gcd(*a, *b);
  *a /= r;
  *b /= r;
}

fn main() {
  for _ in 0..read_usize() {
    let line = read_line();
    let mut it = line.split(" ");
    let mut a = it.next().unwrap().parse::<usize>().unwrap();
    let mut b = it.next().unwrap().parse::<usize>().unwrap();
    let mut c = it.next().unwrap().parse::<usize>().unwrap();
    let mut d = it.next().unwrap().parse::<usize>().unwrap();
    f(&mut a, &mut b);
    f(&mut c, &mut d);

    let mut p = gcd(a, c);
    let mut q = lcm(b, d);
    f(&mut p, &mut q);
    print!("{}/{} ", p, q);
    p = lcm(a, c);
    q = gcd(b, d);
    f(&mut p, &mut q);
    println!("{}/{}", p, q);
  }
}
