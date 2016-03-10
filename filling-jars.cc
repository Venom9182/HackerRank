#include <algorithm>
#include <cstdio>
using namespace std;
typedef long long ll;

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 10000000;
ll fenwick[N];
int c[N];

static inline void add(int n, int x, int y)
{
  for (; x < n; x |= x+1)
    fenwick[x] += y;
}

static inline ll get_sum(int x)
{
  ll s = 0;
  for (; x; x &= x-1)
    s += fenwick[x-1];
  return s;
}

int main()
{
  int n = ri(), m = ri();
  ll s = 0;
  while (m--) {
    int a = ri(), b = ri(), k = ri();
    add(n, a-1, k);
    add(n, b, -k);
  }
  fill_n(c, n, 1);
  for (int x = n; x > 1; x--) {
    int y = x&x-1;
    s += c[x-1]*fenwick[x-1];
    c[y-1] += c[x-1];
  }
  s += c[0]*fenwick[0];
  printf("%lld\n", s/n);
}
