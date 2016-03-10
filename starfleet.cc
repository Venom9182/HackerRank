#include <algorithm>
#include <climits>
#include <cstdio>
#include <map>
#include <utility>
using namespace std;

typedef pair<int, int> pii;
#define REP(i, n) for (int i = 0; i < (n); i++)
#define mp make_pair
#define se second

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 50000, Q = 30000;
pii a[N];
int cnt[N], ct[N+1], mx, ans[Q], B;
struct P
{
  int id, l, h;
  bool operator<(const P &o) const {
    int i = l/B, j = o.l/B;
    return i < j || i == j && h < o.h;
  }
} b[Q];

void add(int i)
{
  ct[cnt[i]]--;
  ct[++cnt[i]]++;
  mx = max(mx, cnt[i]);
}

void remove(int i)
{
  ct[cnt[i]]--;
  ct[--cnt[i]]++;
  if (! ct[mx]) mx--;
}

int main()
{
  map<int, int> ff;
  int n = ri(), q = ri();
  B = max((int)sqrt(double(n)*n/max(q,1)), 1);
  ri();
  REP(i, n) {
    ri();
    int y = ri(), f = ri();
    if (! ff.count(f)) {
      int id = ff.size();
      ff[f] = id;
    }
    a[i] = {y, ff[f]};
  }
  sort(a, a+n);
  REP(i, q) {
    int u = ri(), d = ri();
    ri();
    b[i].id = i;
    b[i].l = lower_bound(a, a+n, mp(d, INT_MIN)) - a;
    b[i].h = upper_bound(a, a+n, mp(u, INT_MAX)) - a;
  }
  sort(b, b+q);

  int l = 0, h = 0;
  REP(i, q) {
    while (l < b[i].l) remove(a[l++].se);
    while (b[i].l < l) add(a[--l].se);
    while (b[i].h < h) remove(a[--h].se);
    while (h < b[i].h) add(a[h++].se);
    ans[b[i].id] = mx;
  }
  REP(i, q)
    printf("%d\n", ans[i]);
}
