// For a forward edge (u, v), ans[v] = ans[u] - x[v] + y[v] where
// x[v] : the size of (the subtree rooted at 'v' with color[parent[v]] subtrees pruned)
// y[v] : vertices outside of the subtree rooted at 'u' with color[v] parts pruned
//
// a[color] : the depth of the lowest ancestor with color 'color'
// l[depth] : ancestor with the given depth

#include <algorithm>
#include <iostream>
#include <type_traits>
#include <vector>
using namespace std;

#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

const long N = 100000, C = 100000;
long c[N], col[C], l[N], a[C], x[N], *y[N], cnt[C], num, sum;
vector<long> es[N];

long dfs(long u, long p, long dep)
{
  if (! cnt[c[u]]++)
    num++;
  sum += num;
  long size = 1, ta = a[c[u]];
  a[c[u]] = dep;
  l[dep] = u;
  for (long v: es[u])
    if (v != p)
      size += dfs(v, u, dep+1);
  a[c[u]] = ta;
  x[u] += size;
  if (ta < 0) {
    col[c[u]] -= size;
    y[u] = &col[c[u]];
  } else {
    if (l[ta+1] != u)
      x[l[ta+1]] -= size;
    y[u] = &x[l[ta+1]];
  }
  if (! --cnt[c[u]])
    num--;
  return size;
}

void dfs2(long u, long p, long sum)
{
  c[u] = sum;
  for (long v: es[u])
    if (v != p)
      dfs2(v, u, sum - x[v] + (col <= y[v] && y[v] < col+C ? num+*y[v] : *y[v]));
}

int main()
{
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  long n, u, v;
  cin >> n;
  REP(i, n) {
    cin >> c[i];
    c[i]--;
  }
  REP(i, n-1) {
    cin >> u >> v;
    u--, v--;
    es[u].push_back(v);
    es[v].push_back(u);
  }
  fill_n(a, C, -1);
  dfs(0, -1, 0);
  num = n;
  dfs2(0, -1, sum);
  REP(i, n)
    cout << c[i] << '\n';
}
