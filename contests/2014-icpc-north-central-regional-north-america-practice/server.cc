#include <cstdio>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); i++)

int main()
{
  int cases = 0, n, t, x;
  while (scanf("%d%d", &n, &t) == 2) {
    int j = 0;
    REP(i, n) {
      scanf("%d", &x);
      if (i == j && x <= t)
        t -= x, j++;
    }
    printf("Case %d: %d\n", ++cases, j);
  }
}
