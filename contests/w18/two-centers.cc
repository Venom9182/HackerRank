#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); i++)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )
#define pb push_back

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 5000;
vector<int> e[N];
int n, d[N], q[N], p[N];

int bfs(int u, int cut = -1)
{
  int *fr = q, *re = q;
  fill_n(d, n, -1);
  d[*re++ = u] = 0;
  while (fr < re) {
    u = *fr++;
    for (int v: e[u])
      if (d[v] < 0 && v != cut) {
        d[v] = d[u]+1;
        p[v] = u;
        *re++ = v;
      }
  }
  return re[-1];
}

int main()
{
  n = ri();
  REP(i, n-1) {
    int u = ri()-1, v = ri()-1;
    e[u].pb(v);
    e[v].pb(u);
  }
  int v = bfs(bfs(0));
  ROF(i, 0, d[v]/2)
    v = p[v];
  int u = p[v];
  printf("%d\n", max(d[bfs(bfs(v, u), u)], d[bfs(bfs(u, v), v)]) + 1 >> 1);
}
