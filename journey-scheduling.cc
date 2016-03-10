#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

typedef long long ll;
#define REP(i, n) for (int i = 0; i < (n); i++)
#define pb push_back

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100000;
vector<int> e[N];
int s[N], ss[N], far[N];

void dfs(int u, int p)
{
  for (int v: e[u])
    if (v != p) {
      dfs(v, u);
      if (s[v]+1 > ss[u]) {
        ss[u] = s[v]+1;
        if (ss[u] > s[u])
          swap(ss[u], s[u]);
      }
    }
}

void dfs2(int u, int p, int up)
{
  far[u] = max(s[u], up);
  for (int v: e[u])
    if (v != p)
      dfs2(v, u, max(s[v]+1 == s[u] ? ss[u] : s[u], up) + 1);
}

int main()
{
  int n = ri(), m = ri();
  REP(i, n-1) {
    int u = ri()-1, v = ri()-1;
    e[u].pb(v);
    e[v].pb(u);
  }
  dfs(0, -1);
  dfs2(0, -1, 0);
  ll diameter = *max_element(far, far+n);
  while (m--) {
    int x = ri()-1, y = ri();
    printf("%lld\n", (y-1)*diameter+far[x]);
  }
}
