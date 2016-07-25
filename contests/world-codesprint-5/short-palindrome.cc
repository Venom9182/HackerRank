#include <cstring>
#include <iostream>
#include <type_traits>
using namespace std;

#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define ROF(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (b); --i >= (a); )

const long N = 1000000, AB = 26, MOD = 1000000007;
char s[N+1];

long inverse(long x)
{
  long r = 1;
  for (; x > 1; x = MOD%x)
    r = r*(MOD-MOD/x)%MOD;
  return r;
}

int main()
{
  cin >> s;
  long n = strlen(s), ans = 0;
  REP(i, n)
    s[i] -= 'a';
  REP(ca, AB) {
    long la = 0, ra = 0, ba[AB] = {}, abba[AB] = {};
    ROF(i, 0, n)
      if (s[i] == ca)
        ra++;
      else
        ba[s[i]] = (ba[s[i]]+ra)%MOD;
    abba[ca] = ra*(ra-1)%MOD*(ra-2)%MOD*(ra-3)%MOD*inverse(24)%MOD;
    REP(i, n)
      if (s[i] == ca)
        la++, ra--;
      else {
        ba[s[i]] -= ra;
        abba[s[i]] = (abba[s[i]]+la*ba[s[i]])%MOD;
      }
    REP(cb, AB)
      ans = (ans+abba[cb])%MOD;
  }
  cout << (ans+MOD)%MOD << endl;
}
