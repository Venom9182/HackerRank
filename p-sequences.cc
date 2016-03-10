#include <algorithm>
#include <cstdio>
using namespace std;
typedef long long ll;
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define REP1(i, n) for (int i = 1; i <= (n); i++)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int P = 1000000000, SP = 31624 /*floor(sqrt(P))+2*/, MOD = 1000000007;
int f[2][SP], g[2][SP], cnt[SP];

int main()
{
  int n = ri(), p = ri(), sp = p;
  for (int sq; (sq = (sp+p/sp)/2) < sp; sp = sq);
  REP1(i, sp)
    f[0][i] = i;
  int l = sp;
  ROF(i, 1, sp+1) {
    int t = p/i;
    cnt[i] = t-l;
    g[0][i] = (t-l+g[0][i+1])%MOD;
    l = t;
  }
  REP(i, n-1) {
    int x = i&1, y = i+1&1;
    REP1(j, sp)
      f[y][j] = (ll(f[y][j-1])+f[x][sp]+g[x][j])%MOD;
    ROF(j, 1, sp+1)
      g[y][j] = (g[y][j+1]+ll(cnt[j])*f[x][j])%MOD;
  }
  printf("%d\n", (f[n-1&1][sp]+g[n-1&1][1])%MOD);
}
