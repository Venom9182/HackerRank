#include <algorithm>
#include <cstdio>
using namespace std;

typedef double ft;
#define REP(i, n) for (int i = 0; i < (n); i++)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100;
struct Vec { ft x, y; } a[N], b[N+2];

ft intercept(Vec A, Vec B, ft y)
{
  return A.x + (y-A.y) / (B.y-A.y) * (B.x-A.x);
}

ft area(int n)
{
  ft ret = 0;
  REP(i, n) {
    int j = (i+n-1)%n;
    ret += b[i].x * b[j].y - b[j].x * b[i].y;
  }
  return ret / 2;
}

int main()
{
  int cases = 0, n;
  ft depth, volume;
  while (scanf("%d", &n) == 1) {
    scanf("%lf%lf", &depth, &volume);
    volume *= 1000 / depth;
    REP(i, n)
      scanf("%lf%lf", &a[i].x, &a[i].y);

    ft lo = 0, hi = 0;
    int bot_left = -1;
    reverse(a, a+n); // -> clockwise
    REP(i, n) {
      if (a[i].y == 0 && (bot_left < 0 || a[i].x < a[bot_left].x))
        bot_left = i;
      hi = max(hi, a[i].y);
    }
    rotate(a, a+bot_left, a+n);
    while (hi-lo > 1e-5) {
      ft mi = (lo+hi)/2;
      int left = 0, right = n-1;
      REP(i, n-2)
        if (a[i].y < mi && mi <= a[i+1].y) {
          left = i;
          break;
        }
      ROF(i, 1, n)
        if (a[i].y < mi && mi <= a[i-1].y) {
          right = i;
          break;
        }
      copy_n(a, left+1, b);
      b[left+1] = {intercept(a[left], a[left+1], mi), mi};
      b[left+2] = {intercept(a[right], a[right-1], mi), mi};
      copy_n(a+right, n-right, b+left+3);
      if (area(left+n-right+3) < volume)
        lo = mi;
      else
        hi = mi;
    }
    printf("Case %d: %.4lf\n", ++cases, lo);
  }
}
