#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

#define ALL(x) (x).begin(), (x).end()
#define REP(i, n) for (int i = 0; i < (n); i++)
#define pb push_back

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 1000;
vector<int> e[N], acc[N];
bool g[N][N];

bool check(int v, int u)
{
  for (int x: acc[v])
    for (int y: acc[u])
      if (g[x][y])
        return true;
  return false;
}

int dfs(int v, int p)
{
  int dp = 0;
  acc[v].assign(1, v);
  vector<int> ch;
  for (int u: e[v])
    if (u != p) {
      dp += dfs(u, v);
      if (check(v, u)) dp++;
      else ch.pb(u);
    }
  bool gg[10][10] = {};
  int f[1<<10] = {}, nn = ch.size(), opt = 0, optc = 0;
  REP(i, nn)
    REP(j, nn)
      if (i != j)
        gg[i][j] = check(ch[i], ch[j]);
  REP(mask, 1 << nn) {
    REP(i, nn)
      if (mask & 1 << i)
        REP(j, nn)
          if (mask & 1 << j && gg[i][j])
            f[mask] = max(f[mask], f[mask-(1<<i)-(1<<j)] + 1);
    if (f[mask] > opt)
      optc = 0, opt = f[mask];
    if (f[mask] == opt)
      optc |= (1 << nn) - 1 - mask;
  }
  dp += opt;
  REP(i, nn)
    if (optc & 1 << i)
      copy(ALL(acc[ch[i]]), back_inserter(acc[v]));
  return dp;
}

int main()
{
  for (int cases = ri(); cases--; ) {
    int n = ri();
    REP(i, n) {
      e[i].clear();
      fill_n(g[i], n, false);
    }
    REP(i, n-1) {
      int v = ri()-1, u = ri()-1;
      e[v].pb(u);
      e[u].pb(v);
    }
    int m = ri();
    REP(i, m) {
      int v = ri()-1, u = ri()-1;
      g[v][u] = g[u][v] = true;
    }
    printf("%d\n", dfs(0, -1));
  }
}
