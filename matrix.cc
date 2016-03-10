#include <algorithm>
#include <cstdio>
#include <utility>
#include <vector>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define REP(i, n) for (int i = 0; i < (n); i++)
#define eb emplace_back
#define fi first
#define se second

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100000;
bool a[N];
vector<pii> es[N];

pll dfs(int u, int p, int w)
{
  ll f = 0, g = 0;
  for (auto e: es[u])
    if (e.fi != p) {
      pll r = dfs(e.fi, u, e.se);
      f += r.fi;
      g = min(g, r.se-r.fi);
    }
  if (a[u])
    g = f, f += w;
  else {
    g += f;
    f = min(f, g+w);
  }
  return {f, g};
}

int main()
{
  int n = ri(), k = ri();
  REP(i, n-1) {
    int u = ri(), v = ri(), w = ri();
    es[u].eb(v, w);
    es[v].eb(u, w);
  }
  REP(i, k)
    a[ri()] = true;
  printf("%lld\n", dfs(0, -1, 0).se);
}
