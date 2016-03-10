#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

const int N = 10000, M = N*2+1;
char a[M], ans[N+1];
int c[26], cc[26];

int main()
{
  gets(a);
  int n = strlen(a);
  reverse(a, a+n);
  REP(i, n) c[a[i]-'a']++;
  REP(i, 26) c[i] /= 2;
  REP(i, n/2)
    REP(x, 26) {
      ans[i] = 'a'+x;
      int p = 0, l = 0;
      REP(j, n)
        if (ans[p] == a[j]) {
          l = j;
          if (++p > i) break;
        }
      if (p <= i) continue;
      copy(c, c+26, cc);
      REP(j, i+1)
        if (--cc[ans[j]-'a'] < 0)
          goto L1;
      FOR(j, l+1, n)
        cc[a[j]-'a']--;
      REP(j, 26)
        if (cc[j] > 0)
          goto L1;
      break;
L1:;
    }
  puts(ans);
}
