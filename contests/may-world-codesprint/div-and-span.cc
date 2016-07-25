// There are Catalan[X] ways to place brackets, 2*X+1 positions to place parentheses
// Catalan's convolution
#include <iostream>
#include <type_traits>
using namespace std;

#define REP1(i, n) for (remove_cv<remove_reference<decltype(n)>::type>::type i = 1; i <= (n); i++)

const long X = 100000, Y = 200, Z = 2*(X+Y), MOD = 1000000007;
long fac[Z+1];

long inv(long x)
{
  long r = 1;
  for (; x > 1; x = MOD%x)
    r = r * (MOD-MOD/x) % MOD;
  return r;
}

int main()
{
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  fac[0] = 1;
  REP1(i, Z)
    fac[i] = fac[i-1] * i % MOD;
  long cases, m, n;
  for (cin >> cases; cases--; ) {
    cin >> m >> n;
    long base = fac[2*(n+m)] * inv(fac[n]) % MOD * inv(fac[2*(n+m)-n]) % MOD * (2*m+1) % MOD * inv(n+m*2+1) % MOD,
         catalan = fac[2*m] * inv(fac[m]) % MOD * inv(fac[m+1]) % MOD;
    cout << catalan * base % MOD * fac[m] % MOD * fac[n] % MOD << '\n';
  }
}
