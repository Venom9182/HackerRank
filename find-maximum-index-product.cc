#include <algorithm>
#include <cstdio>
using namespace std;

typedef long long ll;
#define REP(i, n) for (int i = 0; i < (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100000;
int a[N], s[N], l[N];

int main()
{
  int n = ri(), m = 0;
  ll ans = 0;
  REP(i, n) {
    a[i] = ri();
    while (m && a[s[m-1]] < a[i])
      ans = max(ans, l[s[--m]]*ll(i+1));
    while (m && a[s[m-1]] == a[i])
      m--;
    l[i] = m ? s[m-1]+1 : 0;
    s[m++] = i;
  }
  printf("%lld\n", ans);
}
