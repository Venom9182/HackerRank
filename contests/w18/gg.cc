#include <cstdio>
using namespace std;

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) for (int i = 0; i < (n); i++)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 3000;
char a[N+1];
int dp[N];

int main()
{
  int n = ri(), m = ri();
  scanf("%s", a);
  dp[0] = 1;
  FOR(i, 1, n)
    if (a[i-1] == 'G')
      ROF(j, 0, i-1)
        (dp[j] += dp[j+1]) %= m;
    else {
      int acc = 0;
      REP(j, i+1) {
        int t = (acc+dp[j])%m;
        dp[j] = acc;
        acc = t;
      }
    }
  int ans = 0;
  REP(i, n)
    (ans += dp[i]) %= m;
  printf("%d\n", ans);
}
