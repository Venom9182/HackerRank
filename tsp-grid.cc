#include <algorithm>
#include <climits>
#include <cstdio>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 10, NS = 5798;
int n, r[N][N], d[N][N];
int ns, three[N+1], mapping[177147], states[NS], tr4[NS][N], tr8[NS][N];
int dp[2][NS], *pre, *cur;

int bit(int s, int i)
{
  return s/three[i]%3;
}

void dfs(int k, int x, int s)
{
  if (! k) {
    if (! x) {
      mapping[s] = ns;
      states[ns++] = s;
    }
    return;
  }
  dfs(k-1, x, 3*s);
  if (x > 0) dfs(k-1, x-1, 3*s+1);
  dfs(k-1, x+1, 3*s+2);
}

void tr(int j, int s, int g, int opt)
{
  s -= three[j]*bit(s, j)+three[j+1]*bit(s, j+1);
  s += three[j]*g;
  if (j == n-1) {
    if (bit(s, n)) return;
    s *= 3;
  }
  cur[mapping[s]] = min(cur[mapping[s]], opt);
}

int main()
{
  int m = ri();
  n = ri();
  if (n%2 && m%2)
    return puts("0"), 0;
  REP(i, m)
    REP(j, n-1)
      r[i][j] = ri();
  REP(i, m-1)
    REP(j, n)
      d[i][j] = ri();

  three[0] = 1;
  REP(i, n)
    three[i+1] = three[i]*3;
  dfs(n+1, 0, 0);
  REP(si, ns) {
    int s = states[si];
    REP(i, n) {
      int g = bit(s, i)+3*bit(s, i+1);
      if (g == 4) {
        int c = 0;
        for (int j = i+1; ; j++) {
          int b = bit(s, j);
          if (b == 1) c++;
          if (b == 2) c--;
          if (! c) {
            tr4[si][i] = s-three[i]*g-three[j]; // 1122 -> 0012
            break;
          }
        }
      }
      if (g == 8) {
        int c = 0;
        for (int j = i; ; j--) {
          int b = bit(s, j);
          if (b == 1) c++;
          if (b == 2) c--;
          if (! c) {
            tr8[si][i] = s-three[i]*g+three[j]; // 1122 -> 1200
            break;
          }
        }
      }
    }
  }
  
  pre = dp[0];
  cur = dp[1];
  fill_n(cur, ns, INT_MAX/2);
  cur[mapping[0]] = 0;
  REP(i, m)
    REP(j, n) {
      swap(pre, cur);
      fill_n(cur, ns, INT_MAX/2);
      REP(si, ns) {
        int s = states[si], g = bit(s, j)+bit(s, j+1)*3, opt = pre[si];
        switch (g) {
        case 0:
          tr(j, s, 1+3*2, opt+d[i][j]+r[i][j]);
          break;
        case 1:
        case 3:
          tr(j, s, 1, opt+d[i][j]);
          tr(j, s, 3, opt+r[i][j]);
          break;
        case 2:
        case 6:
          tr(j, s, 2, opt+d[i][j]);
          tr(j, s, 6, opt+r[i][j]);
          break;
        case 5:
          tr(j, s, 0, opt);
          break;
        case 4:
          tr(j, tr4[si][j], 0, opt);
          break;
        case 8:
          tr(j, tr8[si][j], 0, opt);
          break;
        case 7:
          if (i == m-1 && j == n-1)
            tr(j, s, 0, opt);
          break;
        }
      }
    }
  printf("%d\n", cur[mapping[0]]);
}
