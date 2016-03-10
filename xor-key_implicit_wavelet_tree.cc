// implicit wavelet tree encoded with multi-level linked lists
// can also be seen as range tree with factional cascading
// See USACO Training Cow XOR for a simpler problem
#include <algorithm>
#include <cstdio>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); i++)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100000, M = 15, A = 1 << M;
int a[N], same[N], diff[M][N];

int main()
{
  for (int cc = ri(); cc--; ) {
    int n = ri(), q = ri();
    REP(i, n) {
      a[i] = ri();
      same[i] = i+1;
    }
    ROF(k, 0, M) {
      fill_n(diff[k], n, -1);
      REP(i, n)
        if (diff[k][i] < 0) {
          int j = i, xh = -1, xt, xx = n, yh = -1, yt, yy = n;
          while (j < n) {
            int jj = same[j];
            same[j] = n;
            if (a[j] & 1 << k) {
              if (~ xh) same[xt] = j;
              else xh = xx = j;
              xt = j;
              if (xx == n) xx = j;
              for (; yy < j; yy = same[yy])
                diff[k][yy] = j;
            } else {
              if (~ yh) same[yt] = j;
              else yh = yy = j;
              yt = j;
              if (yy == n) yy = j;
              for (; xx < j; xx = same[xx])
                diff[k][xx] = j;
            }
            j = jj;
          }
          if (~ xh) same[xt] = n;
          if (~ yh) same[yt] = n;
          for (; xx < n; xx = same[xx])
            diff[k][xx] = n;
          for (; yy < n; yy = same[yy])
            diff[k][yy] = n;
        }
    }
    while (q--) {
      int x = ri(), l = ri()-1, r = ri();
      ROF(k, 0, M)
        if (~ (x ^ a[l]) & 1 << k && diff[k][l] < r)
          l = diff[k][l];
      printf("%d\n", a[l]^x);
    }
  }
}
