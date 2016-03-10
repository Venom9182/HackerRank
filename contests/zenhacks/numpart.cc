#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <utility>
#include <vector>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define ALL(x) (x).begin(), (x).end()
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) for (int i = 0; i < (n); i++)
#define mp make_pair
#define se second

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100000, Q = 200000, MOD = 1000000007;
vector<pii> a[N];
int block, inv[Q+1], ans[Q], aa[Q], c[Q+1];
struct B {
  int id, t, p;
  bool operator<(const B &o) const {
    int i = p/block, j = o.p/block;
    return i < j || i == j && t < o.t;
  }
} b[Q];
struct G { char op; int p, v; } g[Q];
int y[Q+1];

int main()
{
  inv[1] = 1;
  FOR(i, 2, Q+1)
    inv[i] = inv[MOD%i]*ll(MOD-MOD/i) % MOD;

  int n = ri(), q = ri(), m = 0;
  block = sqrt(n);
  REP(i, n)
    a[i].emplace_back(-1, 0);

  REP(i, q) {
    char op;
    scanf(" %c", &g[i].op);
    g[i].p = ri()-1;
    if (g[i].op == 'U')
      y[i] = g[i].v = ri();
  }
  y[q] = 0;
  sort(y, y+q+1);
  REP(i, q) {
    if (g[i].op == 'U') {
      aa[i] = g[i].p;
      a[g[i].p].emplace_back(i, lower_bound(y, y+q+1, g[i].v) - y);
    } else {
      aa[i] = -1;
      b[m] = {m, i, g[i].p};
      m++;
    }
  }

  int p = -1, t = -1;
  ll prod = 1;
  sort(b, b+m);
  REP(i, m) {
    for (; b[i].t < t; t--)
      if (0 <= aa[t] && aa[t] <= p) {
        auto it = lower_bound(ALL(a[aa[t]]), mp(t, INT_MIN));
        int x = it->se, y = (it-1)->se;
        prod = prod*inv[c[x]+1]%MOD*(c[x])%MOD;
        c[x]--;
        prod = prod*inv[c[y]+1]%MOD*(c[y]+2)%MOD;
        c[y]++;
      }
    while (t < b[i].t)
      if (0 <= aa[++t] && aa[t] <= p) {
        auto it = lower_bound(ALL(a[aa[t]]), mp(t, INT_MIN));
        int x = (it-1)->se, y = it->se;
        prod = prod*inv[c[x]+1]%MOD*(c[x])%MOD;
        c[x]--;
        prod = prod*inv[c[y]+1]%MOD*(c[y]+2)%MOD;
        c[y]++;
      }
    while (b[i].p < p) {
      int x = upper_bound(ALL(a[p]), mp(t, INT_MAX))[-1].se;
      p--;
      prod = prod*inv[c[x]+1]%MOD*(c[x])%MOD;
      c[x]--;
    }
    while (p < b[i].p) {
      p++;
      int x = upper_bound(ALL(a[p]), mp(t, INT_MAX))[-1].se;
      prod = prod*inv[c[x]+1]%MOD*(c[x]+2)%MOD;
      c[x]++;
    }
    int x = upper_bound(ALL(a[p]), mp(t, INT_MAX))[-1].se;
    ans[b[i].id] = prod * inv[c[x]+1] % MOD;
  }

  REP(i, m)
    printf("%d\n", ans[i]);
}
