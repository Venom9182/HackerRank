#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>
#include <numeric>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 3000;
bool vis[N];
int g[N][N], d[N];

int main()
{
  int n = ri(), m = ri();
  memset(g, 0x3f, sizeof g);
  while (m--) {
    int u = ri()-1, v = ri()-1, w = ri();
    g[v][u] = g[u][v] = min(g[u][v], w);
  }
  fill_n(d, n, INT_MAX);
  d[0] = 0;
  int ans = 0;
  for(;;) {
    int u = -1;
    REP(i, n)
      if (! vis[i] && (u < 0 || d[i] < d[u]))
        u = i;
    if (u < 0) break;
    ans += d[u];
    vis[u] = true;
    REP(i, n)
      d[i] = min(d[i], g[u][i]);
  }
  printf("%d\n", ans);
}
