#include <algorithm>
#include <iostream>
#include <type_traits>
#include <unordered_set>
using namespace std;

#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

const long N = 34;
long a[N], adj[N], opt;
unordered_set<long> optc;

void bron_kerbosch(long in, long out, long cand, long sum, long zero)
{
  if (! out && ! cand) {
    if (sum > opt)
      opt = sum, optc.clear();
    if (sum == opt)
      for (long i = zero; ; i = zero & i-1) {
        optc.insert(in - i);
        if (! i) break;
      }
  } else {
    long pivot, pivotpop = -1;
    for (long i = out | cand; i; i &= i-1) {
      long x = __builtin_ctzl(i), j = cand & ~ adj[x], pop = __builtin_popcountl(j);
      if (pop > pivotpop)
        pivotpop = pop, pivot = x;
    }
    for (long i = cand & ~ adj[pivot]; i; i &= i-1) {
      long x = __builtin_ctzl(i);
      bron_kerbosch(in | 1L << x, out & adj[x], cand & adj[x], sum + a[x], zero | (a[x] ? 0 : 1L << x));
      cand -= 1L << x;
      out |= 1L << x;
    }
  }
}

int main()
{
  long n, m, u, v;
  cin >> n >> m;
  REP(i, n) {
    cin >> a[i];
    adj[i] = (1L << n) - 1 - (1L << i);
  }
  while (m--) {
    cin >> u >> v;
    u--, v--;
    adj[u] &= ~ (1L << v);
    adj[v] &= ~ (1L << u);
  }
  opt = -1;
  bron_kerbosch(0, 0, (1L << n) - 1, 0, 0);
  cout << opt << ' ' << optc.size() << endl;
}
