#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )
#define pb push_back
typedef long long ll;

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100000, D = 17, MOD = 1000000007;
vector<int> e[N];
int par[D][N], fenwick[3][N], dep[N], dfnl[N], dfnr[N], tick;

int lca(int u, int v)
{
  if (dep[u] < dep[v]) swap(u, v);
  ROF(i, 0, D)
    if (dep[u]-(1<<i) >= dep[v])
      u = par[i][u];
  if (u == v) return u;
  ROF(i, 0, D)
    if (par[i][u] != par[i][v]) {
      u = par[i][u];
      v = par[i][v];
    }
  return par[0][u];
}

void dfs(int u, int p)
{
  dfnl[u] = tick++;
  for (auto v: e[u])
    if (v != p) {
      par[0][v] = u;
      dep[v] = dep[u]+1;
      dfs(v, u);
    }
  dfnr[u] = tick;
}

void add(int fenwick[], int x, int v)
{
  for (; x < N; x |= x+1)
    (fenwick[x] += v) %= MOD;
}

int get_sum(int fenwick[], int x)
{
  int s = 0;
  for (; x; x &= x-1)
    (s += fenwick[x-1]) %= MOD;
  return s;
}

int get(int u)
{
  int pw = 1, s = 0;
  REP(i, 3) {
    s = (s + ll(pw) * get_sum(fenwick[i], dfnl[u]+1)) % MOD;
    pw = ll(pw)*dep[u]%MOD;
  }
  return (MOD+1ll)/2*s%MOD;
}

int query(int u, int v)
{
  int w = lca(u, v), s = (ll(get(u))+get(v)-get(w))%MOD;
  if (par[0][w] >= 0)
    (s -= get(par[0][w])) %= MOD;
  return s;
}

void upd(int fenwick[], int l, int r, int v)
{
  add(fenwick, l, v);
  add(fenwick, r, -v);
}

void update(int u, int x, int y)
{
  int l = dfnl[u], r = dfnr[u];
  upd(fenwick[2], l, r, y);
  upd(fenwick[1], l, r, (ll(1-2*dep[u])*y+2ll*x)%MOD);
  upd(fenwick[0], l, r, (dep[u]*(dep[u]-1ll)*y+2*(1ll-dep[u])*x)%MOD);
}

int main()
{
  int n = ri(), m = ri(), rt = ri()-1;
  REP(i, n-1) {
    int u = ri()-1, v = ri()-1;
    e[u].pb(v);
    e[v].pb(u);
  }

  tick = 0;
  dep[rt] = 0;
  par[0][rt] = -1;
  dfs(rt, -1);

  FOR(k, 1, D)
    REP(i, n)
      par[k][i] = par[k-1][i] == -1 ? par[k-1][i] : par[k-1][par[k-1][i]];

  while (m--) {
    char op;
    int u, v, w;
    scanf(" %c%d%d", &op, &u, &v);
    u--;
    if (op == 'Q') {
      v--;
      printf("%d\n", (query(u, v)+MOD)%MOD);
    } else {
      w = ri();
      update(u, v, w);
    }
  }
}
