use std::cmp::{max,min};

fn read_until<I: Iterator<Item=std::io::Result<u8>>>(next: &[u8], it: &mut I) -> Vec<u8> {
  it.by_ref().map(|c| c.unwrap()).take_while(|c| !next.contains(c)).collect::<Vec<u8>>()
}

macro_rules! read[
  () => {{
    use std::io::Read;
    use std::str::{FromStr, from_utf8};
    let stdin = std::io::stdin();
    let mut stdin = stdin.lock().bytes();
    let v = read_until(b"\t\r\n ", &mut stdin);
    FromStr::from_str(from_utf8(&v).unwrap()).unwrap()
  }}
];

fn run(n: usize, pref: Vec<usize>) -> (bool, Vec<u8>) {
  let mut f = 0;
  let mut g = 0;
  let mut a: Vec<u8> = (0..n).map(|_| 0).collect();
  let mut b = vec![0; n];
  if pref[0] != n {
    return (false, a);
  }
  for i in 1..n {
    if i < g && pref[i-f] != g-i {
      let mn = min(pref[i-f], g-i);
      if mn != pref[i] {
        return (false, a);
      }
    } else {
      if pref[i] > n-i {
        return (false, a);
      }
      f = i;
      g = max(g, f);
      while g-f < pref[i] {
        if (b[g] & 1 << a[g-f]) != 0 {
          return (false, a);
        }
        a[g] = a[g-f];
        g += 1;
      }
      if g < n {
        b[g] |= 1 << a[g-f];
        let mut ok = false;
        for i in 0..4 {
          if (b[g] & 1 << i) == 0 {
            ok = true;
            a[g] = i;
            break;
          }
        }
        if ! ok {
          return (false, a);
        }
      }
    }
  }
  (true, a)
}

fn main() {
  for _ in 0..read![] {
    let n = read![];
    let mut pref = vec![0; n];
    for i in 0..n {
      pref[i] = read![];
    }
    let (ok, a) = run(n, pref);
    if ! ok {
      println!("Impossible");
    } else {
      for i in 0..n {
        print!("{}", "ACGT".as_bytes()[a[i] as usize] as char);
      }
      println!("");
    }
  }
}
