#include <algorithm>
#include <iostream>
#include <numeric>
#include <type_traits>
using namespace std;

#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define REP1(i, n) for (remove_cv<remove_reference<decltype(n)>::type>::type i = 1; i <= (n); i++)

const long N = 10, D = 100, M = 300, MOD = 1000000007;

int main()
{
  long cases, n, m, a[N], d[N], b[D], c[D], s[M+1], t[M+1], binom[M+1][M+1] = {};
  REP(i, M+1) {
    binom[i][0] = 1;
    REP1(j, i)
      binom[i][j] = (binom[i-1][j-1] + binom[i-1][j]) % MOD;
  }
  for (cin >> cases; cases--; ) {
    cin >> n >> m;
    REP(i, n) {
      cin >> a[i];
      a[i]--;
    }
    fill_n(s, m+1, 0);
    s[0] = 1;
    REP(i, n) {
      cin >> d[i];
      fill_n(b, d[i], 0);
      b[a[i]] = 1;
      fill_n(t, m+1, 0);
      REP(j, m+1) {
        long x = accumulate(b, b+d[i], 0L) % MOD;
        FOR(k, j, m+1)
          (t[k] += binom[k][j]*s[k-j]%MOD*x) %= MOD;
        if (j == m) break;
        REP(k, d[i])
          c[k] = ((k ? b[k-1] : 0) + (k+1 < d[i] ? b[k+1] : 0)) % MOD;
        copy_n(c, d[i], b);
      }
      copy_n(t, m+1, s);
    }
    cout << s[m] << '\n';
  }
}
