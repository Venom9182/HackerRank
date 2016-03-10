#include <algorithm>
#include <cstdio>
using namespace std;

typedef long long ll;
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) for (int i = 0; i < (n); i++)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 150, MOD = 1000000009;
ll catalan[N];
int a[N], f[N][N], g[N][N];

int inv(int x)
{
  int r = 1;
  for (; x > 1; x = MOD%x)
    r = ll(MOD/x) * -r % MOD;
  return r;
}

int main()
{
  catalan[0] = 1;
  FOR(i, 1, N)
    catalan[i] = catalan[i-1] * (4*i-2) % MOD * inv(i+1) % MOD;
  for (int cc = ri(); cc--; ) {
    int n = ri(), alpha = ri(), beta = ri();
    REP(i, n)
      a[i] = ri();
    sort(a, a+n);
    ROF(i, 0, n)
      FOR(j, i, n) {
        int ff = 0, gg = 0;
        FOR(k, i, j+1) {
          ff = (ff + catalan[j-k] * catalan[k-i] % MOD * a[k] + catalan[j-k] * (k ? g[i][k-1] : 0) + catalan[k-i] * (k+1 < n ? g[k+1][j] : 0)) % MOD;
          gg = (gg + catalan[j-k] * (k ? f[i][k-1] : 0) + catalan[k-i] * (k+1 < n ? f[k+1][j] : 0)) % MOD;
        }
        f[i][j] = ff;
        g[i][j] = gg;
      }
    printf("%lld\n", ((ll(f[0][n-1]) * alpha - ll(g[0][n-1]) * beta) % MOD + MOD) % MOD);
  }
}
