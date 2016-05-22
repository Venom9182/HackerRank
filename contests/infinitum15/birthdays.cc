#include <cstdio>
using namespace std;

#define REP(i, n) for (long i = 0; i < (n); i++)
#define ROF(i, a, b) for (long i = (b); --i >= (a); )

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

double rd()
{
  double x;
  scanf("%lf", &x);
  return x;
}

int main()
{
  ROF(_, 0, ri()) {
    double p = rd();
    for (long n = 1; ; n++) {
      long x = n/4, y = n-x;
      double s = 1;
      REP(i, y)
        s *= (365-i)/365.0;
      REP(i, x)
        s *= (366-i-y)/366.0;
      if (s <= 1-p) {
        printf("%ld\n", n);
        break;
      }
    }
  }
}
