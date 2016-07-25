#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>
using namespace std;

#define ALL(x) (x).begin(), (x).end()
#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

const long N = 100000, M = 200000;
long n, a[M+40+1], uf[N];
tuple<long, long, long> e[M];
vector<pair<long, long>> adj[N];

long find(long x)
{
  while (uf[x] >= 0) {
    if (uf[uf[x]] >= 0)
      uf[x] = uf[uf[x]];
    x = uf[x];
  }
  return x;
}

long dfs(long u, long p)
{
  long s = 1;
  for (auto i: adj[u])
    if (i.first != p) {
      long sub = dfs(i.first, u);
      a[i.second] = sub*(n-sub);
      s += sub;
    }
  return s;
}

int main()
{
  ios_base::sync_with_stdio(0);
  long m, u, v, w;
  cin >> n >> m;
  fill_n(uf, n, -1);
  REP(i, m) {
    cin >> get<1>(e[i]) >> get<2>(e[i]) >> get<0>(e[i]);
    get<1>(e[i])--;
    get<2>(e[i])--;
  }
  sort(e, e+m);
  REP(i, m) {
    tie(w, u, v) = e[i];
    long ru = find(u), rv = find(v);
    if (ru != rv) {
      adj[u].emplace_back(v, w);
      adj[v].emplace_back(u, w);
      uf[ru] += uf[rv];
      uf[rv] = ru;
    }
  }
  dfs(0, -1);
  string r;
  for (long i = 0; ; i++) {
    if (i >= m+40) break;
    r += a[i] & 1 ? '1' : '0';
    a[i+1] += a[i] >> 1;
  }
  while (r.size() > 1 && r.back() == '0')
    r.pop_back();
  reverse(ALL(r));
  cout << r << endl;
}
