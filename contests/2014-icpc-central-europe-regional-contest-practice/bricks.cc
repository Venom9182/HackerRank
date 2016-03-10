#define __STDC_FORMAT_MACROS
#include <cstdio>
#include <inttypes.h>
#include <utility>
using namespace std;

typedef int64_t ll;
#define REP(i, n) for (int i = 0; i < (n); i++)
#define fi first
#define se second

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100000;
int a[N];

int gcd(int x, int y)
{
  int t;
  while (y)
    t = x%y, x = y, y = t;
  return x;
}

int main()
{
  for (int cases = ri(); cases--; ) {
    int n = ri(), bb = 0, ww = 0;
    REP(i, n) {
      char c;
      a[i] = ri();
      scanf(" %c", &c);
      if (c == 'B')
        bb += a[i];
      else
        ww += a[i], a[i] *= -1;
    }
    if (! bb || ! ww)
      printf("%d\n", bb+ww);
    else {
      int d = gcd(bb, ww);
      ll y = 0;
      int c = 0;
      bb /= d;
      ww /= d;
      REP(i, n) {
        ll t = a[i] > 0 ? ww : bb, x = ll(a[i])*t;
        if ((y<0&&x>0 || y>0&&x<0) && (x > 0 ? y+x >= 0 : y+x <= 0) && (y+x)%t == 0)
          c++;
        y += x;
      }
      printf("%d\n", c);
    }
  }
}
