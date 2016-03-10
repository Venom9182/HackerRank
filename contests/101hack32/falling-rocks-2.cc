#include <algorithm>
#include <cstdio>
#include <numeric>
using namespace std;

typedef long long ll;
#define REP(i, n) for (int i = 0; i < (n); i++)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int W = 7, S = 1 << W;
ll a[S][S], b[S][S], t[S][S];

void multiply(ll a[][S], ll b[][S], ll mod)
{
  REP(i, S)
    fill_n(t[i], S, 0);
  REP(i, S)
    REP(k, S)
      REP(j, S)
        t[i][j] = (t[i][j] + a[i][k] * b[k][j]) % mod;
  REP(i, S)
    copy_n(t[i], S, a[i]);
}

int main()
{
  int w = ri(), h = ri(), mod = ri();
  REP(i, 1<<w)
    REP(j, 1<<w) {
      int ii = i & ~j;
      REP(k, w-1)
        if (ii & 1 << k && ! (j & 1 << k+1))
          ii |= 1 << k+1;
      ROF(k, 1, w)
        if (ii & 1 << k && ! (j & 1 << k-1))
          ii |= 1 << k-1;
      a[i][ii]++;
    }
  b[1][1] = 1;
  for (; h; h /= 2) {
    if (h & 1)
      multiply(b, a, mod);
    multiply(a, a, mod);
  }
  printf("%lld\n", accumulate(b[1]+1, b[1]+(1<<w), 0ll) % mod);
}
