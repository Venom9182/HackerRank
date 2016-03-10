#include <algorithm>
#include <cstdio>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100000;
int a[N], b[N];

int main()
{
  for (int cc = ri(); cc--; ) {
    int n = ri();
    REP(i, n)
      a[i] = ri();
    REP(i, n)
      b[i] = ri();
    int t = -1;
    bool ok = true;
    REP(i, n) {
      int mn = min(a[i], b[i]), mx = max(a[i], b[i]);
      if (t <= mn)
        t = mn;
      else if (t <= mx)
        t = mx;
      else {
        ok = false;
        break;
      }
    }
    puts(ok ? "YES" : "NO");
  }
}
