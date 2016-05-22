#include <cstdio>
using namespace std;

#define ROF(i, a, b) for (decltype(b) i = (b); --i >= (a); )

long rl()
{
  long x;
  scanf("%ld", &x);
  return x;
}

const long MOD = 1000000007;

long inv(long x)
{
  long r = 1;
  while (x > 1) {
    r = r*(MOD-MOD/x)%MOD;
    x = MOD%x;
  }
  return r;
}

long sum(long n)
{
  return n*(n+1)%MOD*inv(2)%MOD;
}

long sum2(long n)
{
  return n*(n+1)%MOD*(2*n+1)%MOD*inv(6)%MOD;
}

int main()
{
  ROF(_, 0, rl()) {
    long l = rl()%MOD, r = rl()%MOD,
         s = (15*(sum2(r)-sum2(l-1))+4*(sum(r)-sum(l-1))-4*(r-l+1))%MOD;
    printf("%ld\n", (s+MOD)%MOD);
  }
}

/*
 * x^2 = k/3
 * y^2 = k/2
 * z^2 = k/6
 * phi1 = (2 * (sqrt 2 + sqrt 3) - 3) * k
 * phi2 = (8 * sqrt 6) * k^2
 * phi3 = k^2 + k - 1
 * S = 15 k^2 + 4 k - 4
 */
