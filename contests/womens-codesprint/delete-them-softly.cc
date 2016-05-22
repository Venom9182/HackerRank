#include <algorithm>
#include <climits>
#include <cstdio>
#include <utility>
using namespace std;

#define FOR(i, a, b) for (decltype(b) i = (a); i < (b); i++)
#define REP(i, n) for (decltype(n) i = 0; i < (n); i++)
#define ROF(i, a, b) for (decltype(b) i = (b); --i >= (a); )

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 150;
const long inf = LLONG_MAX/4;
int left[N], right[N];
long a[N], sum[N+1], dp[N][N][N];

int main()
{
  int n = ri();
  REP(i, n) {
    a[i] = ri();
    sum[i+1] = sum[i] + a[i];
  }
  fill_n(left, n, -1);
  fill_n(right, n, n);
  ROF(i, 0, ri()) {
    int u = ri()-1, v = ri()-1;
    if (u < v)
      left[v] = max(left[v], u);
    else
      right[v] = min(right[v], u);
  }
  ROF(i, 0, n) {
    REP(k, n-i)
      dp[i][i][k] = a[i] > 0 ? a[i]*k : 0;
    FOR(j, i+1, n)
      REP(k, n-j) {
        dp[i][j][k] = - inf;
        FOR(p, i, j+1) // 'p' is taken first among i ... j
          if (left[p] < i && j < right[p]) {
            // take 'p' before the trailing 'k' numbers
            dp[i][j][k] = max(dp[i][j][k],
                              sum[p]-sum[i] +
                              (i < p ? dp[i][p-1][k+j-p] : 0) +
                              (p < j ? dp[p+1][j][k] : 0)
                             );
            // take 'p' after the trailing 'k' numbers
            dp[i][j][k] = max(dp[i][j][k],
                              (sum[j+1]-sum[i]) * k +
                              sum[p]-sum[i] +
                              (i < p ? dp[i][p-1][j-p] : 0) +
                              (p < j ? dp[p+1][j][0] : 0)
                             );
          }
      }
  }
  if (dp[0][n-1][0] == - inf)
    puts("Impossible");
  else
    printf("%ld\n", dp[0][n-1][0]);
}
