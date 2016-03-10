#include <algorithm>
#include <cstdio>
#include <deque>
#include <utility>
using namespace std;

typedef long long ll;
#define REP(i, n) for (int i = 0; i < (n); i++)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )
#define fi first
#define pb push_back
#define se second

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int K = 5000;
typedef pair<int, ll> pil;
ll dp[K+1];
deque<pil> q[K];

int main()
{
  int n = ri(), k = ri();
  while (n--) {
    ll x = ri();
    int s = ri(), a = ri(), b = ri();
    if (! a)
      REP(i, k+1)
        dp[i] += s*x;
    else if (! b)
      ROF(i, a, k+1)
        dp[i] = max(dp[i], dp[i-a]+s*x);
    else {
      REP(i, b)
        q[i].clear();
      REP(i, k+1) {
        auto &qq = q[i%b];
        while (qq.size() && qq.back().se+(i-qq.back().fi)/b*x <= dp[i])
          qq.pop_back();
        qq.emplace_back(i, dp[i]);

        if (i >= a) {
          auto &qq = q[(i-a)%b];
          while (qq.size() && (i-a-qq[0].fi)/b >= s)
            qq.pop_front();
          if (qq.size())
            dp[i] = max(dp[i], qq[0].se+((i-a-qq[0].fi)/b+1)*x);
        }
      }
      b = b;
    }
  }
  printf("%lld\n", dp[k]);
}
