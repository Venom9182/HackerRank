#include <algorithm>
#include <climits>
#include <cstdio>
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

const int N = 100000;
struct A
{
  int x, a, b, id;
  bool operator<(const A &o) const {
    return x < o.x;
  }
} a[N];
int rnk[N];

struct Seg
{
  ll mx, dlt;
  Seg *c[2];
  Seg() {}
  Seg(int l, int r) {
    mx = dlt = 0;
    if (l < r-1) {
      int m = l+r >> 1;
      c[0] = new Seg(l, m);
      c[1] = new Seg(m, r);
    }
  }
  void *operator new(size_t) {
    extern struct Seg *allo;
    return allo++;
  }
  ll getMax(int l, int r, int li, int ri) {
    if (li <= l && r <= ri)
      return mx + dlt;
    int m = l+r >> 1;
    ll ret = LLONG_MIN/2;
    if (li < m) ret = max(ret, c[0]->getMax(l, m, li, ri));
    if (m < ri) ret = max(ret, c[1]->getMax(m, r, li, ri));
    return ret + dlt;
  }
  void add(int l, int r, int li, int ri, ll v) {
    if (li <= l && r <= ri)
      dlt += v;
    else {
      int m = l+r >> 1;
      if (li < m) c[0]->add(l, m, li, ri, v);
      if (m < ri) c[1]->add(m, r, li, ri, v);
      mx = max(c[0]->mx + c[0]->dlt, c[1]->mx + c[1]->dlt);
    }
  }
} pool[2*2*N], *allo = pool;

int main()
{
  int n = ri();
  REP(i, n) {
    a[i].x = ri();
    a[i].a = ri();
    a[i].b = ri();
    a[i].id = i;
  }
  sort(a, a+n);
  REP(i, n)
    rnk[a[i].id] = i;
  ll ans = 0;
  auto seg0 = new Seg(0, n); // f(k) + pref[k-1]
  auto seg1 = new Seg(0, n); // f(k) - pref[k]
  REP(i, n) {
    int j = rnk[i];
    ll v = max(max(seg0->getMax(0, n, 0, j+1) + seg1->getMax(0, n, j, j+1),
                   seg1->getMax(0, n, j, n) + seg0->getMax(0, n, j, j+1)),
               0ll) + a[j].a;
    ans = max(ans, v);
    seg0->add(0, n, j, j+1, v);
    if (j+1 < n)
      seg0->add(0, n, j+1, n, a[j].b);
    seg1->add(0, n, j, j+1, v);
    seg1->add(0, n, j, n, - a[j].b);
  }
  printf("%lld\n", ans);
}
