#include <algorithm>
#include <climits>
#include <cstdio>
#include <utility>
using namespace std;

typedef pair<int, int> pii;
#define REP(i, n) for (int i = 0; i < (n); i++)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )
#define fi first
#define se second

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 150000;
pii a[N];

int main()
{
  for (int cases = ri(); cases--; ) {
    int n = ri(), k = ri(), dp[9+2] = {};
    REP(i, n) {
      a[i].fi = ri();
      a[i].se = ri();
    }
    dp[k+1] = INT_MAX;
    sort(a, a+n);
    ROF(i, 0, n)
      REP(j, k+1)
        dp[j] = max(dp[j], min(a[i].fi, dp[j+1]) - a[i].se);
    printf("%d\n", dp[0]);
  }
}
