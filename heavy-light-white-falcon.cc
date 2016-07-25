#include <algorithm>
#include <iostream>
#include <type_traits>
#include <vector>
using namespace std;

#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

const long N = 50000, NN = 65536;
long chain[N], dep[N], dfn[N], par[N], tick;
long mx[2*NN];
vector<long> adj[N];

long dfs(long u, long p)
{
  long size = 1, maxs = 0;
  par[u] = p;
  chain[u] = -1;
  for (long v: adj[u])
    if (v != p) {
      dep[v] = dep[u]+1;
      long s = dfs(v, u);
      size += s;
      if (s > maxs)
        maxs = s, chain[u] = v;
    }
  return size;
}

void hld(long u, long p, long top)
{
  dfn[u] = tick++;
  if (chain[u] >= 0) {
    hld(chain[u], u, top);
    for (long v: adj[u])
      if (v != p && v != chain[u])
        hld(v, u, v);
  }
  chain[u] = top;
}

long get_max(long l, long r)
{
  long ans = 0;
  for (l += NN, r += NN; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ans = max(ans, mx[l++]);
    if (r & 1) ans = max(ans, mx[--r]);
  }
  return ans;
}

int main()
{
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  long n, q, op, u, v;
  cin >> n >> q;
  REP(i, n-1) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  dfs(0, -1);
  hld(0, -1, 0);
  while (q--) {
    cin >> op >> u >> v;
    if (op == 1) {
      long i = dfn[u]+NN;
      mx[i] = v;
      while (i >>= 1)
        mx[i] = max(mx[2*i], mx[2*i+1]);
    } else {
      long ans = 0;
      while (chain[u] != chain[v]) {
        if (dep[chain[u]] > dep[chain[v]]) {
          ans = max(ans, get_max(dfn[chain[u]], dfn[u]+1));
          u = par[chain[u]];
        } else {
          ans = max(ans, get_max(dfn[chain[v]], dfn[v]+1));
          v = par[chain[v]];
        }
      }
      if (dep[u] > dep[v])
        ans = max(ans, get_max(dfn[v], dfn[u]+1));
      else
        ans = max(ans, get_max(dfn[u], dfn[v]+1));
      cout << ans << '\n';
    }
  }
}
