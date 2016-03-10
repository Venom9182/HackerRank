#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100000;
const char AB[] = "ACGT";
char a[N+1];
int pit, last, dp[N+1];
struct P { int l, suff, half, c[4]; } b[N+1];

int getSuff(int i, int x)
{
  if (! i) return -1;
  while (x >= 0 && a[i-1-b[x].l] != a[i])
    x = b[x].suff;
  return x;
}

int alloc()
{
  fill_n(b[pit].c, 4, -1);
  return pit++;
}

void add(int i)
{
  int x = getSuff(i, last), ch = find(AB, AB+4, a[i])-AB;
  if (x < 0)
    last = 0;
  else {
    if (b[x].c[ch] < 0) {
      int y = alloc();
      b[x].c[ch] = y;
      b[y].l = b[x].l+2;
      int z = getSuff(i, b[x].suff);
      b[y].suff = z < 0 ? 0 : b[z].c[ch];
      if (! x)
        b[y].half = 0;
      else {
        z = b[x].half;
        while (z >= 0 && (a[i-1-b[z].l] != a[i] || 2*(b[z].l+2) > b[y].l))
          z = b[z].suff;
        b[y].half = z < 0 ? 0 : b[z].c[ch];
      }
    }
    last = b[x].c[ch];
  }
}

int main()
{
  for (int cases = ri(); cases--; ) {
    scanf("%s", a);
    int n = strlen(a);
    pit = last = 0;
    alloc();
    b[0].l = 0; b[0].suff = -1;
    REP(i, n)
      add(i);
    dp[0] = 1;
    queue<int> q;
    q.push(0);
    int ans = n;
    while (! q.empty()) {
      int v = q.front();
      q.pop();
      REP(ch, 4)
        if (b[v].c[ch] >= 0) {
          int u = b[v].c[ch];
          dp[u] = min(dp[v] + 1, b[u].l/2-b[b[u].half].l + dp[b[u].half] + 1);
          ans = min(ans, n - b[u].l + dp[u]);
          q.push(u);
        }
    }
    printf("%d\n", ans);
  }
}
