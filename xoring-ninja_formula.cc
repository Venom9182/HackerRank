#include <cstdio>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int MOD = 1000000007;

int main()
{
  for (int cc = ri(); cc--; ) {
    int n = ri(), s = 0;
    REP(i, n)
      s |= ri();
    REP(i, n-1)
      s = (2*s)%MOD;
    printf("%d\n", s);
  }
}
