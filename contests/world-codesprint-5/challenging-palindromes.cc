// suffix array + palindromic tree
#include <algorithm>
#include <cstring>
#include <iostream>
#include <numeric>
#include <type_traits>
#include <utility>
using namespace std;

#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define ROF(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (b); --i >= (a); )

const long N = 100000, M = 4*N+3, AB = 26;
char a[M];
long sa[M], isa[M], tab[19][M], L[M], R[M], len[N];

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
      if (isa[sa[i]] != isa[sa[i-1]] || max(sa[i], sa[i-1]) >= n-k || isa[sa[i]+k] != isa[sa[i-1]+k]) m++;
      h[sa[i]] = m-1;
    }
    copy_n(h, n, isa);
    if (m == n) break;
  }
  k = 0;
  h[0] = 0;
  REP(i, n)
    if (isa[i]) {
      for (long j = sa[isa[i]-1]; i+k < n && j+k < n && a[i+k] == a[j+k]; k++);
      h[isa[i]] = k;
      k && k--;
    }
}

long lcp(long x, long y)
{
  if (x < 0 || y < 0) return 0;
  x = isa[x], y = isa[y];
  if (x > y) swap(x, y);
  x++;
  long k = 0;
  while (1 << k+1 < y-x+1) k++;
  return min(tab[k][x], tab[k][y-(1<<k)+1]);
}

struct PalindromicTree { long len, sl, c[AB]; } pt[M+2];

void palindromic_tree(long from, long to)
{
  long allo = 2, u = 1;
  pt[0].len = 0; pt[1].len = -1;
  pt[0].sl = pt[1].sl = 1;
  fill_n(pt[0].c, AB, 0);
  fill_n(pt[1].c, AB, 0);
  FOR(i, from, to) {
    while (i-pt[u].len-1 < 0 || a[i-pt[u].len-1] != a[i])
      u = pt[u].sl;
    long c = a[i]-'a';
    if (! pt[u].c[c]) {
      long v = allo++, w = pt[u].sl;
      pt[v].len = pt[u].len+2;
      while (a[i-pt[w].len-1] != a[i])
        w = pt[w].sl;
      pt[v].sl = pt[w].c[c];
      fill_n(pt[v].c, AB, 0);
      pt[u].c[c] = v;
    }
    u = pt[u].c[c];
    len[i-from] = pt[u].len;
  }
}

int main()
{
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  long cases;
  for (cin >> cases; cases--; ) {
    cin >> a;
    long na = strlen(a);
    a[na] = 0;
    char* ra = a+na+1;
    copy_n(a, na, ra);
    reverse(ra, ra+na);
    ra[na] = 1;
    char* b = ra+na+1;
    cin >> b;
    long nb = strlen(b);
    b[nb] = 2;
    char* rb = b+nb+1;
    copy_n(b, nb, rb);
    reverse(rb, rb+nb);
    long n = 2*na+2*nb+3;
    // layout: a '\0' rev(a) '\1' b '\2' rev(b)

    suffix_array(n, 'z'+1, tab[0], L);
    for (long i = 1; 1 << i < n; i++)
      for (long j = n-(1<<i); j > 0; j--)
        tab[i][j] = min(tab[i-1][j], tab[i-1][j+(1<<i-1)]);

    long opt = 0, optp, optx, opty;
    REP(i, n)
      if (b-a <= sa[i] && sa[i] < b-a+nb)
        L[i] = sa[i];
      else
        L[i] = i ? L[i-1] : -1;
    ROF(i, 0, n)
      if (b-a <= sa[i] && sa[i] < b-a+nb)
        R[i] = sa[i];
      else
        R[i] = i+1 < n ? R[i+1] : -1;
    palindromic_tree(ra-a, ra-a+na);
    REP(i, na) {
      long pal = i ? len[i-1] : 0, ii = ra-a+i, j = L[isa[ii]], comm;
      if (lcp(ii, R[isa[ii]]) > lcp(ii, j))
        j = R[isa[ii]];
      comm = lcp(ii, j);
      if (comm > 0) {
        long len = pal+2*comm, pos = na-(i+comm);
        if (len > opt || len == opt && isa[pos] < isa[optp])
          opt = len, optp = pos, optx = pal+comm, opty = comm;
      }
    }

    REP(i, n)
      if (ra-a <= sa[i] && sa[i] < ra-a+na)
        L[i] = sa[i];
      else
        L[i] = i ? L[i-1] : -1;
    ROF(i, 0, n)
      if (ra-a <= sa[i] && sa[i] < ra-a+na)
        R[i] = sa[i];
      else
        R[i] = i+1 < n ? R[i+1] : -1;
    palindromic_tree(b-a, b-a+nb);
    REP(i, nb) {
      long pal = i ? len[i-1] : 0, ii = b-a+i, j = L[isa[ii]], comm;
      if (lcp(ii, R[isa[ii]]) > lcp(ii, j))
        j = R[isa[ii]];
      comm = lcp(ii, j);
      if (comm > 0) {
        long len = pal+2*comm, pos = n-(i+comm);
        if (len > opt || len == opt && isa[pos] < isa[optp])
          opt = len, optp = pos, optx = comm, opty = pal+comm;
      }
    }

    if (! opt)
      cout << -1;
    else {
      REP(i, optx)
        cout << a[optp+i];
      ROF(i, 0, opty)
        cout << a[optp+i];
    }
    cout << '\n';
  }
}
