use std::collections::HashSet;
use std::io::stdin;

fn read_line() -> String {
  let mut s = String::new();
  stdin().read_line(&mut s);
  s.trim_right().to_string()
}

fn read_usize() -> usize {
  read_line().parse().unwrap()
}

const LOGN: usize = 14;

fn clog2(x: usize) -> usize {
  let mut r = 0;
  while 1 << r < x {
    r += 1;
  }
  r
}

struct Z {
  es: Vec<Vec<usize>>,
  vs: HashSet<usize>,
  fenwick: Vec<i32>,
  pre: Vec<usize>,
  post: Vec<usize>,
  par: Vec<Vec<usize>>,
}

impl Z {
  fn dfs(&mut self) {
    let mut st = vec![(0, 0)];
    let mut tick = 0;
    let n = self.es.len();
    while ! st.is_empty() {
      let mut u = st.pop().unwrap();
      if u.1 == 0 {
        self.pre[u.0] = tick;
        tick += 1;
      }
      if u.1 < self.es[u.0].len() && self.es[u.0][u.1] == self.par[0][u.0] {
        u.1 += 1;
      }
      if u.1 < self.es[u.0].len() {
        st.push((u.0, u.1+1));
        let v = self.es[u.0][u.1];
        self.par[0][v] = u.0;
        st.push((v, 0));
      } else {
        self.post[u.0] = tick;
      }
    }
  }

  fn add(&mut self, mut x: usize, v: i32) {
    while x < self.fenwick.len() {
      self.fenwick[x] += v;
      x |= x+1;
    }
  }

  fn getSum(&self, mut x: usize) -> i32 {
    let mut s = 0;
    while x > 0 {
      s += self.fenwick[x-1];
      x &= x-1;
    }
    s
  }

  fn isRoot(&self, x: usize) -> bool {
    (self.getSum(self.post[x]) - self.getSum(self.pre[x])) as usize == self.vs.len()
  }

  fn new() {
    let n = read_usize();
    let logn = clog2(n-1)+1;
    let mut z = Z{es: vec![vec![]; n],
                  vs: HashSet::new(),
                  fenwick: vec![0; n],
                  pre: vec![0; n],
                  post: vec![0; n],
                  par: vec![vec![!0; n]; logn]};
    for _ in 1..n {
      let line = read_line();
      let mut sp = line.split(" ");
      let u = sp.next().unwrap().parse::<usize>().ok().unwrap();
      let v = sp.next().unwrap().parse::<usize>().ok().unwrap();
      z.es[u].push(v);
      z.es[v].push(u);
    }
    z.dfs();
    for j in 1..logn {
      for i in 0..n {
        z.par[j][i] =
          if z.par[j-1][i] == !0 { !0 }
        else { z.par[j-1][z.par[j-1][i]] };
      }
    }
    for _ in 0..read_usize() {
      let line = read_line();
      let mut sp = line.split(" ");
      let op = sp.next().unwrap();
      let x = sp.next().unwrap().parse::<usize>().ok().unwrap();
      if op == "+" {
        z.vs.insert(x);
        let px = z.pre[x];
        z.add(px, 1);
      } else {
        z.vs.remove(&x);
        let px = z.pre[x];
        z.add(px, -1);
      }
      match z.vs.iter().next() {
        None =>
          println!("-1"),
        Some(v) => {
          let mut v: usize = *v;
          if ! z.isRoot(v) {
            for i in (0..logn).rev() {
              if z.par[i][v] != !0 && ! z.isRoot(z.par[i][v]) {
                v = z.par[i][v];
              }
            }
            v = z.par[0][v];
          }
          println!("{}", v);
        }
      }
    }
  }
}

fn main() {
  for _ in 0..read_usize() {
    Z::new();
  }
}
