#include <algorithm>
#include <cstdio>
#include <cstring>
#include <utility>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); i++)
#define fi first
#define se second

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 150, M = 3000;
int a[N][N][N];
pair<int, pair<int, int>> e[M];

int main()
{
  int cc = ri();
  while (cc--) {
    int n = ri(), m = ri(), q = ri();
    memset(a, 0x3f, sizeof a);
    REP(i, n)
      a[i][i][0] = 0;
    REP(i, m) {
      int v = ri()-1, u = ri()-1, w = ri();
      e[i] = {w, {v, u}};
    }
    sort(e, e+m);
    REP(i, m)
      REP(j, n)
        REP(k, n-1)
          a[j][e[i].se.se][k+1] = min(a[j][e[i].se.se][k+1], a[j][e[i].se.fi][k]+e[i].fi);
    while (q--) {
      int v = ri()-1, u = ri()-1, w = min(ri()+1, n), ans = *min_element(a[v][u], a[v][u]+w);
      printf("%d\n", ans < 0x3f3f3f ? ans : -1);
    }
  }
}
