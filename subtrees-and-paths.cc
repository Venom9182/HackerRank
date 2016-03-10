#include <algorithm>
#include <climits>
#include <cstdio>
#include <vector>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); i++)
#define pb push_back

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100000, NN = 131072;
vector<int> e[N];
int dep[N], par[N], size[N], pre[N], post[N], heavy[N], dlt[2*NN], mx[2*NN];

void apply(int i, int v)
{
  dlt[i] += v;
  mx[i] += v;
}

void untag(int i)
{
  if (i < 0 || NN <= i) return;
  i += NN;
  for (int j, h = 31-__builtin_clz(NN); h; h--)
    if (dlt[j = i >> h]) {
      apply(2*j, dlt[j]);
      apply(2*j+1, dlt[j]);
      dlt[j] = 0;
    }
}

void mconcat(int i)
{
  mx[i] = max(mx[2*i], mx[2*i+1]);
}

void add(int l, int r, int v)
{
  bool lf = false, rf = false;
  untag(l-1);
  untag(r);
  for (l += NN, r += NN; l < r; ) {
    if (l & 1) lf = true, apply(l++, v);
    l >>= 1;
    if (lf) mconcat(l-1);
    if (r & 1) rf = true, apply(--r, v);
    r >>= 1;
    if (rf) mconcat(r);
  }
  for (l--; l >>= 1, r >>= 1; ) {
    if (lf || l == r) mconcat(l);
    if (rf && l < r) mconcat(r);
  }
}

int getMax(int l, int r)
{
  int ret = INT_MIN;
  untag(l-1);
  untag(r);
  for (l += NN, r += NN; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ret = max(ret, mx[l++]);
    if (r & 1) ret = max(ret, mx[--r]);
  }
  return ret;
}

int dfs(int d, int v, int p)
{
  par[v] = p;
  dep[v] = d;
  size[v] = 1;
  for (int u: e[v])
    if (u != p)
      size[v] += dfs(d+1, u, v);
  return size[v];
}

int heavyLight(int v, int p, int chain, int tick)
{
  int prefer = -1;
  pre[v] = tick++;
  heavy[v] = chain;
  for (int u: e[v])
    if (u != p && (prefer < 0 || size[u] > size[prefer]))
      prefer = u;
  if (prefer >= 0) {
    tick = heavyLight(prefer, v, chain, tick);
    for (int u: e[v])
      if (u != p && u != prefer)
        tick = heavyLight(u, v, u, tick);
  }
  return post[v] = tick;
}

int lca(int v, int u)
{
  while (heavy[v] != heavy[u]) {
    if (dep[heavy[v]] > dep[heavy[u]])
      v = par[heavy[v]];
    else
      u = par[heavy[u]];
  }
  return dep[v] < dep[u] ? v : u;
}

int query(int v, int u)
{
  int ret = INT_MIN;
  while (heavy[v] != heavy[u]) {
    ret = max(ret, getMax(pre[heavy[v]], pre[v]+1));
    v = par[heavy[v]];
  }
  return max(ret, getMax(pre[u], pre[v]+1));
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
  heavyLight(0, -1, 0, 0);
  for (int q = ri(); q--; ) {
    char op[9];
    scanf("%s", op);
    int x = ri()-1, y = ri();
    if (*op == 'a')
      add(pre[x], post[x], y);
    else {
      int z = lca(x, --y);
      printf("%d\n", max(query(x, z), query(y, z)));
    }
  }
}
