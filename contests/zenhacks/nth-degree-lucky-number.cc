#include <algorithm>
#include <cstdio>
#include <functional>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

typedef long long ll;
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) for (int i = 0; i < (n); i++)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )
#define mp make_pair
#define se second

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

namespace std
{
  template<typename T>
  struct hash<vector<T>> {
    size_t operator()(const vector<T> &v) const {
      hash<T> h;
      size_t r = 0;
      for (auto x: v)
        r = r*17+h(x);
      return r;
    }
  };
}

const int MAXP = 7, N = 43046721+1, NDIG = 10;
bool sieve[N];
int pw[10][MAXP];
vector<int> pows;

ll g(int k)
{
  static unordered_map<vector<int>, ll> memo[NDIG];
  auto it = memo[k].find(pows);
  if (it != memo[k].end())
    return it->se;
  ll ret;
  if (! k) {
    ret = -1;
    REP(i, MAXP)
      if (sieve[pows[i]]) {
        ret = i;
        break;
      }
  } else {
    ret = 0;
    REP(i, 10) {
      REP(j, MAXP)
        pows[j] += pw[i][j];
      ret += g(k-1);
      REP(j, MAXP)
        pows[j] -= pw[i][j];
    }
  }
  return memo[k][pows] = ret;
}

ll f(int n)
{
  int d[10], nd = 0;
  ll ret = 0;
  do d[nd++] = n%10;
  while (n /= 10);
  pows.assign(MAXP, 0);
  ROF(i, 0, nd)
    REP(j, d[i]+1) {
      REP(k, MAXP)
        pows[k] += pw[j][k];
      if (j == d[i]) break;
      ret += g(i);
      REP(k, MAXP)
        pows[k] -= pw[j][k];
    }
  return ret;
}

int main()
{
  REP(i, 10) {
    pw[i][0] = i;
    FOR(j, 1, MAXP)
      pw[i][j] = pw[i][j-1]*i;
  }
  sieve[0] = sieve[1] = true;
  for (int i = 2; i*i < N; i++)
    if (! sieve[i])
      for (int j = i*i; j < N; j += i)
        sieve[j] = true;
  for (int cc = ri(); cc--; ) {
    int a = ri(), b = ri();
    printf("%lld\n", f(b+1)-f(a));
  }
}
