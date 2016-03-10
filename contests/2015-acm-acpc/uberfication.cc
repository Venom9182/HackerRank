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

fn main() {
  for _ in 0..read_usize() {
    let line = read_line();
    let mut it = line.split(" ");
    let n = it.next().unwrap().parse::<usize>().unwrap();
    let m = it.next().unwrap().parse::<usize>().unwrap();
    let mut es = vec![vec![]; n];
    for _ in 0..m {
      let line = read_line();
      let mut it = line.split(" ");
      let u = it.next().unwrap().parse::<usize>().unwrap()-1;
      let v = it.next().unwrap().parse::<usize>().unwrap()-1;
      es[u].push(v);
      es[v].push(u);
    }

    let mut cnt = vec![1; n];
    let mut sum = vec![0; n];
    let mut dfn = vec![!0; n];
    let mut low = vec![!0; n];
    let mut par = vec![!0; n];
    let mut st = vec![];
    let mut tick = 0;
    let mut ans = 0;
    for i in 0..n {
      if dfn[i] == !0 {
        st.push((i, 0));
        par[i] = !0;
        while ! st.is_empty() {
          let (u, mut c) = st.pop().unwrap();
          if c == 0 {
            dfn[u] = tick;
            low[u] = tick;
            tick += 1;
          }
          if c < es[u].len() && es[u][c] == par[u] {
            c += 1;
          }
          if c < es[u].len() {
            st.push((u, c+1));
            let v = es[u][c];
            if dfn[v] == !0 {
              par[v] = u;
              st.push((v, 0));
            } else {
              low[u] = min(low[u], dfn[v]);
            }
          } else {
            let p = par[u];
            if p != !0 {
              low[p] = min(low[p], low[u]);
              if dfn[u] == low[u] {
                ans += sum[p]*cnt[u]+(sum[u]+cnt[u])*cnt[p];
                cnt[p] += cnt[u];
                sum[p] += sum[u]+cnt[u];
              }
            }
          }
        }
      }
    }
    println!("{}", ans);
  }
}
