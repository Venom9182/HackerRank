#include <algorithm>
#include <iostream>
#include <type_traits>
#include <unordered_map>
#include <vector>
using namespace std;

#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

const long N = 50000;
long c[N], s[N], opt;
unordered_map<long, long> a, b;
vector<long> adj[N];

void update(long x)
{
  if (3*x >= s[0])
    opt = min(opt, 3*x-s[0]);
}

long dfs(long u, long p)
{
  s[u] = c[u];
  for (long v: adj[u])
    if (v != p)
      s[u] += dfs(v, u);
  a[s[u]]++;
  return s[u];
}

void dfs2(long u, long p)
{
  if (2*s[u] == s[0] || // x -> x
      b[2*s[u]] ||      // o -> x -> x
      b[s[0]-s[u]] ||   // x -> o -> x
      a[s[u]] > 1)      // o -> (x, x)
    update(s[u]);
  if ((s[0]-s[u])%2 == 0 && b[s[0]-(s[0]-s[u])/2]) // x -> x -> o
    update((s[0]-s[u])/2);
  b[s[u]]++;
  long t = (s[0]-s[u])/2;
  if ((s[0]-s[u])%2 == 0 && t >= s[u] && a[t] > b[t]) // x -> (x, o)
    update(t);
  for (long v: adj[u])
    if (v != p)
      dfs2(v, u);
  b[s[u]]--;
}

int main()
{
  ios_base::sync_with_stdio(0);
  long cases, n, u, v;
  for (cin >> cases; cases--; ) {
    cin >> n;
    REP(i, n) {
      cin >> c[i];
      adj[i].clear();
    }
    REP(i, n-1) {
      cin >> u >> v;
      u--, v--;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
    a.clear();
    b.clear();
    dfs(0, -1);
    opt = s[0];
    dfs2(0, -1);
    cout << (opt == s[0] ? -1 : opt) << endl;
  }
}
