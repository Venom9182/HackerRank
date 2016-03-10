#include <algorithm>
#include <climits>
#include <cstdio>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

typedef pair<int, int> pii;
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

const int N = 3000;
bool vis[N];
int d[N];
vector<pii> es[N];

void dijkstra(int n, int src)
{
  fill_n(vis, n, false);
  fill_n(d, n, INT_MAX);
  d[src] = 0;
  priority_queue<pii, vector<pii>, greater<pii>> pq;
  pq.emplace(0, src);
  while (! pq.empty()) {
    pii x = pq.top();
    pq.pop();
    if (vis[x.se]) continue;
    vis[x.se] = true;
    for (pii e: es[x.se])
      if (x.fi+e.se < d[e.fi])
        pq.emplace(d[e.fi] = x.fi+e.se, e.fi);
  }
}

int main()
{
  for (int cc = ri(); cc--; ) {
    int n = ri(), m = ri();
    REP(i, n)
      es[i].clear();
    while (m--) {
      int u = ri()-1, v = ri()-1, w = ri();
      es[u].eb(v, w);
      es[v].eb(u, w);
    }
    int s = ri()-1;
    dijkstra(n, s);
    REP(i, n)
      if (i != s)
        printf("%d ", d[i] < INT_MAX ? d[i] : -1);
    puts("");
  }
}
