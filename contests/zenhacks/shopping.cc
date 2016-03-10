#include <algorithm>
#include <cstdio>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); i++)
#define REP1(i, n) for (int i = 1; i <= (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 3000, M = 5, K = 5, ST = 7776;
double a[ST], b[ST], aa[ST], bb[ST];
int c[K+1], pw[K+1];

int main()
{
  int n = ri(), m = ri(), k = ri();
  pw[0] = 1;
  REP1(i, k)
    pw[i] = pw[i-1]*(m+1);
  int st = pw[k];
  a[0] = 1;
  b[0] = 0;
  REP(i, n) {
    fill_n(c, k, 0);
    fill_n(aa, st, 0.0);
    fill_n(bb, st, 0.0);
    REP(s, st) {
      int ix = min_element(c, c+k)-c, tim = c[ix], ss = 0;
      REP(j, k)
        ss += pw[j] * (c[j]-tim);
      REP1(j, m) {
        int sss = ss+pw[ix]*j;
        aa[sss] += a[s]/m;
        bb[sss] += (b[s]+tim)*a[s]/m;
      }
      for (int j = 0; (c[j]+=1) > m; j++)
        c[j] = 0;
    }
    double ans = 0;
    REP(s, st) {
      a[s] = aa[s];
      if (aa[s]) {
        ans += bb[s];
        b[s] = bb[s]/aa[s];
      }
    }
    printf("%lf\n", ans);
  }
}
