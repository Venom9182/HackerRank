#include <algorithm>
#include <cstdio>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100000;
int a[N], c[N], f[N+1];

void add(int x, int v)
{
  for (; x < N+1; x |= x+1)
    f[x] += v;
}

int getSum(int x)
{
  int s = 0;
  for (; x; x &= x-1)
    s += f[x-1];
  return s;
}

int main()
{
  int m = ri(), n = ri(), q = ri();
  REP(i, n)
    c[a[i] = ri()]++;
  REP(i, m)
    add(c[i], 1);
  while (q--) {
    int op = ri(), x = ri();
    if (op == 2)
      printf("%d\n", getSum(x));
    else {
      int y = ri();
      add(c[a[x]], -1);
      add(--c[a[x]], 1);
      add(c[y], -1);
      add(++c[y], 1);
      a[x] = y;
    }
  }
}
