#include <algorithm>
#include <climits>
#include <cstdio>
using namespace std;

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) for (int i = 0; i < (n); i++)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 300;
int dp[N][N];
struct P
{
  int x, y, d;
  bool operator<(const P &o) const {
    return x < o.x;
  }
} a[N+1];

int main()
{
  for (int cases = ri(); cases--; ) {
    int n = ri();
    REP(i, n) {
      a[i].x = ri();
      a[i].y = ri();
      a[i].d = ri();
    }
    a[n].x = 10001;
    a[n].d = -1;
    sort(a, a+n);
    ROF(i, 0, n)
      FOR(j, i, n) {
        int p = n;
        FOR(k, i, j+1)
          if (a[k].y < a[j+1].x && (p == -1 || a[k].d > a[p].d))
            p = k;
        if (p == n)
          dp[i][j] = 0;
        else {
          int l = p, h = p;
          for (; l-1 >= i && a[l-1].x == a[p].x; l--);
          for (; h+1 <= j && a[h+1].x <= a[p].y; h++);
          dp[i][j] = INT_MAX;
          FOR(k, l, h+1)
            dp[i][j] = min(dp[i][j], a[p].d + (k ? dp[i][k-1] : 0) + (k+1 < n ? dp[k+1][j] : 0));
        }
      }
    printf("%d\n", dp[0][n-1]);
  }
}
