#include <cstdio>
#include <queue>
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

const int N = 400, M = 1000001;
bool flag[M];
int d[M];
vector<int> e[M];

int main()
{
  for (int n = ri(); n--; ) {
    int u = -1;
    for (int k = ri(); k--; ) {
      int v = ri();
      flag[v] = true;
      if (~ u) {
        e[u].pb(v);
        d[v]++;
      }
      u = v;
    }
  }
  priority_queue<int, vector<int>, greater<int>> pq;
  REP(i, M)
    if (flag[i] && ! d[i])
      pq.push(i);
  bool first = true;
  while (! pq.empty()) {
    int u = pq.top();
    pq.pop();
    if (first) first = false;
    else putchar(' ');
    printf("%d", u);
    for (int v: e[u])
      if (! --d[v])
        pq.push(v);
  }
  puts("");
}
