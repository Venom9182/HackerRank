#include <algorithm>
#include <cstdio>
#include <set>
using namespace std;
typedef long long ll;
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

ll a[100000];
multiset<ll> s;

void go(int i, int c, ll sum)
{
  if (! c)
    s.erase(s.find(sum));
  else
    for (; i >= 0; i--)
      go(i, c-1, sum+a[i]);
}

int main()
{
  for (int cc = ri(); cc--; ) {
    int n = ri(), k = ri();
    char c;
    ll x;
    s.clear();
    for(;;) {
      int g = scanf("%lld%c", &x, &c);
      s.insert(x);
      if (c == '\n' || g != 2) break;
    }
    a[0] = *s.begin()/k;
    s.erase(s.begin());
    FOR(i, 1, n) {
      a[i] = *s.begin()-(k-1)*a[0];
      if (i < n-1)
        go(i, k-1, a[i]);
    }
    REP(i, n)
      printf("%lld%c", a[i], i == n-1 ? '\n' : ' ');
  }
}
