#include <algorithm>
#include <iostream>
#include <type_traits>
using namespace std;

#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

const long N = 2318;
long c[N][N];
struct P {
  long x, y, i;
  P operator-(const P& rhs) const {
    return {x-rhs.x, y-rhs.y, i};
  }
  long operator*(const P& rhs) const {
    return x*rhs.y-y*rhs.x;
  }
  bool operator!=(const P& rhs) const {
    return x != rhs.x || y != rhs.y;
  }
  P rot() const {
    return {y, - x, i};
  }
} a[N], b[N*2];

int main()
{
  long n;
  cin >> n;
  REP(i, n) {
    a[i].i = i;
    cin >> a[i].x >> a[i].y;
  }
  REP(i, n) {
    long m = 0;
    REP(j, n)
      if (a[j] != a[i])
        b[m++] = a[j]-a[i];
    sort(b, b+m, [&](const P& u, const P& v) {
      char fu = u.x >= 0 ? u.y > 0 : u.y >= 0,
           fv = v.x >= 0 ? v.y > 0 : v.y >= 0;
      if (fu != fv) return fu < fv;
      return u*v < 0;
    });
    copy_n(b, m, b+m);
    for (long k = 0, j = 0, jj = 0; j < m; j = jj) {
      while (++jj < m && b[j]*b[jj] == 0);
      P t = b[j].rot();
      for (k = max(k, jj); k < j+m && b[j]*b[k] <= 0 && b[k]*t < 0; k++);
      FOR(x, j, jj)
        c[i][b[x].i] = k-jj;
    }
  }
  long ans = 0;
  REP(i, n)
    FOR(j, i+1, n)
      ans += c[i][j]*c[j][i];
  cout << ans << endl;
}
