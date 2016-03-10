// ingenious dynamic programming on tree
#include <algorithm>
#include <cstdio>
#include <deque>
#include <utility>
#include <vector>
using namespace std;

typedef pair<int, int> pii;
#define REP(i, n) for (int i = 0; i < (n); i++)
#define fi first
#define mp make_pair
#define pb push_back
#define se second

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100000;
vector<int> e[N];

// {C, {A, B}}
// C: whether A covers the parent edge
// A: cost of subtree(v)
// B: cost of subtree(v)+parent edge; parent edge is the end of some path
// A <= B <= A+1
pair<bool, pii> dfs(int v, int p)
{
  deque<pii> c;
  int t = -1;
  bool has = false;
  for (auto u: e[v])
    if (u != p) {
      auto r = dfs(u, v);
      if (! r.fi)
        has = true;
      if (r.se.fi == r.se.se)
        c.push_front(r.se);
      else
        c.pb(r.se);
      t = u;
    }
  if (c.empty())
    return {false, pii{0, 1}};
  bool cover = false;
  int f = 0, g = 0, i = 0;
  for (; i+1 < c.size() && c[i+1].fi == c[i+1].se; i += 2) // beneficial to pair B if the A=B for some child
    f += c[i].se+c[i+1].se-1, cover = true;
  if (i < c.size()) {
    g = f+c[i].se;
    if (c[i].fi == c[i].se)
      cover = true;
    // if A < B for all children and some child is uncovered
    f += ! cover && has ? cover = true, c[i].se : c[i].fi;
    while (++i < c.size())
      f += c[i].fi, g += c[i].fi;
  } else
    g = f+1; // all children are paired, one more edge is needed to cover the parent edge
  return {cover, {f, g}};
}

int main()
{
  for (int cc = ri(); cc--; ) {
    int n = ri();
    REP(i, n)
      e[i].clear();
    REP(i, n-1) {
      int u = ri(), v = ri();
      e[u].pb(v);
      e[v].pb(u);
    }
    printf("%d\n", dfs(0, -1).se.fi);
  }
}
