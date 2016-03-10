#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>
using namespace std;

typedef pair<int, int> pii;
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) for (int i = 0; i < (n); i++)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )
#define fi first
#define se second

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 50;
char a[101], b[901], ans[101];
int g[8][5], nxt[901][26];
pii h[127];

void f(int x, int y, int xx, int yy, int &m)
{
  int err = 0,
    dx = abs(xx-x), sx = x < xx ? 1 : -1,
    dy = abs(yy-y), sy = y < yy ? 1 : -1;
  for(;;) {
    int e = 2*err;
    if (e <= dx-dy) {
      if (x == xx) break;
      x += sx;
      err += dy;
    }
    if (e >= dx-dy) {
      if (y == yy) break;
      y += sy;
      err -= dx;
    }
    b[m++] = g[x][y];
  }
}

int main()
{
  FOR(i, 'A', 'F') {
    g[2+i-'A'][4] = i;
    h[i] = {2+i-'A', 4};
  }
  FOR(i, 'F', 'M') {
    g[1+i-'F'][3] = i;
    h[i] = {1+i-'F', 3};
  }
  FOR(i, 'M', 'T') {
    g[1+i-'M'][2] = i;
    h[i] = {1+i-'M', 2};
  }
  FOR(i, 'T', 'Z'+1) {
    g[1+i-'T'][1] = i;
    h[i] = {1+i-'T', 1};
  }
  for (int cc = ri(); cc--; ) {
    int n = ri(), m = 0;
    scanf("%s", a);
    b[m++] = a[0];
    for (int i = 1; a[i]; i++)
      f(h[a[i-1]].fi, h[a[i-1]].se, h[a[i]].fi, h[a[i]].se, m);
    ROF(i, 0, m)
      REP(j, 26)
        nxt[i][j] = b[i] == 'A'+j ? i : i == m-1 ? m : nxt[i+1][j];
    ans[0] = '\0';
    while (n--) {
      scanf("%s", a);
      int p = -1;
      for (int i = 0; a[i] && p < m; i++)
        p = nxt[p+1][a[i]-'A'];
      if (p < m && ! ans[0])
        strcpy(ans, a);
    }
    puts(ans[0] ? ans : "NO SOLUTION");
  }
}
