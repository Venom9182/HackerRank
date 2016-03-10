#include <algorithm>
#include <cstdio>
#include <utility>
#include <vector>
using namespace std;

typedef long long ll;
#define ALL(x) (x).begin(), (x).end()
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) for (int i = 0; i < (n); i++)
#define SIZE(x) (sizeof(x)/sizeof(*x))
#define fi first
#define pb push_back
#define se second

const int N = 100000, NN = 131072, M = 101;
const int MOD[] = {11*101*13*97*17*89, 19*83*23*81*25*29, 31*79*37*73*41, 43*47*49*53*59, 61*64*67*71}, NMOD = SIZE(MOD);
const int PRIME[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101}, NPRIME = SIZE(PRIME);

int belong[M+1], pre[N], post[N];
ll dlt[2*NN][NMOD], sum[2*NN][NMOD];
vector<int> e[N];

int dfs(int v, int p, int tick)
{
  pre[v] = tick++;
  if (p >= 0)
    e[v].erase(find(ALL(e[v]), p));
  for (int u: e[v])
    tick = dfs(u, v, tick);
  return post[v] = tick;
}

ll modPow(ll a, ll n, ll mod)
{
  a %= mod;
  ll r = 1;
  for (; n; n >>= 1, a = a*a%mod)
    if (n & 1)
      r = r*a%mod;
  return r;
}

int findChild(int t, int r)
{
  int l = 0, h = e[t].size()-1;
  while (l < h) {
    int mi = l+h >> 1;
    if (post[e[t][mi]] <= pre[r])
      l = mi+1;
    else
      h = mi;
  }
  return e[t][l];
}

void apply(int i, ll v, int j)
{
  dlt[i][j] = (dlt[i][j] + v) % MOD[j];
  sum[i][j] = (sum[i][j] + (v << __builtin_clz(i)-__builtin_clz(NN))) % MOD[j];
}

void mconcat(int i, int j)
{
  sum[i][j] = (sum[2*i][j]+sum[2*i+1][j]) % MOD[j];
}

void untag(int i, int j)
{
  if (i < 0 || NN <= i) return;
  i += NN;
  for (int ii, h = 31-__builtin_clz(NN); h; h--)
    if (dlt[ii = i >> h]) {
      apply(2*ii, dlt[ii][j], j);
      apply(2*ii+1, dlt[ii][j], j);
      dlt[ii][j] = 0;
    }
}

void add(int l, int r, ll v, int j)
{
  bool lf = false, rf = false;
  untag(l-1, j);
  untag(r, j);
  for (l += NN, r += NN; l < r; ) {
    if (l & 1) lf = true, apply(l++, v, j);
    l >>= 1;
    if (lf) mconcat(l-1, j);
    if (r & 1) rf = true, apply(--r, v, j);
    r >>= 1;
    if (rf) mconcat(r, j);
  }
  for (l--; l >>= 1, r >>= 1; ) {
    if (lf || l == r) mconcat(l, j);
    if (rf && l < r) mconcat(r, j);
  }
}

ll getSum(int l, int r, int j)
{
  ll s = 0;
  untag(l-1, j);
  untag(r, j);
  for (l += NN, r += NN; l < r; l >>= 1, r >>= 1) {
    if (l & 1) s += sum[l++][j];
    if (r & 1) s += sum[--r][j];
  }
  return s;
}

pair<ll, ll> halfEuclid(ll a, ll b)
{
  ll x = 1, y = 0;
  while (b) {
    ll q = a/b, t = a%b;
    a = b; b = t;
    t = x-q*y; x = y; y = t;
  }
  return {a, x};
}

ll linearModular(ll b[], ll w[], int n)
{
  ll m = 1, a = 0;
  REP(i, n)
    m *= w[i];
  REP(i, n) {
    ll mm = m/w[i], x = halfEuclid(mm, w[i]).se;
    a = (a + mm * x % m * b[i]) % m;
  }
  return (a + m) % m;
}

int main()
{
  FOR(i, 2, M+1)
    REP(j, NMOD)
      if (halfEuclid(i, MOD[j]).fi != 1)
        belong[i] = j;
  int n, q;
  scanf("%d", &n);
  REP(i, n-1) {
    int v, u;
    scanf("%d%d", &v, &u);
    v--;
    u--;
    e[v].pb(u);
    e[u].pb(v);
  }
  dfs(0, -1, 0);
  for (scanf("%d", &q); q--; ) {
    char op;
    int r, t;
    scanf(" %c%d%d", &op, &r, &t);
    r--;
    t--;
    if (op == 'U') {
      ll a, b;
      scanf("%lld%lld", &a, &b);
      REP(i, NMOD) {
        ll v = (modPow(a, b, MOD[i]) + modPow(a+1, b, MOD[i]) + modPow(b+1, a, MOD[i])) % MOD[i];
        if (r == t)
          add(0, n, v, i);
        else if (pre[t] < pre[r] && post[r] <= post[t]) {
          int p = findChild(t, r);
          add(0, n, v, i);
          add(pre[p], post[p], - v, i);
        } else
          add(pre[t], post[t], v, i);
      }
    } else {
      int m, nw = 0;
      ll w[3], b[3];
      scanf("%d", &m);
      for (int mm = m, i = 0; mm > 1; i++) {
        int p = 1;
        while (mm % PRIME[i] == 0) {
          mm /= PRIME[i];
          p *= PRIME[i];
        }
        if (p > 1)
          w[nw++] = p;
      }
      REP(i, nw) {
        int j = belong[w[i]];
        if (r == t)
          b[i] = getSum(0, n, j) % w[i];
        else if (pre[t] < pre[r] && post[r] <= post[t]) {
          int p = findChild(t, r);
          b[i] = (getSum(0, n, j) - getSum(pre[p], post[p], j)) % w[i];
        } else 
          b[i] = getSum(pre[t], post[t], j) % w[i];
      }
      printf("%lld\n", linearModular(b, w, nw));
    }
  }
}
