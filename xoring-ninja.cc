#include <cstdio>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); i++)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100000, MOD = 1000000007;
int a[N];

int main()
{
  for (int cc = ri(); cc--; ) {
    int n = ri(), s = 0;
    REP(i, n)
      a[i] = ri();
    ROF(k, 0, 30) {
      int z0 = 1, z1 = 0, t;
      REP(i, n)
        if (a[i] >> k & 1)
          t = (z0+z1)%MOD, z0 = z1 = t;
        else
          z0 = 2*z0%MOD, z1 = 2*z1%MOD;
      s = (s*2LL+z1)%MOD;
    }
    printf("%d\n", s);
  }
}
