#include <cstdio>
using namespace std;

#define REP(i, n) for (long i = 0; i < (n); i++)
#define REP1(i, n) for (long i = 1; i <= (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const long MOD = 1000000007, N = 2000000;
long fac[N+1];

long inv(long x)
{
  long r = 1;
  while (x > 1) {
    r = r*(MOD-MOD/x)%MOD;
    x = MOD%x;
  }
  return r;
}

int main()
{
  fac[0] = 1;
  REP1(i, N)
    fac[i] = fac[i-1]*i%MOD;
  for (int cc = ri(); cc--; ) {
    long n = ri()-1, k = ri()-1, p = 1, q = 1;
    REP(i, k) {
      p = p*(n-i)%MOD;
      q = q*(i+1)%MOD;
    }
    printf("%ld\n", fac[n]*inv(fac[k])%MOD*inv(fac[n-k])%MOD);
  }
}
