#include <cstdio>
#include <inttypes.h>
using namespace std;

typedef int64_t ll;
#define REP(i, n) for (int i = 0; i < (n); i++)
#define REP1(i, n) for (int i = 1; i <= (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int S = 30+1;
ll c[S][S];

int main()
{
  REP(i, S) {
    c[i][0] = 1;
    REP1(j, i)
      c[i][j] = c[i-1][j-1] + c[i-1][j];
  }
  int cases = ri();
  REP1(cc, cases) {
    int n = ri(), k = ri();
    printf("Case %d: %lld\n", cc, c[n][k-1]);
  }
}
