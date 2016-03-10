#include <algorithm>
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

ll rl()
{
  ll x;
  scanf("%lld", &x);
  return x;
}

const int N = 50, MOD = 1000000007;
const int dx[] = {-1,-1,-1,0,1,1,1,0}, dy[] = {-1,0,1,1,1,0,-1,-1};
int a[N][N][10], b[N][N][9];

int main()
{
  int cc = ri();
  while (cc--) {
    int n = ri(), m = ri(), s = ri(), x = ri()-1, y = ri()-1;
    REP(i, n)
      REP(j, m)
        fill_n(a[i][j], 10, 0);
    a[x][y][8] = 1;
    while (s--) {
      REP(i, n)
        REP(j, m) {
          REP(d, 8) {
            int ii = i+dx[d], jj = j+dy[d];
            if (unsigned(ii) < n && unsigned(jj) < m) {
              int t = ((ll)a[i][j][8]-a[i][j][9]+a[i][j][d]+MOD)%MOD;
              (b[ii][jj][8] += t) %= MOD;
              (b[ii][jj][d] += t) %= MOD;
            }
          }
        }
      REP(i, n)
        REP(j, m) {
          REP(d, 8) {
            a[i][j][d] = b[i][j][d];
            b[i][j][d] = 0;
          }
          a[i][j][9] = a[i][j][8];
          (a[i][j][8] += b[i][j][8]) %= MOD;
          b[i][j][8] = 0;
        }
    }
    ll ans = 0;
    REP(i, n)
      REP(j, m)
        ans = (ans+ll(ri())*a[i][j][8])%MOD;
    printf("%lld\n", ans);
  }
}
