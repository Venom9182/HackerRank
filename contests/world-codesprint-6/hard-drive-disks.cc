/*
 * answer = 2 * dp[K][N] + sum{b_i - a_i}
 *
 * dp[k+1][i] = min{dp[k][j] + C(j, i)}
 * = min{dp[k][j] + min{C0(j, p) + C1(p, i)}}
 * = min{min{dp[k][j] + C0(j, p)} + C1(p, i)}}
 * = min{dp0[k+1][p] + C1(p, i)}
 *
 * where
 * C0(j, p) = sum{x_p - b_i : j <= i, a_i+b_i <= 2*x_p}
 * C1(p, i) = sum{a_j - x_p : j < i, 2*x_p < a_j+b_j}
 */
#include <algorithm>
#include <climits>
#include <iostream>
#include <type_traits>
#include <utility>
using namespace std;

typedef pair<long, long> pll;
#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

const long N = 100000, LOGN = 63-__builtin_clzl(N-1)+1, V = 4*(LOGN+1);
pll a[N], seg[2*N*V];
long n, dp[N+1], dp0[2*N], xs[2*N], allo;
int root0[N+1], root1[N+1], child[2*N*V][2];

template<class U, class V>
pair<U, V> operator+(pair<U, V> x, pair<U, V> y)
{
  return {x.first+y.first, x.second+y.second};
}

template<class U, class V>
pair<U, V> operator-(pair<U, V> x, pair<U, V> y)
{
  return {x.first-y.first, x.second-y.second};
}

long scale(long x)
{
  return lower_bound(xs, xs+2*n, x) - xs;
}

void insert(int& r, int rt, long l, long h, long x, long xx)
{
  long m = l+h >> 1;
  r = allo++;
  seg[r] = {seg[rt].first+1, seg[rt].second+xx};
  if (l < h-1) {
    if (x < m) {
      child[r][1] = child[rt][1];
      insert(child[r][0], child[rt][0], l, m, x, xx);
    } else {
      child[r][0] = child[rt][0];
      insert(child[r][1], child[rt][1], m, h, x, xx);
    }
  }
}

pll get_sum(int rt, long l, long h, long ll, long hh)
{
  if (! rt || ll <= l && h <= hh)
    return seg[rt];
  long m = l+h >> 1;
  pll r{0, 0};
  if (ll < m)
    r = r + get_sum(child[rt][0], l, m, ll, hh);
  if (m < hh)
    r = r + get_sum(child[rt][1], m, h, ll, hh);
  return r;
}

long calc_l(long j, long p)
{
  long r = dp[j], l = 0, h = n;
  if (r == LONG_MAX)
    return LONG_MAX;
  while (l < h) {
    long m = l+h >> 1;
    if (a[m].first+a[m].second <= 2*xs[p])
      l = m+1;
    else
      h = m;
  }
  if (j < l) {
    pll t = get_sum(root1[l], 0, 2*n, 0, p) - get_sum(root1[j], 0, 2*n, 0, p);
    r += xs[p]*t.first-t.second;
  }
  return r;
}

long calc_r(long p, long i)
{
  long r = dp0[p], l = 0, h = n;
  if (r == LONG_MAX)
    return LONG_MAX;
  while (l < h) {
    long m = l+h >> 1;
    if (a[m].first+a[m].second <= 2*xs[p])
      l = m+1;
    else
      h = m;
  }
  if (l < i) {
    pll t = get_sum(root0[i], 0, 2*n, p+1, 2*n) - get_sum(root0[l], 0, 2*n, p+1, 2*n);
    r += t.second-xs[p]*t.first;
  }
  return r;
}

void conquer(bool left, long l, long h, long jl, long jh)
{
  if (l >= h) return;
  long m = l+h >> 1, opt = LONG_MAX, optj = jl;
  FOR(j, jl, jh) {
    long t = left ? calc_l(j, m) : calc_r(j, m);
    if (t < opt)
      opt = t, optj = j;
  }
  (left ? dp0[m] : dp[m]) = opt;
  conquer(left, l, m, jl, optj+1);
  conquer(left, m+1, h, optj, jh);
}

int main()
{
  ios_base::sync_with_stdio(0);
  long k, ans = 0;
  cin >> n >> k;
  REP(i, n) {
    cin >> a[i].first >> a[i].second;
    if (a[i].first > a[i].second)
      swap(a[i].first, a[i].second);
    xs[2*i] = a[i].first;
    xs[2*i+1] = a[i].second;
    ans += a[i].second-a[i].first;
  }
  sort(a, a+n, [](const pll& u, const pll& v) {
    return u.first+u.second < v.first+v.second;
  });
  sort(xs, xs+2*n);
  allo = 1;
  REP(i, n) {
    insert(root0[i+1], root0[i], 0, 2*n, scale(a[i].first), a[i].first);
    insert(root1[i+1], root1[i], 0, 2*n, scale(a[i].second), a[i].second);
  }
  dp[0] = 0;
  fill_n(dp+1, n, LONG_MAX);
  REP(i, k) {
    conquer(true, 0, 2*n, 0, n);
    conquer(false, 1, n+1, 0, 2*n);
  }
  cout << ans+2*dp[n] << endl;
}
