#include <algorithm>
#include <climits>
#include <functional>
#include <iostream>
#include <queue>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>
using namespace std;

typedef pair<long, long> pll;
#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

const long N = 1000, K = 10;
long a[N], d[N << K];
vector<pll> adj[N];

int main()
{
  long n, m, k, u, v, w;
  cin >> n >> m >> k;
  REP(i, n) {
    long t;
    for (cin >> t; t--; ) {
      cin >> w;
      a[i] |= 1 << w-1;
    }
  }
  while (m--) {
    cin >> u >> v >> w;
    u--, v--;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }
  priority_queue<pll, vector<pll>, greater<pll>> pq;
  fill_n(d, n << K, LONG_MAX/2);
  d[a[0]] = 0;
  pq.emplace(0, a[0]);
  while (pq.size()) {
    tie(w, u) = pq.top();
    pq.pop();
    if (d[u] < w) continue;
    for (pll& e: adj[u >> K]) {
      long v = e.first << K | u & (1<<K)-1 | a[e.first];
      if (d[u] + e.second < d[v]) {
        d[v] = d[u] + e.second;
        pq.emplace(d[v], v);
      }
    }
  }
  long ans = LONG_MAX;
  REP(i, 1 << k)
    for (long j = i; ; j = j-1 & i) {
      ans = min(ans, max(d[(n-1) << K | i], d[(n-1) << K | (1 << k) - 1 - i | j]));
      if (! j) break;
    }
  cout << ans << endl;
}
