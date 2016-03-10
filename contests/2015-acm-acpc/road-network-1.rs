use std::cmp::max;
use std::io::stdin;
use std::mem::swap;

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
    let n = read_usize();
    let mut es = vec![vec![]; n];
    let mut down0 = vec![0; n];
    let mut down1 = vec![0; n];
    let mut from0 = vec![!0; n];
    let mut from1 = vec![!0; n];
    for _ in 1..n {
      let line = read_line();
      let mut it = line.split(" ");
      let u = it.next().unwrap().parse::<usize>().unwrap()-1;
      let v = it.next().unwrap().parse::<usize>().unwrap()-1;
      es[u].push(v);
      es[v].push(u);
    }

    let mut st = vec![(0, !0)];
    let mut fr = 0;
    while fr < st.len() {
      let (u, p) = st[fr];
      fr += 1;
      for &v in &es[u] {
        if v != p {
          st.push((v, u));
        }
      }
    }

    let mut ans = 0;
    for &(v, p) in st.iter().rev() {
      ans = max(ans, down0[v]+down1[v]);
      if p != !0 {
        if down0[v]+1 > down1[p] {
          down1[p] = down0[v]+1;
          from1[p] = v;
        }
        if down1[p] > down0[p] {
          swap(&mut down1[p], &mut down0[p]);
          swap(&mut from1[p], &mut from0[p]);
        }
      }
    }
    println!("{}", n-1-ans);
  }
}
