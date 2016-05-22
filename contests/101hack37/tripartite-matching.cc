#include <iostream>
#include <type_traits>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

typedef pair<long, long> pll;
#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

const long N = 100000, SN = 300;

namespace std {
template<>
  struct hash<pll> {
    size_t operator()(const pll& x) const {
      return x.first * N + x.second;
    }
  };
}

vector<long> a[N], b[N], c[N];
unordered_set<pll> e;

int main()
{
  ios_base::sync_with_stdio(0);
  long n, m, u, v, ans = 0;
  cin >> n;
  for (cin >> m; m--; ) {
    cin >> u >> v;
    a[u-1].push_back(v-1);
    a[v-1].push_back(u-1);
  }
  for (cin >> m; m--; ) {
    cin >> u >> v;
    b[u-1].push_back(v-1);
    b[v-1].push_back(u-1);
  }
  for (cin >> m; m--; ) {
    cin >> u >> v;
    c[u-1].push_back(v-1);
    c[v-1].push_back(u-1);
    e.emplace(u-1, v-1);
    e.emplace(v-1, u-1);
  }
  vector<char> f(n);
  REP(v, n) {
    const auto& aa = a[v];
    const auto& bb = b[v];
    if (aa.size() + bb.size() < SN)
      for (long u: aa)
        for (long w: bb)
          ans += e.count({u, w});
    else if (aa.size() > bb.size()) {
      for (long u: aa)
        f[u] = 1;
      for (long w: bb)
        for (long uu: c[w])
          ans += f[uu];
      for (long u: aa)
        f[u] = 0;
    } else {
      for (long w: bb)
        f[w] = 1;
      for (long u: aa)
        for (long ww: c[u])
          ans += f[ww];
      for (long w: bb)
        f[w] = 0;
    }
  }
  cout << ans << endl;
}
