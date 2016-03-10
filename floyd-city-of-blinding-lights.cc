#include <algorithm>
#include <climits>
#include <cstdio>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 400;
int d[N][N];

int main()
{
  int n = ri(), m = ri();
  REP(i, n) {
    fill_n(d[i], n, INT_MAX/2);
    d[i][i] = 0;
  }
  while (m--) {
    int u = ri()-1, v = ri()-1, w = ri();
    d[u][v] = w;
  }
  REP(k, n)
    REP(i, n)
      REP(j, n)
        d[i][j] = min(d[i][j], d[i][k]+d[k][j]);
  for (m = ri(); m--; ) {
    int u = ri()-1, v = ri()-1;
    printf("%d\n", d[u][v] == INT_MAX/2 ? -1 : d[u][v]);
  }
}
