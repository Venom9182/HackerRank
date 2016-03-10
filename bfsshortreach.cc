#include <algorithm>
#include <cstdio>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

typedef pair<int, int> pii;
#define REP(i, n) for (int i = 0; i < (n); i++)
#define pb push_back

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 3000;
int d[N];
vector<int> es[N];

void bfs(int n, int src)
{
  fill_n(d, n, -1);
  d[src] = 0;
  queue<int> q;
  q.push(src);
  while (! q.empty()) {
    int u = q.front();
    q.pop();
    for (int v: es[u])
      if (d[v] < 0) {
        d[v] = d[u]+1;
        q.push(v);
      }
  }
}

int main()
{
  for (int cc = ri(); cc--; ) {
    int n = ri(), m = ri();
    REP(i, n)
      es[i].clear();
    while (m--) {
      int u = ri()-1, v = ri()-1;
      es[u].pb(v);
      es[v].pb(u);
    }
    int s = ri()-1;
    bfs(n, s);
    REP(i, n)
      if (i != s)
        printf("%d ", ~ d[i] ? 6*d[i] : -1);
    puts("");
  }
}
