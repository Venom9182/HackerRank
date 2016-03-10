#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

#define ALL(x) (x).begin(), (x).end()
#define REP(i, n) for (int i = 0; i < (n); i++)
#define pb push_back

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int A = 1 << 15;
vector<int> bag[2*A];

int main()
{
  for (int cc = ri(); cc--; ) {
    REP(i, 2*A)
      bag[i].clear();
    int n = ri(), q = ri();
    REP(i, n)
      for (int x = A+ri(); x; x >>= 1)
        bag[x].pb(i);
    REP(i, 2*A)
      sort(ALL(bag[i]));
    while (q--) {
      int x = ri(), l = ri()-1, r = ri(), i = 1, j = 14, ans = 0;
      for (; j >= 0; j--) {
        i *= 2;
        int c = (x>>j&1)^1;
        auto it = lower_bound(ALL(bag[i+c]), l);
        if (it != bag[i+c].end() && *it < r)
          i += c, ans += 1 << j;
        else
          i += c^1;
      }
      printf("%d\n", ans);
    }
  }
}
