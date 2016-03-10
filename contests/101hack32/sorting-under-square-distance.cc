#include <algorithm>
#include <cstdio>
#include <utility>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define REP(i, n) for (int i = 0; i < (n); i++)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100000;
int a[N], c[N], emp[N];
pii b[N];

void add(int n, int x)
{
  for (; x < n; x |= x+1)
    emp[x]++;
}

int getSum(int x)
{
  int s = 0;
  for (; x; x &= x-1)
    s += emp[x-1];
  return s;
}

int main()
{
  int n = ri();
  REP(i, n) {
    a[i] = ri();
    b[i] = {a[i], i};
  }
  sort(b, b+n);
  REP(i, n)
    c[a[i] = lower_bound(b, b+n, pii{a[i], i}) - b] = i;
  ll ans = 0;
  ROF(i, 0, n) {
    int j = c[i];
    ans += i-(j-getSum(j));
    add(n, j);
  }
  printf("%lld\n", ans);
}
