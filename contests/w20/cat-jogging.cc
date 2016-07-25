#include <algorithm>
#include <iostream>
#include <type_traits>
#include <unordered_map>
#include <vector>
using namespace std;

#define ALL(x) (x).begin(), (x).end()
#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

const long N = 50000, B = 300;
bool a[N];
vector<long> adj[N];
unordered_map<long, long> c[N];

int main()
{
  ios_base::sync_with_stdio(0);
  long n, m, u, v, ans = 0;
  cin >> n >> m;
  REP(i, m) {
    cin >> u >> v;
    u--, v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  REP(i, n)
    sort(ALL(adj[i]));
  REP(i, n)
    if (adj[i].size() < B)
      for (long u: adj[i])
        for (long v: adj[i]) {
          if (u <= v) break;
          ans += c[u][v]++;
        }
    else {
      for (long u: adj[i])
        a[u] = true;
      REP(j, n)
        if (j != i && (adj[j].size() < B || j < i)) {
          long cnt = 0;
          for (long u: adj[j])
            if (u != i && a[u])
              ans += cnt++;
        }
      for (long u: adj[i])
        a[u] = false;
    }
  cout << ans/2 << endl;
}
