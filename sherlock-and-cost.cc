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

int main()
{
  for (int cc = ri(); cc--; ) {
    int n = ri(), bb, f = 0, g = 0;
    REP(i, n) {
      int b = ri();
      if (i) {
        int ff = max(f, g+bb-1),
            gg = max(f+b-1, g+b-bb);
        f = ff;
        g = gg;
      }
      bb = b;
    }
    printf("%d\n", max(f, g));
  }
}
