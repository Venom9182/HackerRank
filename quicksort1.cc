#include <algorithm>
#include <cstdio>
using namespace std;
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 1000;
int a[N];

int inplace_stable_partition(int a[], int n, int p)
{
  if (n == 1)
    return a[0] < p;
  int m = n/2, i = inplace_stable_partition(a, m, p), j = inplace_stable_partition(a+m, n-m, p);
  rotate(a+i, a+m, a+m+j);
  return i+j;
}

int main()
{
  int n = ri();
  REP(i, n) a[i] = ri();
  inplace_stable_partition(a, n, a[0]);
  REP(i, n) printf("%d%c", a[i], i == n-1 ? '\n' : ' ');
}
