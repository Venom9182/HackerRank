#include <cstdio>
using namespace std;

typedef long long ll;
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) for (int i = 0; i < (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100000;
bool sieve[N];
int pi[N];

int main()
{
  int n = ri();
  for (int i = 2; i*i < n; i++)
    if (! sieve[i])
      for (int j = i*i; j < n; j += i)
        sieve[j] = true;
  FOR(i, 2, n)
    pi[i] = pi[i-1] + ! sieve[i];
  ll ans = 0;
  REP(i, n)
    ans += (long long)(pi[i]-pi[n-1-i]) * ri();
  printf("%lld\n", ans);
}
