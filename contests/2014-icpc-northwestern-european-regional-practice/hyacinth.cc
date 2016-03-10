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

const int N = 10000;
int id, col[N][2];
vector<int> e[N];

void dfs(int u, int p, int c)
{
  int cc = id++;
  col[u][0] = c;
  col[u][1] = cc;
  for (int v: e[u])
    if (v != p) {
      dfs(v, u, cc);
      swap(c, cc);
    }
}

int main()
{
  int n = ri();
  REP(i, n-1) {
    int u = ri()-1, v = ri()-1;
    e[u].pb(v);
    e[v].pb(u);
  }
  if (n == 2)
    puts("0 1\n0 1");
  else {
    id++;
    dfs(0, -1, 0);
    REP(i, n)
      printf("%d %d\n", col[i][0], col[i][1]);
  }
}
