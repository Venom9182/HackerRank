#include <algorithm>
#include <climits>
#include <cstdio>
using namespace std;

typedef long long ll;
#define REP(i, n) for (int i = 0; i < (n); i++)
#define REP1(i, n) for (int i = 1; i <= (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 500;
int g[N][N], d[N+1][N];

int gcd(int a, int b)
{
  int t;
  while (b)
    t = a%b, a = b, b = t;
  return a;
}

int main()
{
  int n = ri();
  REP(i, n)
    REP(j, n)
      g[i][j] = ri();
  d[0][0] = 0;
  REP1(k, n)
    REP(i, n) {
      d[k][i] = INT_MAX;
      REP(j, n)
        if (j != i)
          d[k][i] = min(d[k][i], d[k-1][j]+g[j][i]);
    }
  int optp = 1, optq = 0;
  REP(i, n) {
    int pp = 0, qq = 1;
    REP(k, n) { // all d[k][i] are finite
      int p = d[n][i]-d[k][i], q = n-k, x = gcd(p, q);
      p /= x;
      q /= x;
      if (ll(p)*qq > ll(q)*pp)
        pp = p, qq = q;
    }
    if (ll(pp)*optq < ll(qq)*optp)
      optp = pp, optq = qq;
  }
  printf("%d/%d\n", optp, optq);
}
