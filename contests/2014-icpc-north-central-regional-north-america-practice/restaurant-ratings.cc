#include <algorithm>
#include <cstdio>
using namespace std;

typedef long long ll;
#define REP(i, n) for (int i = 0; i < (n); i++)
#define FOR(i, a, b) for (int i = (a); i < (b); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int S = 30+15, M = 15;
ll c[S][M];

int main()
{
  REP(i, S) {
    c[i][0] = 1;
    FOR(j, 1, min(M, i+1))
      c[i][j] = c[i-1][j-1] + c[i-1][j];
  }
  int cases = 0, n, a[M];
  while (n = ri()) {
    int s = 0;
    ll ans = 0;
    REP(i, n)
      s += a[i] = ri();
    REP(i, s)
      ans += c[i+n-1][n-1];
    REP(i, n-1) {
      REP(j, a[i])
        ans += c[s-j+n-2-i][n-2-i];
      s -= a[i];
    }
    printf("Case %d: %lld\n", ++cases, ans+1);
  }
}
