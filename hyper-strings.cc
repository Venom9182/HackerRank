#include <algorithm>
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

const int N = 100, AB = 10, MOD = 1000000007;
char aa[N+1];
int a[1<<AB], s[N+1][AB];
bool b[1<<AB];

int main()
{
  int n = ri(), m = ri();
  REP(i, n) {
    scanf("%s", aa);
    for (int j = 0; aa[j]; j++)
      a[i] |= 1 << aa[j]-'a';
  }
  sort(a, a+n);
  b[0] = true;
  REP(i, n)
    ROF(j, 0, 1 << __builtin_ctz(a[i]))
      if (b[j])
        b[j | a[i]] = true;
  n = 0;
  FOR(i, 1, 1<<AB)
    if (b[i])
      a[n++] = i;
  
  int ans = 0;
  s[0][AB-1] = 1;
  REP(i, m+1)
    REP(j, AB) {
      (ans += s[i][j]) %= MOD;
      REP(k, n) {
        int pop = __builtin_popcount(a[k]);
        if (i+pop <= m && __builtin_ctz(a[k]) <= j)
          (s[i+pop][31-__builtin_clz(a[k])] += s[i][j]) %= MOD;
      }
    }
  printf("%d\n", ans);
}
