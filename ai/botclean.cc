#include <algorithm>
#include <climits>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); i++)

const int N = 5, NS = 5798;
bool plugd[N][N], plugr[N][N], vis[N][N];
int srcx, srcy;
int ns, mapping[1<<2*(N+1)], states[NS], paired[NS], single[NS], match[NS][N+1];
int dp[2][NS], par[N*N][NS], *pre, *cur;

int bit(int s, int i)
{
  return s >> 2*i & 3;
}

void dfs(int k, int x, int paired, int single, int s)
{
  if (! k) {
    if (! x) {
      ::paired[ns] = paired;
      ::single[ns] = single;
      mapping[s] = ns;
      states[ns++] = s;
    }
    return;
  }
  dfs(k-1, x, paired, single, 4*s);
  if (x > 0)
    dfs(k-1, x-1, paired+1, single, 4*s+1);
  dfs(k-1, x+1, paired, single, 4*s+2);
  if (single < 2)
    dfs(k-1, x, paired, single+1, 4*s+3);
}

void tr(int si, int i, int j, int s, int g, int sum, bool canStart = false)
{
  if (! canStart && i == srcx && j == srcy) return;
  s &= ~ (15 << 2*j);
  s |= g << 2*j;
  if (j == N-1) {
    if (bit(s, N)) return;
    s <<= 2;
  }
  int si2 = mapping[s];
  if (sum < cur[si2])
    cur[si2] = sum, par[N*i+j][si2] = si;
}

int leftMatch(int s, int j)
{
  int c = 0;
  for (; ; j--) {
    int b = bit(s, j);
    if (b == 1) c++;
    if (b == 2) c--;
    if (! c) return j;
  }
}

int rightMatch(int s, int j)
{
  int c = 0;
  for (; ; j++) {
    int b = bit(s, j);
    if (b == 1) c++;
    if (b == 2) c--;
    if (! c) return j;
  }
}

void next_move(int srcx, int srcy, vector<string> a)
{
  ::srcx = srcx;
  ::srcy = srcy;

  int lastx = -1, lasty = -1;
  REP(i, N)
    REP(j, N)
    if (a[i][j] == 'd')
      lastx = i, lasty = j;
  if (lastx < 0) return;

  dfs(N+1, 0, 0, 0, 0);
  REP(si, ns) {
    int s = states[si];
    REP(i, N+1)
      switch (s >> 2*i & 3) {
      case 1:
        match[si][i] = rightMatch(s, i);
        break;
      case 2:
        match[si][i] = leftMatch(s, i);
        break;
      }
  }

  int opt = INT_MAX/2, optx = -1, opty = -1, opts = -1;
  pre = dp[0];
  cur = dp[1];
  fill_n(cur, ns, INT_MAX/2);
  cur[mapping[0]] = 0;
  REP(i, N) REP(j, N) {
    swap(pre, cur);
    fill_n(cur, ns, INT_MAX/2);
    REP(si, ns)
      if (pre[si] < INT_MAX/2) {
        int s = states[si], g = s >> 2*j & 15, sum = pre[si], jj;
        switch (g) {
        case 0:
          if (a[i][j] == '-')
            tr(si, i, j, s, 0, sum);
          tr(si, i, j, s, 1+4*2, sum+1);
          if (single[si] < 2) {
            tr(si, i, j, s, 3, sum+1, true);
            tr(si, i, j, s, 4*3, sum+1, true);
          }
          break;
        case 1:
          tr(si, i, j, s, 1, sum+1);
          tr(si, i, j, s, 4*1, sum+1);
          if (single[si] < 2)
            tr(si, i, j, s + (1 << 2*match[si][j]), 0, sum+1, true);
          break;
        case 2:
          tr(si, i, j, s, 2, sum+1);
          tr(si, i, j, s, 4*2, sum+1);
          if (single[si] < 2)
            tr(si, i, j, s + (2 << 2*match[si][j]), 0, sum+1, true);
          break;
        case 3:
        case 12:
          tr(si, i, j, s, 3, sum+1);
          tr(si, i, j, s, 4*3, sum+1);
          if (single[si] == 1 && ! paired[si])
            if ((lastx < i || lastx == i && lasty <= j) && sum+1 < opt)
              opt = sum+1, optx = i, opty = j, opts = si;
          break;
        case 4:
          tr(si, i, j, s, 1, sum+1);
          tr(si, i, j, s, 4*1, sum+1);
          if (single[si] < 2)
            tr(si, i, j, s + (1 << 2*match[si][j+1]), 0, sum+1, true);
          break;
        case 5:
          tr(si, i, j, s - (1 << 2*match[si][j+1]), 0, sum+1);
          break;
        case 6:
          tr(si, i, j, s, 0, sum+1);
          break;
        case 7:
          tr(si, i, j, s + (1 << 2*match[si][j+1]), 0, sum+1);
          break;
        case 8:
          tr(si, i, j, s, 2, sum+1);
          tr(si, i, j, s, 4*2, sum+1);
          if (single[si] < 2)
            tr(si, i, j, s + (2 << 2*match[si][j+1]), 0, sum+1, true);
        case 9:
          break;
        case 10:
          tr(si, i, j, s + (1 << 2*match[si][j]), 0, sum+1);
          break;
        case 11:
          tr(si, i, j, s + (2 << 2*match[si][j+1]), 0, sum+1);
          break;
        case 13:
          tr(si, i, j, s + (1 << 2*match[si][j]), 0, sum+1);
          break;
        case 14:
          tr(si, i, j, s + (2 << 2*match[si][j]), 0, sum+1);
          break;
        case 15:
          if (! paired[si])
            if ((lastx < i || lastx == i && lasty <= j) && sum+1 < opt)
              opt = sum+1, optx = i, opty = j, opts = si;
          break;
        }
      }
  }

  for(;;) {
    if (bit(states[opts], opty))
      plugr[optx][opty-1] = true;
    if (bit(states[opts], opty+1))
      plugd[optx-1][opty] = true;
    if (optx || opty)
      opts = par[N*optx+opty-1][opts];
    if (opty)
      opty--;
    else if (! optx)
      break;
    else
      optx--, opty = N-1;
  }

  if (a[srcx][srcy] == 'd')
    puts("CLEAN");
  else if (lastx < srcx || lastx == srcx && lasty < srcy) {
    if (count(a[srcx].begin(), a[srcx].begin()+srcy, 'd'))
      puts("LEFT");
    else
      puts("UP");
  } else if (srcx && plugd[srcx-1][srcy])
    puts("UP");
  else if (srcx+1 < N && plugd[srcx][srcy])
    puts("DOWN");
  else if (srcy+1 < N && plugr[srcx][srcy])
    puts("RIGHT");
  else
    puts("LEFT");
}

int main()
{
  int pos[2];
  vector <string> board;
  cin>>pos[0]>>pos[1];
  for(int i=0;i<5;i++) {
    string s;cin >> s;
    board.push_back(s);
  }
  next_move(pos[0], pos[1], board);
}
