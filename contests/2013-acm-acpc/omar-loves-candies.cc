#include <algorithm>
#include <climits>
#include <cstdio>
using namespace std;

typedef long long ll;
#define REP(i, n) for (int i = 0; i < (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 1000;
ll a[N][N];

int main()
{
  int cc = ri();
  while (cc--) {
    int n = ri(), m = ri();
    REP(i, n)
      REP(j, m) {
        a[i][j] = ri();
        if (i) a[i][j] += a[i-1][j];
        if (j) a[i][j] += a[i][j-1];
        if (i && j) a[i][j] -= a[i-1][j-1];
      }
    ll ans = LLONG_MIN;
    REP(i, n)
      REP(j, m) {
        ll t = a[n-1][m-1];
        if (i) t -= a[i-1][m-1];
        if (j) t -= a[n-1][j-1];
        if (i && j) t += a[i-1][j-1];
        ans = max(ans, t);
      }
    printf("%lld\n", ans);
  }
}
