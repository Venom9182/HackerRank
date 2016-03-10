#include <algorithm>
#include <climits>
#include <cstdio>
#include <inttypes.h>
#include <vector>
using namespace std;

typedef int64_t ll;
#define ALL(x) (x).begin(), (x).end()
#define REP(i, n) for (int i = 0; i < (n); i++)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100000, NN = 131072;
int ans[N], it[2*NN];
struct Vec
{
  int x, y;
  Vec operator-(const Vec &o) const {
    return {x - o.x, y - o.y};
  }
  ll det(const Vec &o) const {
    return ll(x) * o.y - ll(y) * o.x;
  }
} a[N];
vector<Vec> seg[2*NN];

ll highest(Vec s, int j)
{
  const vector<Vec> &hull = seg[j];
  if (hull.empty())
    return LLONG_MIN;
  int &i = it[j];
  while (i+1 < hull.size() && s.det(hull[i+1]) > s.det(hull[i]))
    i++;
  return s.det(hull[i]);
}

int main()
{
  for (int cases = ri(); cases--; ) {
    int n = ri();
    REP(i, n) {
      a[i].x = ri();
      a[i].y = ri();
    }
    int nn = 1;
    while (nn < n)
      nn *= 2;
    REP(i, n)
      seg[nn+i].push_back(a[i]);
    ROF(i, 1, nn) {
      auto &hull = seg[i];
      hull = seg[2*i];
      for (auto p: seg[2*i+1]) {
        while (hull.size() > 1 && (hull.back()-hull[hull.size()-2]).det(p-hull[hull.size()-2]) >= 0)
          hull.pop_back();
        hull.push_back(p);
      }
    }
    fill_n(it, 2*nn, 0);
    vector<int> q(n-1);
    iota(ALL(q), 0);
    sort(ALL(q), [&](int i, int j) {
      return (a[i+1]-a[i]).det(a[j+1]-a[j]) < 0;
    });
    for (int i: q) {
      ans[i] = 0;
      auto s = a[i+1]-a[i];
      ll thr = s.det(a[i+1]);
      int j = nn+i+1;
      for (; j; j >>= 1)
        if (j%2 == 0 && highest(s, j+1) > thr) {
          j++;
          while (j < nn)
            if (highest(s, 2*j) > thr)
              j *= 2;
            else
              j = 2*j+1;
          ans[i] = j-nn;
          break;
        }
    }
    REP(i, n-1)
      printf("%d%c", ans[i], i == n-2 ? '\n' : ' ');
    REP(i, 2*nn)
      vector<Vec>().swap(seg[i]);
  }
}
