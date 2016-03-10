  void real();
  real();
}

#define REP(i, n) for (int i = 0; i < (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

#include <cstdio>
#include <vector>
using namespace std;

void real()
{
  int n = ri(), q = ri();
  vector<vector<int>> a(n);
  REP(i, n) {
    int k = ri();
    a[i].resize(k);
    REP(j, k)
      a[i][j] = ri();
  }
  while (q--) {
    int x = ri(), y = ri();
    printf("%d\n", a[x][y]);
  }
}
