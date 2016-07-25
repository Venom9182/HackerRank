#include <algorithm>
#include <climits>
#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>
using namespace std;

#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define ROF(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (b); --i >= (a); )

const long N = 200000, NN = 1 << 63-__builtin_clzl(N-1)+1, M = 100000;
long st[N], dep[N], pre[N], post[N], tick, mx[2*NN], dlt[2*NN], opt;
vector<pair<long, long>> adj[N], ticket[N], other[N], down[N], up[N];

void mconcat(long i)
{
  mx[i] = max(mx[2*i]+dlt[2*i], mx[2*i+1]+dlt[2*i+1]);
}

// plus satisfies associativity, tagging is unnecessary
void add(long u, long x)
{
  bool lf = false, rf = false;
  long l = NN+pre[u], r = NN+post[u];
  while (l < r) {
    if (l & 1) lf = true, dlt[l++] += x;
    l >>= 1;
    if (lf) mconcat(l-1);
    if (r & 1) rf = true, dlt[--r] += x;
    r >>= 1;
    if (rf) mconcat(r);
  }
  for (l--; l >>= 1, r >>= 1; ) {
    if (lf || l == r) mconcat(l);
    if (rf && l != r) mconcat(r);
  }
}

void dfs(long d, long sum, long u)
{
  dep[u] = d;
  st[d] = u;
  mx[NN+tick] = - sum;
  pre[u] = tick++;
  post[u] = LONG_MAX;
  long x = 0;
  for (auto e: ticket[u])
    if (post[e.first]) {
      long v = e.first, cost = e.second;
      if (post[v] == LONG_MAX) {
        long w = st[dep[v]+1];
        down[w].emplace_back(u, cost);
        up[u].emplace_back(w, cost);
        x += cost;
      } else {
        other[u].emplace_back(v, cost);
        other[v].emplace_back(u, cost);
      }
    }
  for (auto e: adj[u])
    if (! post[e.first])
      dfs(d+1, sum+e.second, e.first);
  post[u] = tick;
  add(u, x);
}

void calc(long u, long p)
{
  for (auto e: other[u])
    add(e.first, e.second);
  for (auto e: down[u])
    add(e.first, - e.second);
  for (auto e: up[u]) {
    dlt[1] += e.second;
    add(e.first, - e.second);
  }
  opt = max(opt, mx[1]+dlt[1]);
  for (auto e: adj[u])
    if (e.first != p) {
      dlt[1] -= e.second;
      add(e.first, 2*e.second);
      calc(e.first, u);
      dlt[1] += e.second;
      add(e.first, -2*e.second);
    }
  for (auto e: other[u])
    add(e.first, - e.second);
  for (auto e: down[u])
    add(e.first, e.second);
  for (auto e: up[u]) {
    dlt[1] -= e.second;
    add(e.first, e.second);
  }
}

int main()
{
  ios_base::sync_with_stdio(0);
  long n, m, u, v, w;
  cin >> n;
  REP(i, n-1) {
    cin >> u >> v >> w;
    u--, v--;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }
  cin >> m;
  REP(i, m) {
    cin >> u >> v >> w;
    u--, v--;
    ticket[u].emplace_back(v, w);
    ticket[v].emplace_back(u, w);
  }
  dfs(0, 0, 0);
  ROF(i, 1, NN)
    mconcat(i);
  calc(0, -1);
  cout << opt << endl;
}
