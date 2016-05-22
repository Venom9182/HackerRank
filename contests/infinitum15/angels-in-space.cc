#include <cmath>
#include <cstdio>
using namespace std;

#define REP(i, n) for (decltype(n) i = 0; i < (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const long N = 100;
double x[N], y[N], z[N];
#define sqr(x) ((x)*(x))
#define len(i, j) (sqr(x[i]-x[j])+sqr(y[i]-y[j])+sqr(z[i]-z[j]))

int main()
{
  long n = ri();
  REP(i, n) {
    x[i] = ri();
    y[i] = ri();
    z[i] = ri();
  }
  double s = 0, c = 0;
  REP(k, n)
    REP(j, k)
      REP(i, j) {
        double ij = len(i, j), jk = len(j, k), ki = len(k, i);
        s += acos((ij+jk-ki)/(2*sqrt((ij*jk))));
        c++;
      }
  printf("%.10lf\n", s/c);
}
