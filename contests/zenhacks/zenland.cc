#include <cstdio>
#include <cstdlib>
#include <utility>
#include <vector>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pll;
#define REP(i, n) for (int i = 0; i < (n); i++)
#define fi first
#define pb push_back
#define se second

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100000;
int a[N];
vector<int> e[N];

pll dfs(int v, int p)
{
  pll r = {a[v], 0};
  for (int u: e[v])
    if (u != p) {
      auto rr = dfs(u, v);
      r.fi += rr.fi;
      r.se += rr.se;
    }
  return {r.fi, r.se+abs(r.fi)};
}

int main()
{
  int n = ri();
  REP(i, n) {
    int x = ri(), y = ri();
    a[i] = x-y;
  }
  REP(i, n-1) {
    int v = ri(), u = ri();
    e[v].pb(u);
    e[u].pb(v);
  }
  printf("%lld\n", dfs(0, -1).se);
}
