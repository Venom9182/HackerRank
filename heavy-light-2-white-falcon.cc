#include <algorithm>
#include <iostream>
#include <iterator>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>
using namespace std;

#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

const long N = 50000, LN = 63-__builtin_clzl(N-1)+1, NN = 1L << LN, MOD = 1000000007, INV2 = (MOD+1)/2;

vector<long> adj[N];
long chain[N], dep[N], dfn[N], par[N], tick;
pair<long, long> ap[2*NN];
long sum[2*NN];

long dfs(long u, long p)
{
  long size = 1, maxs = 0;
  par[u] = p;
  chain[u] = -1;
  for (long v: adj[u])
    if (v != p) {
      dep[v] = dep[u]+1;
      long s = dfs(v, u);
      size += s;
      if (s > maxs)
        maxs = s, chain[u] = v;
    }
  return size;
}

void hld(long u, long p, long top)
{
  dfn[u] = tick++;
  if (chain[u] >= 0) {
    hld(chain[u], u, top);
    for (long v: adj[u])
      if (v != p && v != chain[u])
        hld(v, u, v);
  }
  chain[u] = top;
}

vector<pair<long, long>> path(long u, long v)
{
  long r = 0;
  vector<pair<long, long>> ps0, ps1;
  while (chain[u] != chain[v]) {
    if (dep[chain[u]] > dep[chain[v]]) {
      ps0.emplace_back(~ dfn[chain[u]], ~ (dfn[u]+1));
      u = par[chain[u]];
    } else {
      ps1.emplace_back(dfn[chain[v]], dfn[v]+1);
      v = par[chain[v]];
    }
  }
  if (dep[u] > dep[v])
    ps0.emplace_back(~ dfn[v], ~ (dfn[u]+1));
  else
    ps1.emplace_back(dfn[u], dfn[v]+1);
  copy(ps1.rbegin(), ps1.rend(), back_inserter(ps0));
  return ps0;
}

void apply(long i, long start, pair<long, long> x)
{
  long h = LN-(63-__builtin_clzl(i)), k = 1L << h;
  x.first = (x.first + ((i<<h) - NN - start) * x.second) % MOD;
  sum[i] = (sum[i] + (2*x.first + (k-1)*x.second) % MOD * k % MOD * INV2) % MOD;
  ap[i].first = (ap[i].first + x.first) % MOD;
  ap[i].second = (ap[i].second + x.second) % MOD;
}

void untag(long i)
{
  if (i < 0 || i >= NN) return;
  i += NN;
  for (long j, h = LN; h; h--)
    if (j = i >> h, ap[j].first || ap[j].second) {
      apply(2*j, (j << h) - NN, ap[j]);
      apply(2*j+1, (j << h) - NN, ap[j]);
      ap[j] = {0, 0};
    }
}

void mconcat(long i)
{
  sum[i] = (sum[2*i] + sum[2*i+1]) % MOD;
}

long get_sum(long l, long r)
{
  long s = 0;
  untag(l-1);
  untag(r);
  for (l += NN, r += NN; l < r; l >>= 1, r >>= 1) {
    if (l & 1) s = (s + sum[l++]) % MOD;
    if (r & 1) s = (s + sum[--r]) % MOD;
  }
  return s;
}

void modify(long l, long r, pair<long, long> x)
{
  long start = l;
  bool lf = false, rf = false;
  untag(l-1);
  untag(r);
  long k = 1;
  for (l += NN, r += NN; l < r; k <<= 1) {
    if (l & 1) lf = true, apply(l++, start, x);
    l >>= 1;
    if (lf) mconcat(l-1);
    if (r & 1) rf = true, apply(--r, start, x);
    r >>= 1;
    if (rf) mconcat(r);
  }
  for (l--; l >>= 1, r >>= 1; ) {
    if (lf || l == r) mconcat(l);
    if (rf && l != r) mconcat(r);
  }
}

int main()
{
  long n, q, op, u, v;
  cin >> n >> q;
  REP(i, n-1) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  dfs(0, -1);
  hld(0, -1, 0);
  while (q--) {
    cin >> op >> u >> v;
    auto ps = path(u, v);
    if (op == 1) {
      long x, y;
      cin >> x;
      y = x;
      for (auto p: ps) {
        tie(u, v) = p;
        if (u >= 0) {
          modify(u, v, make_pair(y, x));
          y = (y + (v-u)*x) % MOD;
        } else {
          modify(~ u, ~ v, make_pair((y+(u-v-1)*x)%MOD, - x));
          y = (y + (u-v)*x) % MOD;
        }
      }
    } else {
      long ans = 0;
      for (auto p: ps) {
        tie(u, v) = p;
        if (u < 0)
          u = ~ u, v = ~ v;
        ans = (ans + get_sum(u, v)) % MOD;
      }
      cout << (ans + MOD) % MOD << '\n';
    }
  }
}
