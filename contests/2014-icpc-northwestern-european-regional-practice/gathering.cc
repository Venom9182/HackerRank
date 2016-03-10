#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstdlib>
using namespace std;

typedef long long ll;
#define REP(i, n) for (int i = 0; i < (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100000;

namespace my
{
  ll x[N], y[N], a[N*2], x0, y0, x1, y1, ans;

  ll median(ll a[], int n)
  {
    nth_element(a, a+n/2, a+n);
    return a[n/2];
  }

  void check(int n, ll xx, ll yy)
  {
    if (xx-yy < x0 || x1 < xx-yy || xx+yy < y0 || y1 < xx+yy)
      return;
    ll s = 0;
    REP(i, n)
      s += abs(x[i]-xx)+abs(y[i]-yy);
    ans = min(ans, s);
  }

  void main()
  {

    int n = ri();
    REP(i, n) {
      x[i] = ri();
      y[i] = ri();
    }
    ll d = ri();
    x0 = y0 = LLONG_MIN;
    ans = x1 = y1 = LLONG_MAX;
    REP(i, n) {
      x0 = max(x0, x[i]-y[i]-d);
      x1 = min(x1, x[i]-y[i]+d);
      y0 = max(y0, x[i]+y[i]-d);
      y1 = min(y1, x[i]+y[i]+d);
    }
    if (x0 > x1 || y0 > y1)
      puts("impossible");
    else {
      check(n, median(x, n), median(y, n));
      ll xs[] = {x0, x1}, ys[] = {y0, y1}, p[][2] = {{x0,1},{x1,1},{y0,-1},{y1,-1}};
      REP(i, 16)
        check(n, xs[i&1]+ys[i>>1&1]+(i>>2&1) >> 1, ys[i>>1&1]-xs[i&1]+(i>>3&1) >> 1);
      REP(i, 4) {
        REP(j, n) {
          a[j] = x[j];
          a[n+j] = p[i][0]+p[i][1]*y[j];
        }
        ll xx = median(a, 2*n);
        check(n, xx, p[i][1]*(xx-p[i][0]));
      }
      printf("%lld\n", ans);
    }
  }
}

int main()
{
  my::main();
}
