#include <algorithm>
#include <iostream>
#include <numeric>
#include <tuple>
#include <type_traits>
#include <utility>
using namespace std;

typedef tuple<long, long, long> tlll;
#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define ROF(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (b); --i >= (a); )

const long N = 100000, AB = 26, LOGN = 63-__builtin_clzl(N-1)+1, MOD = 1000000007;
char a[N+1];
long sa[N], isa[N], cnt[N], tab[LOGN][N], has[N+1], pw[N+1];
struct PalindromicTree { long left, len, sl, cnt, c[AB]; } pt[N+2];
tlll palin[N];

void suffix_array(long n, long m, long h[], long x[])
{
  fill_n(h, m, 0);
  copy_n(a, n, isa);
  REP(i, n) h[isa[i]]++;
  FOR(i, 1, m) h[i] += h[i-1];
  ROF(i, 0, n) sa[--h[isa[i]]] = i;
  long k = 1;
  for (; ; k <<= 1) {
    iota(x, x+k, n-k);
    long j = k;
    REP(i, n) if (sa[i] >= k) x[j++] = sa[i]-k;
    fill_n(h, m, 0);
    REP(i, n) h[isa[x[i]]]++;
    FOR(i, 1, m) h[i] += h[i-1];
    ROF(i, 0, n) sa[--h[isa[x[i]]]] = x[i];
    fill_n(h, m, 0);
    m = 1;
    h[sa[0]] = 0;
    FOR(i, 1, n) {
      if (isa[sa[i]] != isa[sa[i-1]] || max(sa[i], sa[i-1]) >= n-k || isa[sa[
i]+k] != isa[sa[i-1]+k]) m++;
      h[sa[i]] = m-1;
    }
    copy_n(h, n, isa);
    if (m == n) break;
  }
  k = h[0] = 0;
  REP(i, n)
    if (isa[i]) {
      for (long j = sa[isa[i]-1]; i+k < n && j+k < n && a[i+k] == a[j+k]; k++);
      h[isa[i]] = k;
      k && k--;
    }
}

long palindromic_tree(long n, long x[], long seq[])
{
  long allo = 2, u = 1;
  pt[0].len = 0; pt[1].len = -1;
  pt[0].sl = pt[1].sl = 1;
  REP(i, n) {
    while (i-pt[u].len-1 < 0 || a[i-pt[u].len-1] != a[i])
      u = pt[u].sl;
    long c = a[i];
    if (! pt[u].c[c-'a']) {
      long v = allo++, w = pt[u].sl;
      pt[v].len = pt[u].len+2;
      pt[v].left = i+1-pt[v].len;
      while (a[i-pt[w].len-1] != a[i])
        w = pt[w].sl;
      pt[v].sl = pt[w].c[c-'a'];
      pt[u].c[c-'a'] = v;
    }
    u = pt[u].c[c-'a'];
    pt[u].cnt++;
  }
  fill_n(x, n, 0);
  FOR(i, 2, allo)
    x[pt[i].len-1]++;
  FOR(i, 1, n)
    x[i] += x[i-1];
  FOR(i, 2, allo)
    seq[--x[pt[i].len-1]] = i;
  ROF(i, 0, allo-2) {
    u = seq[i];
    palin[i] = tlll{pt[u].cnt, pt[u].left, pt[u].len};
    pt[pt[u].sl].cnt += pt[u].cnt;
  }
  return allo-2;
}

long lcp(long i, long j)
{
  if (i == j) return N;
  if (i > j) swap(i, j);
  long t = 63-__builtin_clzl(j-i);
  return min(tab[t][i+1], tab[t][j+1-(1<<t)]);
}

int main()
{
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  long n, k, q;
  cin >> n >> q >> a;
  pw[0] = 1;
  REP(i, n) {
    has[i+1] = (has[i]*100001+a[i]) % MOD;
    pw[i+1] = pw[i]*100001 % MOD;
  }
  long npalin = palindromic_tree(n, tab[0], tab[1]);
  suffix_array(n, 'z'+1, tab[0], tab[1]);
  for (long j = 1; 1<<j < n; j++)
    for (long i = n-(1<<j); i > 0; i--)
      tab[j][i] = min(tab[j-1][i], tab[j-1][i+(1<<j-1)]);
  sort(palin, palin+npalin, [](const tlll& x, const tlll& y) {
    long l, r, _, ll, rr;
    tie(_, l, r) = x;
    tie(_, ll, rr) = y;
    return lcp(isa[l], isa[ll]) >= min(r, rr) ? r < rr : isa[l] < isa[ll];
  });
  FOR(i, 1, npalin)
    get<0>(palin[i]) += get<0>(palin[i-1]);
  REP(i, npalin) {
    long l, r, _;
    tie(_, l, r) = palin[i];
    get<1>(palin[i]) = (has[l+r]-has[l]*pw[r]%MOD+MOD) % MOD;
  }
  while (q--) {
    cin >> k;
    if (k > get<0>(palin[npalin-1]))
      cout << "-1\n";
    else {
      auto it = lower_bound(palin, palin+npalin, tlll{k, 0, 0});
      cout << get<1>(*it) << '\n';
    }
  }
}
