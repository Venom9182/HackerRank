#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <utility>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) for (int i = 0; i < (n); i++)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )
#define fi first
#define se second

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100000, Q = 100000, MOD = 1000003;
char s[N+1];
int bs, d, p25 = 1, pref[N+1], cntl[N+1][28], cntr[N+1][28], cnts[N+1];
bool ok[N+1];
ll ans[Q];
struct A {
  int id, l, r;
  bool operator<(const A &o) const {
    int i = l/bs, j = o.l/bs;
    return i < j || i == j && r < o.r;
  }
} a[Q];

struct H {
  int b[MOD], id = 0;
  pair<pii, pii> a[N+1];
  H() { fill_n(b, MOD, -1); }
  pii &operator[](int x) {
    int k = x % MOD;
    for (int i = b[k]; i >= 0; i = a[i].fi.se)
      if (a[i].fi.fi == x)
        return a[i].se;
    a[id] = {{x, b[k]}, {0, 0}};
    b[k] = id;
    return a[id++].se;
  }
} c;

int main()
{
  int p = ri(), q = ri(), po = p, r2 = 0, r5 = 0;
  while (po % 2 == 0)
    po /= 2, r2++, p25 *= 2;
  while (po % 5 == 0)
    po /= 5, r5++, p25 *= 5;
  d = max(r2, r5);
  scanf("%s", s);
  int n = strlen(s), ten = 1;

  pref[n] = 0;
  ROF(i, 0, n) {
    pref[i] = (pref[i+1] + ten * ll(s[i]-'0')) % po;
    ten = ten * 10ll % po;
  }

  // cntl[i][j]: number of a[i..i] a[i..i+1] ... a[i..i+j] divisible by p
  REP(i, n+1) {
    ll t = 0;
    int g = 0;
    REP(j, min(d-1, n-i+1)) {
      t = t * 10 + s[i+j] - '0';
      if (t % p == 0)
        g++;
      cntl[i][j] = g;
    }
  }

  // cntr[i][j]: number of a[i..i] a[i-1..i] ... a[i-j..i] divisible by p
  REP(i, n+1) {
    ll t = 0, ten = 1;
    int g = 0;
    REP(j, min(d-1, i+1)) {
      t = t + ten * (s[i-j] - '0');
      ten *= 10;
      if (t % p == 0)
        g++;
      cntr[i][j] = g;
    }
  }

  // cnts[i]: number of pref[i-d+1..i-1] equals to pref[i]
  if (d > 1)
    REP(i, n+1)
      cnts[i] = count(pref+max(i-d+1, 0), pref+i, pref[i]);

  // ok[i]: a[i-d..i-1] % 25 == 0
  FOR(i, d, n+1) {
    ll t = 0;
    FOR(j, i-d, i)
      t = t * 10 + s[j] - '0';
    ok[i] = t % p25 == 0;
  }

  REP(i, q) {
    a[i].id = i;
    a[i].l = ri()-1;
    a[i].r = ri();
  }
  bs = sqrt(double(n))*1.5;
  sort(a, a+q);
  int l = 0, r = -1;
  ll sum = 0;
  REP(i, q) {
    while (a[i].l < l) {
      l--;
      c[pref[l]].fi++;
      if (l+d <= r && ok[l+d])
        c[pref[l+d]].se++;
      sum += c[pref[l]].se - ! d;
      int t = min(r-l-1, d-2);
      if (t >= 0)
        sum += cntl[l][t];
    }
    while (r < a[i].r) {
      r++;
      if (l <= r-d && ok[r]) {
        c[pref[r]].se++;
        sum += c[pref[r]].fi;
        sum -= cnts[r];
      }
      c[pref[r]].fi++;
      int t = min(r-l-1, d-2);
      if (t >= 0)
        sum += cntr[r-1][t];
    }
    for (; l < a[i].l; l++) {
      int t = min(r-l-1, d-2);
      if (t >= 0)
        sum -= cntl[l][t];
      c[pref[l]].fi--;
      sum -= c[pref[l]].se - ! d;
      if (l+d <= r && ok[l+d])
        c[pref[l+d]].se--;
    }
    for (; a[i].r < r; r--) {
      int t = min(r-l-1, d-2);
      if (t >= 0)
        sum -= cntr[r-1][t];
      c[pref[r]].fi--;
      if (l <= r-d && ok[r]) {
        c[pref[r]].se--;
        sum -= c[pref[r]].fi;
        sum += cnts[r];
      }
    }
    ans[a[i].id] = sum;
  }
  REP(i, q)
    printf("%lld\n", ans[i]);
}
