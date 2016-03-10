#include <algorithm>
#include <cstdio>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); i++)
#define REP1(i, n) for (int i = 1; i <= (n); i++)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100000;
int a[N];

void add(int n, int x)
{
  for (; x < n; x |= x+1)
    a[x]++;
}

int getSum(int x)
{
  int s = 0;
  for (; x; x &= x-1)
    s += a[x-1];
  return s;
}

int main()
{
  ROF(_, 0, ri()) {
    int n = ri();
    long ans = 0;
    fill_n(a, n, 0);
    REP(i, n) {
      int x = ri()-1, y = x+getSum(n-x)-i;
      if (y > 2)
        ans = -1;
      if (~ ans && y > 0) {
        ans += y;
        add(n, n-x);
      }
    }
    if (ans < 0)
      puts("Too chaotic");
    else
      printf("%ld\n", ans);
  }
}
