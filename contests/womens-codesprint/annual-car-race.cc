#include <algorithm>
#include <climits>
#include <cstdio>
#include <type_traits>
using namespace std;

#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define ROF(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (b); --i >= (a); )

long rl()
{
  long x;
  scanf("%ld", &x);
  return x;
}

const long N = 500, inf = LONG_MAX/3;
long g[N][N], d0[N], d1[N];
bool flag[N];

void dijkstra(long n, long src, long d[])
{
  fill_n(flag, n, false);
  fill_n(d, n, inf);
  d[src] = 0;
  for (;; ) {
    long x = -1, bestw = inf;
    REP(i, n)
      if (d[i] < bestw && ! flag[i])
        bestw = d[x = i];
    if (x < 0) break;
    flag[x] = true;
    REP(i, n)
      d[i] = min(d[i], d[x]+g[x][i]);
  }
}

void remove(long n, long src, long sink)
{
  REP(i, n)
    REP(j, n)
      if (d0[i]+d1[j]+g[i][j] == d0[sink])
        g[i][j] = g[j][i] = inf;
}

int main()
{
  ROF(_, 0, rl()) {
    long n = rl(), m = rl(), src = rl(), sink = rl();
    REP(i, n)
      fill_n(g[i], n, inf);
    REP(i, m) {
      long u = rl(), v = rl(), w = rl();
      g[u][v] = g[v][u] = w;
    }
    dijkstra(n, src, d0);
    dijkstra(n, sink, d1);
    remove(n, src, sink);

    dijkstra(n, src, d0);
    dijkstra(n, sink, d1);
    remove(n, src, sink);

    dijkstra(n, src, d0);
    printf("%ld\n", d0[sink] < inf ? d0[sink] : -1);
  }
}
