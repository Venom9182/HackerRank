#include <algorithm>
#include <cstdio>
#include <utility>
#include <vector>
using namespace std;

#define REP(i, n) for (decltype(n) i = 0; i < (n); i++)
#define REP1(i, n) for (decltype(n) i = 1; i <= (n); i++)
#define FOR(i, a, b) for (long i = (a); i < (b); i++)
#define ROF(i, a, b) for (long i = (b); --i >= (a); )

long rl()
{
  long x;
  scanf("%ld", &x);
  return x;
}

typedef pair<long, long> pll;
const long N = 100000, LOGN = 17, MOD = 1e9+7;
vector<long> es[N];
long dep[N], par[LOGN][N], pre[N], post[N], subtrahend[N+1], tick;
pll minuend[N+1];

pll recur(pll x, long n)
{
  if (n >= 0) {
    long sa = 1, sb = 0, a = 0, b = 1;
    for (; n; n /= 2) {
      if (n & 1) {
        long ta = sa;
        sa = (sa*a+sb*b)%MOD;
        sb = (ta*b+sb*a+sb*b)%MOD;
      }
      long ta = a;
      a = (a*a+b*b)%MOD;
      b = (2*ta*b+b*b)%MOD;
    }
    return {(sa*x.first+sb*x.second)%MOD, (sb*x.first+(sa+sb)*x.second)%MOD};
  } else {
    long sa = 1, sb = 0, a = 0, b = 1;
    for (n = -n; n; n /= 2) {
      if (n & 1) {
        long ta = sa;
        sa = (sa*a+sb*b)%MOD;
        sb = (ta*b+sb*a-sb*b)%MOD;
      }
      long ta = a;
      a = (a*a+b*b)%MOD;
      b = (2*ta*b-b*b)%MOD;
    }
    x.second = (x.second-x.first)%MOD;
    return {(sa*x.first+sb*x.second)%MOD, ((sa+sb)*x.first+sa*x.second)%MOD};
  }
}

pll operator+(const pll& x, const pll& y)
{
  return {x.first+y.first, x.second+y.second};
}

pll operator%(const pll& x, long y)
{
  return {x.first%y, x.second%y};
}

template<class T>
void add(T fenwick[], long n, long i, T x)
{
  for (; i < n; i |= i+1)
    fenwick[i] = (fenwick[i]+x)%MOD;
}

template<class T>
T get_sum(T fenwick[], long i)
{
  T s{};
  for (; i; i &= i-1)
    s = (s+fenwick[i-1])%MOD;
  return s;
}

void dfs(long u, long d, long p)
{
  dep[u] = d;
  par[0][u] = p;
  pre[u] = tick++;
  for (long v: es[u])
    if (v != p)
      dfs(v, d+1, u);
  post[u] = tick;
}

long lca(long u, long v)
{
  if (dep[u] < dep[v])
    swap(u, v);
  ROF(i, 0, LOGN)
    if (dep[u]-dep[v] >= 1 << i)
      u = par[i][u];
  if (u == v)
    return u;
  ROF(i, 0, LOGN)
    if (par[i][u] != par[i][v])
      u = par[i][u], v = par[i][v];
  return par[0][u];
}

long path_sum(long u)
{
  pll t = recur(get_sum(minuend, pre[u]+1), dep[u]);
  return (t.first + get_sum(subtrahend, pre[u]+1)) % MOD;
}

int main()
{
  long n = rl(), m = rl();
  REP1(i, n-1) {
    long p = rl()-1;
    es[p].push_back(i);
  }
  dfs(0, 0, -1);
  FOR(j, 1, LOGN)
    REP(i, n)
      par[j][i] = par[j-1][i] < 0 ? -1 : par[j-1][par[j-1][i]];
  while (m--) {
    char op;
    scanf(" %c", &op);
    long x = rl()-1, y = rl();
    if (op == 'Q') {
      y--;
      long z = lca(x, y), ans = path_sum(x) + path_sum(y) - path_sum(z);
      if (z)
        ans -= path_sum(par[0][z]);
      printf("%ld\n", (ans%MOD+MOD)%MOD);
    } else {
      pll t = recur(pll{0, 1}, y+1); // Fib(y+1)
      add(subtrahend, n, pre[x], - t.first);
      add(subtrahend, n, post[x], t.first);
      t = recur(pll{0, 1}, y-dep[x]+2); // Fib(y-d+2)
      add(minuend, n, pre[x], t);
      add(minuend, n, post[x], pll{- t.first, -t.second});
    }
  }
}
