/* Problem
   Divide a M*N board into two connected parts where some cells are disallowed to be included in a part.
   Print the number of ways if the absolute difference between numbers of cells in two parts <= K.

   connectivity DP, singly-linked list as state
   state: connectivity of n cells & colors of n+1 cells on the contour 
 */
  
#include <algorithm>
#include <cstdio>
#include <map>
#include <tuple>
using namespace std;

typedef tuple<int, int, int> tiii;
#define REP(i, n) for (int i = 0; i < (n); i++)
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )
#define fi first
#define se second

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 8;
char a[N][N+1];

int main()
{
  int m = ri(), n = ri(), diff = ri(), rest[3] = {0, 0, n*m};
  long ans = 0;
  REP(i, m) {
    scanf("%s", a[i]);
    REP(j, n) {
      if (a[i][j] == 'D')
        rest[0]++;
      if (a[i][j] == 'T')
        rest[1]++;
    }
  }
  map<tuple<vector<int>, int, int>, long> cur, pre;
  vector<int> src(n);
  int srcy = 0;
  // initial state: interlaced colors which can be blocked freely
  iota(src.begin(), src.end(), 0);
  for (int i = 0; i < n; i += 2)
    srcy |= 1 << i;
  cur.emplace(make_tuple(src,srcy,0), 1);
  REP(i, m)
    REP(j, n) {
      pre.swap(cur);
      cur.clear();
      for (auto &it: pre) {
        vector<int> L(n), R;
        int y, num;
        tie(R, y, num) = it.fi;
        REP(i, n)
          L[R[i]] = i;
        REP(d, 2) // choose D or T
          if (a[i][j] != (d ? 'D' : 'T') && (! i || ! j || (y>>j-1 & 7) != (d ? 7 : 0))) { // not the other color, not square
            // not block a connected component with the other color
            if (! i || (y>>j+1 & 1) == d || R[j] != j) {
              vector<int> LL = L, RR = R;
              int yy = y;

              if ((y>>j+1 & 1) == d) {
                if (j && (y>>j-1 & 1) == d) {
                  // j-1 & j may belong to the same list or two different lists, merge if different
                  int jj = RR[j-1];
                  RR[LL[jj] = LL[j]] = jj;
                  LL[RR[j-1] = j] = j-1;
                }
              } else {
                LL[RR[j]] = LL[j];
                RR[LL[j]] = RR[j];
                if (j && (y>>j-1 & 1) == d) {
                  LL[RR[j] = RR[j-1]] = j;
                  RR[LL[j] = j-1] = j;
                } else
                  LL[j] = RR[j] = j;
              }
              
              // cell j on the countour moves and changes color
              if (d)
                yy |= 1 << j;
              else
                yy &= ~ (1 << j);
              if (j == n-1)
                yy = (yy & (1<<n)-1) << 1;
              cur[make_tuple(RR, yy, num+d)] += it.se;
            } else if (! rest[d^1] && (n == 1 || i == m-1)) {
              bool ok = true;
              // square
              FOR(k, j+1, n)
                if ((y>>k & 3) == (d ? 3 : 0))
                  ok = false;
              // check whether other connected components with the other color exist
              REP(k, j)
                if ((y>>k & 1) != d)
                  ok = false;
              FOR(k, j+2, n+1)
                if ((y>>k & 1) != d)
                  ok = false;
              if (ok && abs(2*(num+(d?rest[2]:0))-n*m) <= diff)
                ans += it.se;
            }
          }
      }

      if (a[i][j] == 'D')
        rest[0]--;
      if (a[i][j] == 'T')
        rest[1]--;
      rest[2]--;
  }
  for (auto &it: cur) {
    vector<int> R;
    int y, num;
    tie(R, y, num) = it.fi;
    if (abs(2*num-n*m) <= diff) {
      int comp = 0;
      REP(j, n)
        if (R[j] <= j)
          comp++;
      if (comp <= 2)
        ans += it.se;
    }
  }
  printf("%ld\n", ans);
}
