#include <cstdio>
#include <utility>
using namespace std;

typedef long long ll;
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

const int N = 100000, NN = 131072, MOD = 1000003;
ll fact[MOD], d[2*NN], p[2*NN], dp[2*NN], dlt[2*NN];

ll power(ll a, int n)
{
  ll r = 1;
  for (; n; n >>= 1, a = a*a%MOD)
    if (n & 1)
      r = r*a%MOD;
  return r;
}

void apply(int n, int i, ll v)
{
  dlt[i] += v;
  p[i] += v << __builtin_clz(i)-__builtin_clz(n);
  dp[i] = dp[i]*power(d[i], v)%MOD;
}

void mconcat(int i)
{
  p[i] = p[2*i]+p[2*i+1];
  dp[i] = dp[2*i]*dp[2*i+1]%MOD;
}

void untag(int n, int i)
{
  if (i < 0 || n <= i) return;
  i += n;
  for (int j, h = 31-__builtin_clz(n); h; h--)
    if (dlt[j = i >> h]) {
      apply(n, 2*j, dlt[j]);
      apply(n, 2*j+1, dlt[j]);
      dlt[j] = 0;
    }
}

void add(int n, int l, int r, ll v)
{
  bool lf = false, rf = false;
  untag(n, l-1);
  untag(n, r);
  for (l += n, r += n; l < r; ) {
    if (l & 1) lf = true, apply(n, l++, v);
    l >>= 1;
    if (lf) mconcat(l-1);
    if (r & 1) rf = true, apply(n, --r, v);
    r >>= 1;
    if (rf) mconcat(r);
  }
  for (l--; l >>= 1, r >>= 1; ) {
    if (lf || l == r) mconcat(l);
    if (rf && l != r) mconcat(r);
  }
}

pair<ll, ll> query(int n, int l, int r)
{
  ll ps = 0, dps = 1;
  untag(n, l-1);
  untag(n, r);
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) {
      ps += p[l];
      dps = dps*dp[l]%MOD;
      l++;
    }
    if (r & 1) {
      r--;
      ps += p[r];
      dps = dps*dp[r]%MOD;
    }
  }
  return {ps, dps};
}

int main()
{
  fact[0] = 1;
  FOR(i, 1, MOD)
    fact[i] = fact[i-1]*i%MOD;
  int n = ri(), nn = 1;
  while (nn < n) nn *= 2;
  REP(i, n) {
    ri();
    d[nn+i] = ri();
    p[nn+i] = ri();
    dp[nn+i] = power(d[nn+i], p[nn+i]);
  }
  ROF(i, 1, nn) {
    d[i] = d[2*i]*d[2*i+1]%MOD;
    mconcat(i);
  }
  for (int q = ri(); q--; ) {
    int op = ri(), l = ri()-1, r = ri();
    if (op)
      add(nn, l, r, ri());
    else {
      auto ans = query(nn, l, r);
      ll ps = ans.fi, dps = (ans.se+MOD)%MOD;
      printf("%lld %lld\n", ps, ps >= MOD ? 0 : fact[ps]*dps%MOD);
    }
  }
}
