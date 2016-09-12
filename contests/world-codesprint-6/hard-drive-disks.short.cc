/*
 * answer = dp[K][N]
 *
 * dp[k+1][i] = min{dp[k][j] + C(j, i)}
 *
 * where
 * C(j, i) = let (small, large) = splitAt(j-i, sort({a[j..i-1].first, a[j..i-1].second}))
 *           in sum(large) - sum(small)
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
long n, prefix[2*N+1], dp[N+1], dp0[N+1], xs[2*N], allo;
int root[N+1], child[2*N*V][2];

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

long query(long l, long h)
{
  long r = prefix[2*h]-prefix[2*l], rt0 = root[2*l], rt1 = root[2*h], k = h-l;
  l = 0;
  h = 2*n;
  while (k && l < h-1) {
    long m = l+h >> 1, t = seg[child[rt1][0]].first-seg[child[rt0][0]].first;
    if (k < t) {
      h = m;
      rt0 = child[rt0][0];
      rt1 = child[rt1][0];
    } else {
      k -= t;
      r -= (seg[child[rt1][0]].second-seg[child[rt0][0]].second)*2;
      l = m;
      rt0 = child[rt0][1];
      rt1 = child[rt1][1];
    }
  }
  if (k)
    r -= seg[rt1].second/seg[rt1].first*k*2;
  return r;
}

void conquer(long l, long h, long jl, long jh)
{
  if (l >= h) return;
  long m = l+h >> 1, opt = LONG_MAX, optj = jl;
  FOR(j, jl, min(jh, m))
    if (dp[j] < LONG_MAX) {
      long t = dp[j] + query(j, m);
      if (t < opt)
        opt = t, optj = j;
    }
  dp0[m] = opt;
  conquer(l, m, jl, optj+1);
  conquer(m+1, h, optj, jh);
}

int main()
{
  ios_base::sync_with_stdio(0);
  long k, ans = 0;
  cin >> n >> k;
  REP(i, n) {
    cin >> a[i].first >> a[i].second;
    xs[2*i] = a[i].first;
    xs[2*i+1] = a[i].second;
  }
  sort(a, a+n, [](const pll& u, const pll& v) {
    return u.first+u.second < v.first+v.second;
  });
  REP(i, n) {
    prefix[2*i+1] = prefix[2*i]+a[i].first;
    prefix[2*i+2] = prefix[2*i+1]+a[i].second;
  }
  sort(xs, xs+2*n);
  allo = 1;
  REP(i, n) {
    insert(root[2*i+1], root[2*i], 0, 2*n, scale(a[i].first), a[i].first);
    insert(root[2*i+2], root[2*i+1], 0, 2*n, scale(a[i].second), a[i].second);
  }
  dp[0] = 0;
  fill_n(dp+1, n, LONG_MAX);
  REP(i, k) {
    conquer(1, n+1, 0, n);
    copy_n(dp0+1, n, dp+1);
  }
  cout << dp[n] << endl;
}
