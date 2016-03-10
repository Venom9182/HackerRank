#include <algorithm>
#include <cmath>
#include <cstdio>
#include <stack>
#include <utility>
#include <vector>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define ALL(x) (x).begin(), (x).end()
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) for (int i = 0; i < (n); i++)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )
#define fi first
#define pb push_back
#define se second

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100000, Q = 100000;
vector<int> er[N], el[N];
struct Query {
  int id, l, r;
  bool operator<(const Query &o) const {
    return l < o.l;
  }
  bool operator()(const Query &a, const Query &b) const {
    return a.r < b.r;
  }
} qs[Q];
ll ans[Q], sum;
int components, uf[N];
stack<pii> unites;

int find(int x)
{
  while (uf[x] >= 0)
    x = uf[x];
  return x;
}

int findCompress(int x)
{
  while (uf[x] >= 0) {
    if (uf[uf[x]] >= 0)
      uf[x] = uf[uf[x]];
    x = uf[x];
  }
  return x;
}

void unite(int x, int y, bool save)
{
  if (save) {
    x = find(x);
    y = find(y);
  } else {
    x = findCompress(x);
    y = findCompress(y);
  }
  if (x != y) {
    if (uf[x] > uf[y])
      swap(x, y);
    sum += 2LL * uf[x] * uf[y];
    if (save)
      unites.emplace(y, uf[y]);
    uf[x] += uf[y];
    uf[y] = x;
  }
}

void batch(int qi, int qj)
{
  vector<pii> es;
  int minl = qs[qi].l, maxl = qs[qj-1].l, cur = maxl;
  sort(qs+qi, qs+qj, Query());
  int maxr = qs[qj-1].r;
  ROF(i, minl, maxl)
    for (int v: er[i])
      es.emplace_back(i, v);
  fill(uf+minl, uf+maxr, -1);
  sum = 0;
  FOR(i, qi, qj) {
    Query &q = qs[i];
    for (; cur < q.r; cur++)
      for (int v: el[cur])
        if (maxl <= v)
          unite(v, cur, false);
    for (auto &e: es) {
      if (e.fi < q.l) break;
      if (e.se < q.r)
        unite(e.fi, e.se, true);
    }
    ans[q.id] = sum+q.r-q.l;
    while (! unites.empty()) {
      auto x = unites.top();
      unites.pop();
      int y = uf[x.fi];
      uf[x.fi] = x.se;
      uf[y] -= x.se;
      sum -= 2LL * uf[x.fi] * uf[y];
    }
  }
}

int main()
{
  int n = ri(), m = ri(), q = ri();
  REP(i, m) {
    int u = ri()-1, v = ri()-1;
    if (u > v)
      swap(u, v);
    er[u].pb(v);
    el[v].pb(u);
  }
  REP(i, n) {
    sort(ALL(er[i]));
    sort(ALL(el[i]));
  }
  REP(i, q) {
    int u = ri()-1, v = ri();
    qs[i] = {i, u, v};
  }
  sort(qs, qs+q);

  int bs = sqrt(m);
  for (int qj = 0, qi = 0, j = 0, i = 0; i < n; i = j, qi = qj) {
    int remain = bs;
    for (; j < n && remain > 0; j++)
      remain -= er[j].size();
    while (qj < q && qs[qj].l < j)
      qj++;
    if (qi < qj)
      batch(qi, qj);
  }
  REP(i, q)
    printf("%lld\n", ans[i]);
}
