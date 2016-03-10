#include <cmath>
#include <cstdio>
#include <map>
#include <utility>
using namespace std;

typedef long long ll;
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) for (int i = 0; i < (n); i++)
#define fi first
#define se second

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100000;
int p;
ll xs[N], ys[N];

struct Line
{
  ll x, y, dx, dy;
  Line(int i, int j) {
    x = xs[i];
    y = ys[i];
    dx = xs[j]-xs[i];
    dy = ys[j]-ys[i];
    if (dx < 0 || ! dx && dy < 0)
      dx *= -1, dy *= -1;
  }
  bool on(int i) const {
    return dx*(ys[i]-y) == dy*(xs[i]-x);
  }
  bool operator<(const Line &o) const {
    ll t = dx*o.dy-dy*o.dx;
    return t ? t < 0 : dx*(o.y-y)-dy*(o.x-x) < 0;
  }
};

bool f(int l, int h, map<Line, int> &ls)
{
  if (h-l < 2) return true;
  if (h-l < 10) {
    FOR(i, l, h)
      FOR(j, i+1, h)
        ++ls[Line(i, j)];
    for (auto &line: ls)
      line.se = (1+sqrt(1+8*line.se))/2;
  } else {
    int m = l+h >> 1;
    map<Line, int> ls2;
    f(l, m, ls);
    f(m, h, ls2);
    for (auto &line: ls)
      FOR(i, m, h)
        line.se += line.fi.on(i);
    for (auto &line: ls2)
      if (! ls.count(line.fi)) {
        FOR(i, l, m)
          line.se += line.fi.on(i);
        ls[line.fi] = line.se;
      }
  }
  for (auto i = ls.begin(); i != ls.end(); )
    if (100*i->se < p*(h-l))
      i = ls.erase(i);
    else
      ++i;
  return ls.size();
}

int main()
{
  int n = ri();
  p = ri();
  REP(i, n) {
    xs[i] = ri();
    ys[i] = ri();
  }
  map<Line, int> ls;
  printf("%spossible\n", f(0, n, ls) ? "" : "im");
}
