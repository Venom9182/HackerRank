#include <cstdio>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int M = 26;
int a[M];

int main()
{
  int n = 0, x = -1, y = -1;
  REP(i, M) {
    a[i] = ri();
    n += a[i];
    if (a[i]) {
      if (x < 0 || a[i] < a[x]) {
        if (x >= 0 && y < 0)
          y = x;
        x = i;
      }
    }
  }
  putchar('a'+x);
  a[x]--;
  n--;
  if (y >= 0) {
    REP(i, M)
      REP(_, a[i])
        putchar('a'+i);
  } else if (a[x] == n)
    REP(_, a[x])
      putchar('a'+x);
  else {
    y = x+1;
    REP(i, a[x]) {
      for (; ! a[y]; y++);
      putchar('a'+x);
      putchar('a'+y);
      a[y]--;
    }
    for (; y < M; y++)
      REP(_, a[y])
        putchar('a'+y);
  }
  puts("");
}
