#include <iostream>
#include <type_traits>
using namespace std;

#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

const long M = 500000, MOD = 1000000007;
long inv[M+1];

int main()
{
  long cases, n, m;
  inv[1] = 1;
  FOR(i, 2, M+1)
    inv[i] = (MOD-MOD/i)*inv[MOD%i]%MOD;
  for (cin >> cases; cases--; ) {
    cin >> m >> n;
    long sum = 0, t = 1, invn = inv[n];
    REP(i, m-n)
      t = t*n%MOD;
    REP(i, m-n+1) {
      sum = (sum+t)%MOD;
      t = t*invn%MOD * (n-1)%MOD * (n+i)%MOD*inv[i+1]%MOD;
    }
    cout << sum << endl;
  }
}
