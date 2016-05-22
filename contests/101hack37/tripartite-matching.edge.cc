#include <iostream>
#include <type_traits>
#include <unordered_set>
#include <vector>
using namespace std;

#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

const long N = 100000, SN = 300;

vector<long> a[3][N];
unordered_set<long> b[3][N];

int main()
{
  ios_base::sync_with_stdio(0);
  long n, m, u, v, ans = 0;
  cin >> n;
  REP(k, 3)
    for (cin >> m; m--; ) {
      cin >> u >> v;
      a[k][u-1].push_back(v-1);
      a[k][v-1].push_back(u-1);
      b[k][u-1].insert(v-1);
      b[k][v-1].insert(u-1);
    }
  REP(u, n)
    for (long v: a[0][u])
      if (a[2][u].size() < a[1][v].size())
        for (long w: a[2][u])
          ans += b[1][v].count(w);
      else
        for (long w: a[1][v])
          ans += b[2][u].count(w);
  cout << ans << endl;
}
