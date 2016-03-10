#include <algorithm>
#include <cstdio>
#include <cstring>
#include <numeric>
using namespace std;
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100000;
char a[N+1];
int z[N];

void calc_z(int n)
{
  z[0] = n;
  for (int f, g = 0, i = 1; i < n; i++)
    if (i < g && z[i-f] != g-i)
      z[i] = min(z[i-f], g-i);
    else {
      f = i;
      g = max(g, f);
      while (g < n && a[g] == a[g-f])
        g++;
      z[f] = g-f;
    }
}

int main()
{
  for (int cc = ri(); cc--; ) {
    scanf("%s", a);
    int n = strlen(a);
    calc_z(n);
    printf("%lld\n", accumulate(z, z+n, 0ll));
  }
}
