#include <algorithm>
#include <cstdio>
#include <utility>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define fi first
#define se second

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

ll rl()
{
  ll x;
  scanf("%lld", &x);
  return x;
}

pii halfEuclid(int a, int b)
{
  int x = 1, y = 0;
  while (b) {
    int q = a/b, t = a%b;
    a = b; b = t;
    t = x-q*y; x = y; y = t;
  }
  return {a, x};
}

int main()
{
  int cc = ri();
  while (cc--) {
    ll n1 = rl();
    int f1 = ri(), d1 = ri();
    ll n2 = rl();
    int f2 = ri(), d2 = ri();
    auto r = halfEuclid(d1, d2);
    int j1 = d2/r.fi, j2 = d1/r.fi,
      i1 = ((f2-f1)/r.fi*r.se%j1+j1)%j1,
      i2 = (f1+ll(d1)*i1-f2)/d2;
    printf("%lld\n", 1 + min((n1-i1-1)/j1, (n2-i2-1)/j2));
  }
}
