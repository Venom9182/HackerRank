#include <algorithm>
#include <cstdio>
#include <map>
#include <utility>
#include <vector>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); i++)
#define fi first
#define se second

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100000, M = N;
int uf[N], cnt[M];

int find(int x)
{
  while (uf[x] != x)
    uf[x] = uf[uf[x]], x = uf[x];
  return x;
}

int main()
{
  int n = ri(), m = ri(), q = ri();
  vector<map<int,int>> a(n);
  REP(i, n) {
    int x = ri()-1;
    a[i][x] = 1;
    cnt[x]++;
  }
  vector<int> ans(m, -1);
  REP(i, m)
    if (cnt[i] <= 1)
      ans[i] = 0;
  iota(uf, uf+n, 0);
  REP(i, q) {
    int u = ri()-1, v = ri()-1, uu = find(u), vv = find(v);
    if (uu != vv) {
      auto &ma = a[uu], &mb = a[vv];
      if (ma.size() < mb.size()) {
        ma.swap(mb);
        swap(uu, vv);
      }
      uf[vv] = uu;
      for (auto x: mb)
        if ((ma[x.fi] += x.se) == cnt[x.fi] && ans[x.fi] == -1)
          ans[x.fi] = i+1;
    }
  }
  REP(i, m)
    printf("%d\n", ans[i]);
}
