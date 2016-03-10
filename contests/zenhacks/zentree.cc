#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

typedef long long ll;
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) for (int i = 0; i < (n); i++)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )
#define pb push_back

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 50000, LOGN = 16;
vector<int> e[N];
int dep[N], par[LOGN][N], pre[N], post[N], tick;
ll descendant[LOGN][N], fenwick[N];

void dfs(int d, int v, int p)
{
  pre[v] = tick++;
  par[0][v] = p;
  dep[v] = d;
  for (int u: e[v])
    if (u != p)
      dfs(d+1, u, v);
  post[v] = tick;
}

int lca(int v, int u)
{
  if (dep[v] < dep[u]) swap(v, u);
  ROF(i, 0, LOGN)
    if (1 << i <= dep[v]-dep[u])
      v = par[i][v];
  if (v == u) return v;
  ROF(i, 0, LOGN)
    if (par[i][v] != par[i][u])
      v = par[i][v], u = par[i][u];
  return par[0][v];
}

void add(int n, int x, int y)
{
  for (; x < N; x |= x+1)
    fenwick[x] += y;
}

ll getSum(int x)
{
  ll s = 0;
  for (; x; x &= x-1)
    s += fenwick[x-1];
  return s;
}

ll value(int x)
{
  ll s = getSum(post[x])-getSum(pre[x]);
  REP(d, LOGN) {
    if (! x) break;
    x = par[0][x];
    s += descendant[d][x];
  }
  return s;
}

ll byOrder(int z, int x, int y, int k)
{
  for(;;) {
    if (dep[x] < dep[y]) swap(x, y);
    if (y == z) break;
    if (! k) return min(value(x), value(y));
    int p = min(k-1>>1, dep[y]-dep[z]-1);
    if (p) p = 31-__builtin_clz(p);
    else p = -1;
    if (value(~p ? par[p][x] : x) < value(~p ? par[p][y] : y))
      x = par[0][~p ? par[p][x] : x];
    else
      y = par[0][~p ? par[p][y] : y];
    k -= ~p ? (1<<p)+1 : 1;
  }
  ROF(i, 0, LOGN)
    if (1 << i <= k)
      x = par[i][x], k -= 1 << i;
  return value(x);
}

int main()
{
  int n = ri();
  REP(i, n-1) {
    int v = ri()-1, u = ri()-1;
    e[v].pb(u);
    e[u].pb(v);
  }
  dfs(0, 0, -1);
  FOR(k, 1, LOGN)
    REP(i, n)
      par[k][i] = par[k-1][i] < 0 ? -1 : par[k-1][par[k-1][i]];
  int m = ri();
  while (m--) {
    int op = ri(), x = ri(), y = ri();
    if (op == 1) {
      x--;
      REP(i, LOGN)
        descendant[i][x] += y >> i;
      add(n, pre[x], 2*y);
    } else {
      int z = lca(--x, --y);
      int nv = dep[x]+dep[y]-2*dep[z]+1;
      ll s = byOrder(z, x, y, nv/2);
      if (nv % 2 == 0)
        s = s+byOrder(z, x, y, (nv-1)/2) >> 1;
      printf("%lld\n", s);
    }
  }
}
