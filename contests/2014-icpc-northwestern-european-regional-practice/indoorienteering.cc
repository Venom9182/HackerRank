#include <algorithm>
#include <cstdio>
#include <unordered_set>
#include <vector>
using namespace std;

typedef long long ll;
#define ALL(x) (x).begin(), (x).end()
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) for (int i = 0; i < (n); i++)
#define pb push_back

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

ll rl()
{
  ll x;
  scanf("%lld", &x);
  return x;
}

const int N = 14;
ll g[N][N];

int main()
{
  int n = ri(), tak = 0;
  ll tot = rl();
  REP(i, n) REP(j, n)
    g[i][j] = rl();
  vector<vector<int>> perm[2];
  REP(j, 2) {
    vector<int> p((n+j)/2-1);
    iota(ALL(p), 0);
    do perm[j].pb(p);
    while (next_permutation(ALL(p)));
  }
  FOR(x, 1, n) REP(i, 1<<n) {
    if (i & 1 || i & 1<<x || __builtin_popcount(i) != n/2-1) continue;
    unordered_set<ll> as;
    REP(j, 2) {
      vector<int> ps;
      FOR(k, 1, n)
        if (k != x && (j ? ~i : i) & 1<<k)
          ps.pb(k);
      for (auto &p: perm[j]) {
        ll len = 0;
        int y = 0;
        REP(i, ps.size()) {
          len += g[y][ps[p[i]]];
          y = ps[p[i]];
        }
        len += g[y][x];
        if (j)
          tak |= as.count(tot-len);
        else if (len <= tot)
          as.insert(len);
      }
    }
  }
  puts(tak ? "possible" : "impossible");
}
