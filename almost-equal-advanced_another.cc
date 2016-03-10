#include <algorithm>
#include <cstdio>
using namespace std;

typedef long long ll;
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) for (int i = 0; i < (n); i++)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100000, Q = 100000, B = 317;
int b, a[N], c[N], cc[N][B], d1[N][B], x[B], y[B], z[2*B];
ll d2[B][B];

ll calc(int a[], int n, int k)
{
  ll ret = 0;
  int j = 0, jj = 0;
  REP(i, n) {
    for (; j < n && a[j] < a[i]-k; j++);
    for (; jj < n && a[jj] <= a[i]+k; jj++);
    ret += jj-j;
  }
  return (ret-n)/2;
}

int main()
{
  int n = ri(), k = ri();
  REP(i, n)
    a[i] = ri();
  int m = ri();
  iota(c, c+n, 0);
  sort(c, c+n, [](int i, int j) { return a[i] < a[j]; });
  int b = sqrt(double(n)), nb = (n+b-1)/b;
  REP(p, nb) {
    int bgn = b*p, end = min(bgn+b, n), nn = 0;
    REP(i, n)
      if (bgn <= c[i] && c[i] < end)
        cc[p][nn++] = c[i];
    int j = 0, jj = 0;
    REP(i, n) {
      for (; j < nn && a[cc[p][j]] < a[c[i]]-k; j++);
      for (; jj < nn && a[cc[p][jj]] <= a[c[i]]+k; jj++);
      d1[c[i]][p] = jj-j;
    }
    FOR(i, bgn, end)
      d1[i][p]--;
  }
  REP(p, nb)
    FOR(q, p, nb) {
      int bgn = b*p, end = min(bgn+b, n);
      FOR(i, bgn, end)
        d2[p][q] += d1[i][q];
      if (p == q)
        d2[p][q] /= 2;
    }
  ROF(p, 0, nb)
    FOR(q, p+1, nb)
      d2[p][q] += d2[p+1][q]+d2[p][q-1]-d2[p+1][q-1];
  REP(i, n)
    FOR(j, 1, nb)
      d1[i][j] += d1[i][j-1]; 

  REP(i, m) {
    int l = ri(), r = ri(), lb = l/b, rb = r/b;
    ll ans = 0;
    if (lb+1 <= rb-1) {
      ans += d2[lb+1][rb-1];
      FOR(j, l, b*lb+b)
        ans += d1[j][rb-1]-d1[j][lb];
      FOR(j, b*rb, r+1)
        ans += d1[j][rb-1]-d1[j][lb];
    }
    int nx = 0, ny = 0, bgn = b*lb, end = min(bgn+b, r+1), nn = min(bgn+b, n)-bgn;
    REP(j, nn)
      if (l <= cc[lb][j] && cc[lb][j] < end)
        x[nx++] = a[cc[lb][j]];
    if (lb == rb)
      ans += calc(x, nx, k);
    else {
      bgn = b*rb;
      nn = min(bgn+b, n)-bgn;
      REP(j, nn)
        if (bgn <= cc[rb][j] && cc[rb][j] <= r)
          y[ny++] = a[cc[rb][j]];
      merge(x, x+nx, y, y+ny, z);
      ans += calc(z, nx+ny, k);
    }
    printf("%lld\n", ans);
  }
}
