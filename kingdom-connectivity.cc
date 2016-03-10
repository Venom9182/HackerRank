#include <algorithm>
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

const int N = 10000, MOD = 1000000000;
vector<int> e[N], ee[N];
bool vis0[N], vis1[N], vis[N];
int n, memo[N];

void dfs(vector<int> e[], bool vis[], int u)
{
  vis[u] = true;
  for (int v: e[u])
    if (! vis[v])
      dfs(e, vis, v);
}

int postorder(int u)
{
  if (~ memo[u])
    return memo[u];
  int ans = 0;
  vis[u] = true;
  if (u == n-1)
    ans = 1;
  else {
    for (int v: e[u])
      if (vis0[v] && vis1[v]) {
        if (vis[v])
          throw 0;
        ans = (ans+postorder(v))%MOD;
      }
  }
  vis[u] = false;
  return memo[u] = ans;
}

int main()
{
  n = ri();
  int m = ri();
  REP(i, m) {
    int u = ri()-1, v = ri()-1;
    e[u].pb(v);
    ee[v].pb(u);
  }
  dfs(e, vis0, 0);
  dfs(ee, vis1, n-1);
  fill_n(memo, n, -1);
  try {
    printf("%d\n", postorder(0));
  } catch (...) {
    puts("INFINITE PATHS");
  }
}
