use std::cmp::min;

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

fn main() {
  for _ in 0..read![] {
    let n = read![];
    let m = read![];
    let mut es = vec![vec![]; n];
    for _ in 0..m {
      let mut u: usize = read![];
      let mut v: usize = read![];
      u -= 1;
      v -= 1;
      es[u].push(v);
      es[v].push(u);
    }

    let mut cnt = vec![1; n];
    let mut sum = vec![0; n];
    let mut dfn = vec![!0; n];
    let mut low = vec![!0; n];
    let mut par = vec![!0; n];
    let mut st = vec![(0, 0)];
    let mut tick = 0;
    let mut ans = 0;
    par[0] = !0;
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
    println!("{}", ans);
  }
}
