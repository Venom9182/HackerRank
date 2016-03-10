#include <algorithm>
#include <cstdio>
using namespace std;

#define REP1(i, n) for (int i = 1; i <= (n); i++)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int D = 20;
int dp[D+1];
#define ROUND(x) (((x)+5)/10*10)

int main()
{
  int n = ri(), d = ri();
  REP1(i, n) {
    int a = ri();
    ROF(j, 0, d)
      dp[j+1] = min(dp[j+1]+a, ROUND(dp[j]+a));
    dp[0] += a;
  }
  printf("%d\n", ROUND(dp[d]));
}
