#include <algorithm>
#include <iostream>
#include <numeric>
#include <tuple>
#include <type_traits>
#include <vector>
using namespace std;

typedef tuple<long, long, long> tlll;
#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define ROF(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (b); --i >= (a); )

const long N = 100000, V = N*2-1, LOGV = 18;
tlll e[N];
long c[N], uf[V], dep[V], pre[V], par[LOGV][V], weight[V], distinct[V];
vector<long> adj[V];

long find(long x)
{
  while (uf[x] != x) {
    uf[x] = uf[uf[x]];
    x = uf[x];
  }
  return x;
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

void dfs(long u, long p, long d)
{
  static long tick = 0;
  dep[u] = d;
  pre[u] = tick++;
  par[0][u] = p;
  FOR(i, 1, LOGV)
    par[i][u] = par[i-1][u] < 0 ? -1 : par[i-1][par[i-1][u]];
  for (long v: adj[u])
    if (v != p)
      dfs(v, u, d+1);
}

void dfs2(long u, long p)
{
  for (long v: adj[u])
    if (v != p) {
      dfs2(v, u);
      distinct[u] += distinct[v];
    }
}

int main()
{
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  long n, m, q, u, v, w;
  cin >> n >> m >> q;

  // map types to natural numbers
  vector<long> cc(n);
  REP(i, n) {
    cin >> c[i];
    cc[i] = c[i];
  }
  sort(cc.begin(), cc.end());
  cc.erase(unique(cc.begin(), cc.end()), cc.end());
  vector<vector<long>> col(cc.size());
  REP(i, n) {
    c[i] = lower_bound(cc.begin(), cc.end(), c[i]) - cc.begin();
    col[c[i]].push_back(i);
  }

  // Kruskal's to get the reachability tree
  long node = n;
  REP(i, m) {
    cin >> u >> v >> w;
    u--, v--;
    e[i] = tlll{w, u, v};
  }
  sort(e, e+m);
  iota(uf, uf+n*2-1, 0);
  REP(i, m) {
    tie(w, u, v) = e[i];
    u = find(u);
    v = find(v);
    if (u != v) {
      adj[node].push_back(u);
      adj[node].push_back(v);
      weight[node] = w;
      uf[u] = uf[v] = par[0][u] = par[0][v] = node++;
    }
  }

  // pre-order traversal & set 'par' 'dep'
  fill_n(distinct, n, 1);
  REP(i, node)
    if (uf[i] == i)
      dfs(i, -1, 0);

  // distinct types of all subtrees
  REP(i, cc.size())
    if (col[i].size()) {
      // sort vertices of the same type by pre-order
      sort(col[i].begin(), col[i].end(), [](long x, long y) {
        return pre[x] < pre[y];
      });
      REP(j, col[i].size()-1) {
        u = col[i][j];
        v = col[i][j+1];
        if (find(u) == find(v))
          distinct[lca(u, v)]--;
      }
    }
  REP(i, node)
    if (uf[i] == i)
      dfs2(i, -1);

  while (q--) {
    cin >> u >> v >> w;
    u--, v--;
    long g = find(u) == find(v) ? lca(u, v) : -1;
    if (g >= 0 && distinct[g] < w) {
      ROF(k, 0, LOGV)
        if (par[k][g] >= 0 && distinct[par[k][g]] < w)
          g = par[k][g];
      g = par[0][g];
    }
    cout << (g < 0 ? -1 : weight[g]) << '\n';
  }
}
