#include <algorithm>
#include <cstdio>
#include <set>
#include <stack>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

typedef pair<int, int> pii;
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) for (int i = 0; i < (n); i++)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )
#define pb push_back

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100000, LOGN = 17;
vector<int> es[N];
int fenwick[N], pre[N], post[N], par[LOGN][N];
set<int> vs;

void dfs(int n)
{
  stack<pii> st;
  par[0][0] = -1;
  st.emplace(0, 0);
  int tick = 0;
  while (! st.empty()) {
    int u, x;
    tie(u, x) = st.top();
    st.pop();
    if (! x)
      pre[u] = tick++;
    if (x < es[u].size() && es[u][x] == par[0][u])
      x++;
    if (x < es[u].size()) {
      st.emplace(u, x+1);
      par[0][es[u][x]] = u;
      st.emplace(es[u][x], 0);
    } else
      post[u] = tick;
  }
}

void add(int n, int x, int v)
{
  for (; x < n; x |= x+1)
    fenwick[x] += v;
}

int getSum(int x)
{
  int s = 0;
  for (; x; x &= x-1)
    s += fenwick[x-1];
  return s;
}

bool isRoot(int n, int x)
{
  return getSum(post[x])-getSum(pre[x]) == vs.size();
}

int main()
{
  ROF(_, 0, ri()) {
    int n = ri();
    REP(i, n)
      es[i].clear();
    REP(i, n-1) {
      int u = ri(), v = ri();
      es[u].pb(v);
      es[v].pb(u);
    }
    dfs(n);
    FOR(j, 1, LOGN)
      REP(i, n)
        par[j][i] = par[j-1][i] < 0 ? -1 : par[j-1][par[j-1][i]];
    fill_n(fenwick, n, 0);
    vs.clear();
    ROF(_, 0, ri()) {
      char op;
      int x;
      scanf(" %c%d", &op, &x);
      if (op == '+') {
        vs.insert(x);
        add(n, pre[x], 1);
      } else {
        vs.erase(x);
        add(n, pre[x], -1);
      }
      if (vs.empty())
        puts("-1");
      else {
        int v = *vs.begin();
        if (! isRoot(n, v)) {
          ROF(i, 0, LOGN)
            if (~ par[i][v] && ! isRoot(n, par[i][v]))
              v = par[i][v];
          v = par[0][v];
        }
        printf("%d\n", v);
      }
    }
  }
}
