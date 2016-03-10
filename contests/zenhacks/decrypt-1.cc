#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100;
char a[N+1], b[N+1];

int main()
{
  for (int cc = ri(); cc--; ) {
    scanf("%s%s", a, b);
    int n = strlen(a), ans = n;
    REP(i, 26) {
      int t = 0;
      REP(j, n) {
        int aa = (a[j]-'a'+i)%26, bb = b[j]-'a';
        t += aa != bb;
      }
      ans = min(ans, t);
    }
    printf("%d\n", ans);
  }
}
