#include <cstdio>
#include <queue>
using namespace std;

#define REP(i, n) for (decltype(n) i = 0; i < (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 10, S = 1048576;
int a[N], d[S];

#define f(x, i) ((x) >> 2*(i) & 3)

int main()
{
  int n = ri(), x = 0;
  REP(i, n)
    x |= ri()-1 << 2*i;
  fill_n(d, S, -1);
  queue<int> q;
  d[x] = 0;
  for (q.push(x); ! q.empty(); q.pop()) {
    x = q.front();
    if (! x) break;
    int u[4] = {};
    REP(i, n)
      if (! u[f(x, i)]) {
        u[f(x, i)] = 1;
        REP(j, 4)
          if (! u[j]) {
            int y = x & ~ (3 << 2*i) | (j << 2*i);
            if (d[y] < 0) {
              d[y] = d[x]+1;
              q.push(y);
            }
          }
      }
  }
  printf("%d\n", d[0]);
}
