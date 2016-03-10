#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 200, MOD = 1000000007;
char a[N+1];
int s[N][N];

int main()
{
  for (int cc = ri(); cc--; ) {
    scanf("%s", a);
    int n = strlen(a), ans = 0;
    FOR(i, 1, n) {
      reverse(a, a+i);
      REP(j, i)
        ROF(k, i, n) {
          s[j][k] = (j ? s[j-1][k] : 0) + (k+1 < n ? s[j][k+1] : 0);
          if (a[j] == a[k])
            ++s[j][k] %= MOD;
          else if (j && k+1 < n)
            (s[j][k] -= s[j-1][k+1]) %= MOD;
        }
      (ans += s[i-1][i] - (i+1 < n ? s[i-1][i+1] : 0)) %= MOD;
      reverse(a, a+i);
    }
    (ans += MOD) %= MOD;
    printf("%d\n", ans);
  }
}
