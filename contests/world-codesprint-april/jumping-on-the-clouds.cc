#include <algorithm>
#include <cstdio>
using namespace std;

#define REP(i, n) for (decltype(n) i = 0; i < (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100;
int a[100];

int main()
{
  int n = ri();
  REP(i, n)
    a[i] = ri() ? n : i ? min(i ? a[i-1] : n, i > 1 ? a[i-2] : n) + 1 : 0;
  printf("%d\n", a[n-1]);
}
