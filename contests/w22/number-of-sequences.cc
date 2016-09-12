#include <iostream>
#include <numeric>
#include <type_traits>
using namespace std;

#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define REP1(i, n) for (remove_cv<remove_reference<decltype(n)>::type>::type i = 1; i <= (n); i++)

const long N = 100000, MOD = 1000000007;
long a[N+1], p[N+1], pn[N+1], pr[N+1];

int main()
{
  ios_base::sync_with_stdio(0);
  long n, ans = 1;
  cin >> n;
  iota(p, p+n+1, 0);
  FOR(i, 2, n+1)
    if (p[i] == i)
      for (long j = i*i; j <= n; j += i)
        p[j] = i;
  REP1(i, n) {
    cin >> a[i];
    if (a[i] >= 0)
      for (long j = i; j > 1; ) {
        long pp = p[j], jj = j, c = 1;
        while ((jj /= p[j]) % p[j] == 0) {
          c++;
          pp *= p[j];
        }
        if (c > pn[p[j]]) {
          pn[p[j]] = c;
          pr[p[j]] = a[i]%pp;
        }
        j = jj;
      }
  }
  FOR(i, 2, n+1)
    if (p[i] == i) {
      long pp = i, c = 1;
      while (pp*i <= n) {
        pp *= i;
        c++;
      }
      REP(_, c-pn[i])
        ans = ans*i%MOD;
    }
  cout << ans << endl;
}
