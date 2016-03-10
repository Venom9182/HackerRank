#define __STDC_FORMAT_MACROS
#include <cstdio>
#include <inttypes.h>
#include <map>
#include <utility>
#include <vector>
using namespace std;

typedef int64_t ll;
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) for (int i = 0; i < (n); i++)
#define se second

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 1000001, M = 4;
const int pr[4] = {1000000007, 1000000009, 1000000021, 1000000033};
int p[N], q[4][N];

int main()
{
  FOR(i, 2, N)
    if (! p[i])
      for (int j = i; j < N; j += i)
        p[j] = i;
  REP(i, 4) {
    int g = 1;
    REP(j, N) {
      q[i][j] = g;
      g = ll(g) * 3 % pr[i];
    }
  }
  int n = ri();
  map<vector<int>, int> cnt;
  vector<int> g(M);
  cnt[g] = 1;
  REP(i, n) {
    int x = ri(), y;
    for (; x > 1; x /= y) {
      y = p[x] ? p[x] : x;
      REP(i, M)
        g[i] ^= q[i][y];
    }
    cnt[g]++;
  }
  ll ans = 0;
  for (auto &x: cnt)
    ans += x.se * ll(x.se-1) / 2;
  printf("%" PRId64 "\n", ans);
}
