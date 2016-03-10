#include <algorithm>
#include <cstdio>
#include <cstdlib>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); i++)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100, X = 1000;
int a[N], dp[X], d[N], q[N];

int main()
{
  int cc = ri();
  while (cc--) {
    int n = ri(), m = ri(), l = ri();
    REP(i, n)
      a[i] = ri();
    sort(a, a+n);
    fill_n(dp, X, l+1);
    dp[0] = 0;
    REP(i, m) {
      int c = ri(), v = ri();
      ROF(j, v, X)
        dp[j] = min(dp[j], dp[j-v]+c);
    }
    fill_n(d, n, -1);
    d[0] = 0;
    q[0] = 0;
    for (int fr = 0, re = 1; fr < re; fr++) {
      int v = q[fr];
      REP(u, n)
        if (d[u] < 0 && dp[abs(a[v]-a[u])] <= l) {
          d[u] = d[v]+1;
          q[re++] = u;
        }
    }
    printf("%d\n", d[n-1]);
  }
}
