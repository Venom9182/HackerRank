#include <algorithm>
#include <cstdio>
#include <map>
#include <utility>
using namespace std;

#define REP(i, n) FOR(i, 0, n)
#define REP1(i, n) FOR(i, 1, n+1)
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define fi first
#define se second
typedef long long ll;
typedef pair<int, int> pii;

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100000, MOD = 1000000007;
vector<pair<int, pii>> e[N];
map<pii, pair<int, int>> ma;
map<int, int> cnt;
int n, fac[N+1], invfac[N+1];

int inv(int x)
{
  return x == 1 ? 1 : ll(MOD-MOD/x)*inv(MOD%x) % MOD;
}

pair<int, int> &label(pii a, pii b)
{
  if (a.fi > b.fi) swap(a, b);
  auto key = pii{a.fi, b.fi};
  if (! ma.count(key)) {
    int t = ma.size() + 1;
    ma[key] = {t, a.se + b.se + 1};
    cnt[t] = ll(cnt[a.fi]) * cnt[b.fi] % MOD * fac[a.se+b.se] % MOD * invfac[a.se] % MOD * invfac[b.se] % MOD;
    if (a.fi != b.fi)
      cnt[t] = cnt[t] * 2 % MOD;
  }
  return ma[key];
}

pii dfs(int v, int p)
{
  vector<pii> ch;
  for (auto &it: e[v])
    if (it.fi != p) {
      if (! it.se.se)
        it.se = dfs(it.fi, v);
      ch.push_back(it.se);
    }
  if (ch.size() > 2)
    return {0, 0};
  while (ch.size() < 2)
    ch.emplace_back(0, 0);
  return label(ch[0], ch[1]);
}

int main()
{
  fac[0] = invfac[0] = 1;
  REP1(i, N) {
    fac[i] = ll(fac[i-1]) * i % MOD;
    invfac[i] = inv(fac[i]);
  }
  for (int cases = ri(); cases--; ) {
    n = ri();
    cnt.clear();
    cnt[0] = 1;
    ma.clear();
    REP(i, n)
      e[i].clear();

    REP(i, n-1) {
      int x = ri()-1, y = ri()-1;
      e[x].emplace_back(y, pii{0, 0});
      e[y].emplace_back(x, pii{0, 0});
    }

    REP(i, n)
      dfs(i, -1);
    int ans = 0;
    for (auto &x: ma)
      if (x.se.se == n)
        (ans += cnt[x.se.fi]) %= MOD;
    printf("%d\n", ans);
  }
}
