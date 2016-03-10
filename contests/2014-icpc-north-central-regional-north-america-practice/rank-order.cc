#include <algorithm>
#include <cstdio>
#include <utility>
#include <vector>
using namespace std;

typedef pair<int, int> pii;
#define REP(i, n) for (int i = 0; i < (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 1000000;
pii a[N], b[N];

int main()
{
  int cases = 0, n;
  while (scanf("%d", &n) == 1) {
    REP(i, n)
      a[i] = {ri(), i};
    REP(i, n)
      b[i] = {ri(), i};
    sort(a, a+n, greater<pii>());
    sort(b, b+n, greater<pii>());
    int ans = 0;
    REP(i, n)
      if (a[i].second != b[i].second) {
        ans = i+1;
        break;
      }
    printf("Case %d: ", ++cases);
    if (ans) printf("%d\n", ans);
    else puts("agree");
  }
}
