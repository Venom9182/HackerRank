#include <algorithm>
#include <cstdio>
#include <queue>
#include <set>
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

const int N = 200000;
int d[N];
vector<int> e[N];

void complementBFS(int n, int src)
{
  set<int> x;
  REP(i, n)
    if (i != src)
      x.insert(i);
  fill_n(d, n, -1);
  d[src] = 0;
  queue<int> q;
  q.push(src);
  while (! q.empty()) {
    set<int> y;
    int u = q.front();
    q.pop();
    for (int v: e[u])
      if (d[v] == -1) {
        x.erase(v);
        y.insert(v);
      }
    for (int v: x) {
      d[v] = d[u]+1;
      q.push(v);
    }
    x.swap(y);
  }
}

int main()
{
  for (int cc = ri(); cc--; ) {
    int n = ri(), m = ri();
    REP(i, n)
      e[i].clear();
    while (m--) {
      int u = ri()-1, v = ri()-1;
      e[u].pb(v);
      e[v].pb(u);
    }
    int s = ri()-1;
    complementBFS(n, s);
    REP(i, n)
      if (i != s)
        printf("%d ", d[i]);
    puts("");
  }
}
