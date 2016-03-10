#include <algorithm>
#include <cstdio>
using namespace std;

typedef long long ll;
#define REP(i, n) for (int i = 0; i < (n); i++)

const int N = 100000;
unsigned a[N], b[N];
ll c[N], d[N], e[N];

ll getSum(ll fenwick[], int x)
{
  ll s = 0;
  for (; x; x &= x-1)
    s += fenwick[x-1];
  return s;
}

void set(ll fenwick[], int x, ll y)
{
  y -= getSum(fenwick, x+1) - getSum(fenwick, x);
  for (; x < N; x |= x+1)
    fenwick[x] += y;
}

int main()
{
  int n;
  scanf("%d", &n);
  REP(i, n)
    scanf("%u", a+i);
  copy_n(a, n, b);
  sort(b, b+n);
  REP(i, n) {
    int x = lower_bound(b, b+n, a[i]) - b;
    set(c, x, 1);
    set(d, x, getSum(c, x));
    set(e, x, getSum(d, x));
  }
  printf("%lld\n", getSum(e, N));
}
