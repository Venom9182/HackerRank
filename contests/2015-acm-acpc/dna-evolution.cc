#include <algorithm>
#include <cstdio>
using namespace std;

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) for (int i = 0; i < (n); i++)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100000;
int pref[N], a[N], b[N];

bool run(int n)
{
  if (pref[0] != n) return false;
  int f = 0, g = 0;
  a[0] = 0;
  fill_n(b, n, 0);
  FOR(i, 1, n)
    if (i < g && pref[i-f] != g-i) {
      if (min(pref[i-f], g-i) != pref[i])
        return false;
    } else {
      if (pref[i] > n-i)
        return false;
      f = i;
      g = max(g, f);
      for (; g-f < pref[i]; g++) {
        if (b[g] & 1 << a[g-f])
          return false;
        a[g] = a[g-f];
      }
      if (g < n) {
        b[g] |= 1 << a[g-f];
        REP(i, 4+1)
          if (! (b[g] & 1 << i)) {
            a[g] = i;
            break;
          }
        if (a[g] == 4)
          return false;
      }
    }
  return true;
}

int main()
{
  ROF(_, 0, ri()) {
    int n = ri();
    REP(i, n)
      pref[i] = ri();
    if (! run(n))
      puts("Impossible");
    else {
      REP(i, n)
        putchar("ACGT"[a[i]]);
      puts("");
    }
  }
}
