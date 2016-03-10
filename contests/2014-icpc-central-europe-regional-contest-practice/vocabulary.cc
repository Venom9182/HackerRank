#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) for (int i = 0; i < (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 1000000, MOD = 1000000009;
char a[3][N+1];
int g[28][28][28][4][4];

int main()
{
  REP(xx, 28) REP(yy, 28) REP(zz, 28) {
    int x0 = xx, x1 = xx+1, y0 = yy, y1 = yy+1, z0 = zz, z1 = zz+1;
    if (xx == 27) x0 = 1, x1 = 27;
    if (yy == 27) y0 = 1, y1 = 27;
    if (zz == 27) z0 = 1, z1 = 27;
    FOR(x, x0, x1) FOR(y, y0, y1) FOR(z, z0, z1) REP(i, 4) {
      if ((i & 1 || x <= y) && (i & 2 || y <= z)) {
        int j = i;
        if (x < y) j |= 1;
        if (y < z) j |= 2;
        g[xx][yy][zz][i][j]++;
      }
    }
  }
  for (int cases = ri(); cases--; ) {
    int n = 0, m[3];
    REP(i, 3) {
      scanf("%s", a[i]);
      m[i] = strlen(a[i]);
      n = max(n, m[i]);
    }
    REP(i, 3) {
      REP(j, m[i])
        a[i][j] = a[i][j] == '?' ? 27 : a[i][j]-'a'+1;
      fill(a[i]+m[i], a[i]+n, 0);
    }
    int dp[4] = {}, dp2[4];
    dp[0] = 1;
    REP(i, n) {
      int x = a[0][i], y = a[1][i], z = a[2][i];
      REP(j, 4) {
        dp2[j] = 0;
        REP(k, 4)
          dp2[j] = (dp2[j]+(long long)dp[k]*g[x][y][z][k][j])%MOD;
      }
      copy_n(dp2, 4, dp);
    }
    printf("%d\n", dp[3]);
  }
}
