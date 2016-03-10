#include <algorithm>
#include <climits>
#include <cstdio>
#include <utility>
#include <vector>
using namespace std;
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define pb push_back
#define fi first
#define se second

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 102;
vector<pair<int, int> > e[N];
int q[N], d[N];
bool in[N];

int moore(int n, int src, int sink)
{
  int *fo = q, *re = q;
  fill_n(d, n, INT_MAX);
  fill_n(in, n, false);
  d[src] = 0;
  *re++ = src;
  while (fo != re) {
    int u = *fo++;
    if (fo == q+n) fo = q;
    in[u] = false;
    for (auto i: e[u])
      if (d[u]+i.se < d[i.fi]) {
        d[i.fi] = d[u]+i.se;
        if (! in[i.fi]) {
          in[i.fi] = true;
          *re++ = i.fi;
          if (re == q+n) re = q;
        }
      }
  }
  return d[sink];
}

void add(int u, int v, int w)
{
  e[u].pb(make_pair(v, w));
}

int main()
{
  int n = ri(), m = ri();
  while (m--) {
    int u = ri(), v = ri(), w = ri();
    add(u-1, v, w);
    add(v, u-1, -w);
  }
  REP(i, n) {
    add(i, i+1, 1);
    add(i+1, i, 0);
  }
  printf("%d %d\n", -moore(n+1, n, 0), moore(n+1, 0, n));
}
