#include <algorithm>
#include <cstdio>
#include <stack>
#include <vector>
using namespace std;

#define ALL(x) (x).begin(), (x).end()
#define REP(i, n) for (int i = 0; i < (n); i++)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )
#define pb push_back

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100000, P = 15;
int dfn[N], bcc[N], tick, nbcc, cnt[N][P+1], par[N], ans[N], th;
vector<int> e[N], ee[N];

int edgeBiconnected(int u, int p)
{
  static stack<int> S;
  int low = tick++;
  bool back = false;
  S.push(u);
  dfn[u] = low;
  for (auto v: e[u])
    if (dfn[v] == -1) {
      int low2 = edgeBiconnected(v, u);
      low = min(low, low2);
    } else {
      if (v == p && ! back) {
        back = true;
        continue;
      }
      low = min(low, dfn[v]);
    }
  if (low == dfn[u]) {
    int w, c = 0;
    do {
      w = S.top();
      S.pop();
      bcc[w] = nbcc;
      c++;
    } while (w != u);
    fill_n(cnt[nbcc], th+1, c);
    nbcc++;
  }
  return low;
}

void dfs(int u, int p)
{
  par[u] = p;
  for (int v: ee[u])
    if (v != p) {
      dfs(v, u);
      REP(i, th)
        cnt[u][i+1] += cnt[v][i];
    }
}

int main()
{
  int n = ri(), m = ri();
  th = ri();
  while (m--) {
    int u = ri()-1, v = ri()-1;
    e[u].pb(v);
    e[v].pb(u);
  }

  fill_n(dfn, n, -1);
  REP(i, n)
    if (dfn[i] < 0)
      edgeBiconnected(i, -1);
  REP(i, n)
    for (int v: e[i])
      if (bcc[i] != bcc[v]) {
        ee[bcc[i]].pb(bcc[v]);
        ee[bcc[v]].pb(bcc[i]);
      }
  REP(i, n) {
    sort(ALL(ee[i]));
    ee[i].erase(unique(ALL(ee[i])), ee[i].end());
  }
  fill_n(par, nbcc, -1);
  dfs(0, -1);
  REP(u, n) {
    int s = cnt[u][th], p = u;
    ROF(i, 0, th) {
      if (par[p] < 0) break;
      s += cnt[par[p]][i] - (i ? cnt[p][i-1] : 0);
      p = par[p];
    }
    ans[u] = s;
  }
  REP(i, n)
    printf("%d\n", ans[bcc[i]]-1);
}
