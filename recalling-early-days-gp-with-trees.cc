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

const int N = 100000, LOGN = 17, MOD = 100711433;
int r, invr, dep[N], par[LOGN][N];
ll d[N], dd[N], path[N];
vector<int> e[N];

void add(ll &x, ll y)
{
  x = (x+y)%MOD;
}

int inv(int x)
{
  ll r = 1;
  for (; x > 1; x = MOD%x)
    r = MOD/x * -r % MOD;
  return r;
}

void dfs(int d, int v, int p)
{
  dep[v] = d;
  par[0][v] = p;
  for (int u: e[v])
    if (u != p)
      dfs(d+1, u, v);
}

void dfs2(int v, int p)
{
  for (int u: e[v])
    if (u != p) {
      dfs2(u, v);
      add(d[v], d[u]*r);
      add(dd[v], dd[u]*invr);
    }
}

void dfs3(int v, int p, ll s)
{
  path[v] = (s+d[v]+dd[v])%MOD;
  for (int u: e[v])
    if (u != p)
      dfs3(u, v, (s+d[v]+dd[v])%MOD);
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

ll power(ll a, int n)
{
  ll r = 1;
  for (; n; n >>= 1, a = a*a%MOD)
    if (n & 1) 
      r = r*a%MOD;
  return r;
}

int main()
{
  int n = ri();
  r = ri() % MOD;
  invr = r ? inv(r) : 0;
  REP(i, n-1) {
    int v = ri()-1, u = ri()-1;
    e[v].pb(u);
    e[u].pb(v);
  }
  dfs(0, 0, -1);
  FOR(j, 1, LOGN)
    REP(i, n)
      par[j][i] = par[j-1][i] < 0 ? -1 : par[j-1][par[j-1][i]];
  int upd = ri(), q = ri();
  while (upd--) {
    int v = ri()-1, u = ri()-1, w = lca(v, u), x = ri();
    if (r) {
      ll xl = power(r, dep[v]-dep[w]), xr = power(r, dep[u]-dep[w]);
      add(d[v], x);
      if (w)
        add(d[par[0][w]], - (x * xl % MOD * r));
      add(dd[u], x * xl % MOD * xr);
      add(dd[w], - x * xl);
    } else
      add(d[v], x);
  }
  dfs2(0, -1);
  dfs3(0, -1, 0);
  while (q--) {
    int v = ri()-1, u = ri()-1, w = lca(v, u);
    printf("%lld\n", ((path[v]+path[u]-path[w]-(w ? path[par[0][w]] : 0)) % MOD + MOD) % MOD);
  }
}
