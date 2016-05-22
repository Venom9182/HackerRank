#include <algorithm>
#include <iostream>
#include <numeric>
#include <set>
#include <tuple>
#include <type_traits>
using namespace std;

typedef tuple<long, long, long> tlll;
#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define ROF(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (b); --i >= (a); )

const long N = 100000, V = N*2-1, LOGV = 18;
tlll e[N];
long uf[V], dep[V], par[LOGV][V], weight[V], cnt[V];
set<long> ts[V];

long find(long x)
{
  while (uf[x] != x) {
    uf[x] = uf[uf[x]];
    x = uf[x];
  }
  return x;
}

long depth(long u)
{
  if (dep[u] >= 0)
    return dep[u];
  return dep[u] = par[0][u] < 0 ? 0 : depth(par[0][u])+1;
}

long lca(long u, long v)
{
  if (dep[v] < dep[u])
    swap(v, u);
  ROF(k, 0, LOGV)
    if (1 << k <= dep[v]-dep[u])
      v = par[k][v];
  if (u == v)
    return u;
  ROF(k, 0, LOGV)
    if (par[k][u] != par[k][v])
      u = par[k][u], v = par[k][v];
  return par[0][u];
}

int main()
{
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  long n, m, q, u, v, w;
  cin >> n >> m >> q;
  iota(uf, uf+n*2-1, 0);
  REP(i, n) {
    cin >> w;
    ts[i].insert(w);
  }
  int node = n;
  fill_n(par[0], 2*n-1, -1);
  REP(i, m) {
    cin >> u >> v >> w;
    u--, v--;
    e[i] = tlll{w, u, v};
  }
  sort(e, e+m);
  REP(i, m) {
    tie(w, u, v) = e[i];
    u = find(u);
    v = find(v);
    if (u != v) {
      if (ts[u].size() < ts[v].size())
        swap(u, v);
      ts[node].swap(ts[u]);
      for (auto x: ts[v])
        ts[node].insert(x);
      ts[v].clear();
      weight[node] = w;
      cnt[node] = ts[node].size();
      uf[u] = uf[v] = par[0][u] = par[0][v] = node++;
    }
  }
  FOR(k, 1, LOGV)
    REP(i, node)
      par[k][i] = par[k-1][i] < 0 ? -1 : par[k-1][par[k-1][i]];
  fill_n(dep, node, -1);
  REP(i, n)
    if (dep[i] < 0)
      depth(i);
  while (q--) {
    cin >> u >> v >> w;
    u--, v--;
    long g = find(u) == find(v) ? lca(u, v) : -1;
    if (g >= 0 && cnt[g] < w) {
      ROF(k, 0, LOGV)
        if (par[k][g] >= 0 && cnt[par[k][g]] < w)
          g = par[k][g];
      g = par[0][g];
    }
    cout << (g < 0 ? -1 : weight[g]) << '\n';
  }
}
