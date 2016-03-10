#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); i++)
#define pb push_back

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100000, M = N, Q = M, LOGQ = 17;
int uf[N], qu[Q], qv[Q], lo[M], hi[M];
vector<int> vs[N], qs[Q+1];

int find(int x)
{
  while (uf[x] != x)
    uf[x] = uf[uf[x]], x = uf[x];
  return x;
}

int main()
{
  int n = ri(), m = ri(), q = ri();
  REP(i, n)
    vs[ri()-1].pb(i);
  REP(i, q) {
    qu[i] = ri()-1;
    qv[i] = ri()-1;
  }
  fill_n(lo, m, 0);
  fill_n(hi, m, q+1);
  REP(_, LOGQ+1) {
    iota(uf, uf+n, 0);
    REP(i, q+1)
      qs[i].clear();
    REP(i, m)
      qs[lo[i]+hi[i] >> 1].pb(i);
    REP(i, q+1) {
      for (int id: qs[i]) {
        bool flag = true;
        for (int j = 1; j < vs[id].size() && flag; j++)
          flag = find(vs[id][j-1]) == find(vs[id][j]);
        int mi = lo[id]+hi[id] >> 1;
        if (! flag)
          lo[id] = mi+1;
        else
          hi[id] = mi;
      }
      if (i < q)
        uf[find(qu[i])] = find(qv[i]);
    }
  }
  REP(i, m)
    printf("%d\n", lo[i] > q ? -1 : lo[i]);
}
