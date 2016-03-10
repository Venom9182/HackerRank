#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 1500;
char a[N+1], b[N+1];
int q[N];

int main()
{
  for (int cc = ri(); cc--; ) {
    int s = ri(), ans = 0;
    scanf("%s%s", a, b);
    int n = (int)strlen(a);
    FOR(i, 1-n, n) {
      int *fo = q, *re = q;
      FOR(j, max(-i,0), min(n-i,n)) {
        if (a[j] != b[j+i])
          *re++ = j;
        while (re-fo > s+1)
          fo++;
        ans = max(ans, j - (re-fo <= s ? max(-i,0)-1 : *fo));
      }
    }
    printf("%d\n", ans);
  }
}
