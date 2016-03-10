#include <cstdio>
using namespace std;

typedef long long ll;

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

ll pos(int n)
{
  ll s = 0;
  for (int k = 30; k >= 0; k--)
    if (n & 1 << k) {
      n -= 1 << k;
      s += n+1;
      s += k ? ll(k) << k-1 : 0;
    }
  return s;
}

ll neg(int n)
{
  ll s = -32 * ll(n);
  for (int k = 30; k >= 0; k--)
    if (~n >> k & 1) {
      n += 1 << k;
      s += n;
      s -= k ? ll(k) << k-1 : 0;
    }
  return s;
}

int main()
{
  for (int cc = ri(); cc--; ) {
    int a = ri(), b = ri();
    printf("%lld\n", a >= 0 ? pos(b) - (a ? pos(a-1) : 0)
           : b < 0 ? neg(a) - (~ b ? neg(b+1) : 0)
           : neg(a)+pos(b));
  }
}
