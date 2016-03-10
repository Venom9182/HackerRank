#include <algorithm>
#include <cstdio>
using namespace std;

#define REP1(i, n) for (int i = 1; i <= (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

int main()
{
  int cc = ri();
  while (cc--) {
    int n = ri(), x = ri(), y = ri(), f = 0;
    if (y == 1)
      REP1(i, n)
        printf("%d%c", i+(i>=x), i == n ? '\n' : ' ');
    else {
      REP1(i, n-1)
        printf("%d ", i);
      printf("%d\n", max(x, n));
    }
  }
}
