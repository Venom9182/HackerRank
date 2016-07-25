#include <algorithm>
#include <climits>
#include <iostream>
#include <type_traits>
using namespace std;

#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

const long N = 5000;
long x[N], w[N], q[N], cost[N][N], dp[N][N];

long chase(long n, long i, long j0, long j1)
{
  long l = j1+1, h = n;
  while (l < h) {
    long m = l+h >> 1;
    if (dp[i][j0]+cost[j0][m] < dp[i][j1]+cost[j1][m])
      l = m+1;
    else
      h = m;
  }
  return l;
}

int main()
{
  long k, n;
  cin >> n >> k;
  REP(i, n)
    cin >> x[i] >> w[i];
  long sumi = 0, sumi2 = 0;
  REP(i, n) {
    long k = i, sumk = sumi, sumk2 = sumi2, sumj = sumi, sumj2 = sumi2;
    FOR(j, i, n) {
      sumj += w[j];
      sumj2 += w[j]*x[j];
      for (; k < j && x[k]-x[i] < x[j]-x[k]; k++) {
        sumk += w[k];
        sumk2 += w[k]*x[k];
      }
      cost[i][j] = sumk2-sumi2-(sumk-sumi)*x[i] + (sumj-sumk)*x[j]-sumj2+sumk2;
    }
    sumi += w[i];
    sumi2 += w[i]*x[i];
    dp[0][i] = sumi*x[i]-sumi2;
  }
  REP(i, k-1) {
    long *hd = q, *tl = q;
    REP(j, n) {
      while (hd+1 < tl && dp[i][*hd]+cost[*hd][j] > dp[i][hd[1]]+cost[hd[1]][j]) hd++;
      dp[i+1][j] = j ? dp[i][*hd]+cost[*hd][j] : 0;
      while (hd <= tl-2 && chase(n, i, tl[-2], tl[-1]) > chase(n, i, tl[-1], j)) tl--;
      *tl++ = j;
    }
  }
  long ans = LONG_MAX, sum = sumi, sum2 = sumi2;
  sumi = sumi2 = 0;
  REP(i, n) {
    ans = min(ans, dp[k-1][i]+sum2-sumi2-(sum-sumi)*x[i]);
    sumi += w[i];
    sumi2 += w[i]*x[i];
  }
  cout << ans << endl;
}
