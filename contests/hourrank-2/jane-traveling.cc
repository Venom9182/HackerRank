#include <algorithm>
#include <cstdio>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); i++)
#define REP1(i, n) for (int i = 1; i <= (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 500000;
int a[5][2], d[5][N+1], e[5][N+1];

int main()
{
  int n = ri();
  REP(i, 5) {
    REP(j, 2)
      a[i][j] = ri();
    fill_n(d[i], n+1, n+1);
    d[i][0] = 0;
  }
  REP1(i, n)
    REP(j, 5)
      REP(k, 2) {
        int jj = (j+k+1)%5;
        if (a[j][k] <= i && (d[jj][i-a[j][k]] + 1 < d[j][i] ||
                             d[jj][i-a[j][k]] + 1 == d[j][i] && jj < e[j][i])) {
          d[j][i] = d[jj][i-a[j][k]] + 1;
          e[j][i] = jj;
        }
      }
  if (d[0][n] > n)
    puts("-1");
  else {
    bool first = true;
    for (int i = 0; ; ) {
      if (! first) putchar(' ');
      first = false;
      printf("%d", i+1);
      if (! n) break;
      int ii = e[i][n];
      n -= a[i][(ii-i-1+5)%5];
      i = ii;
    }
    puts("");
  }
}
