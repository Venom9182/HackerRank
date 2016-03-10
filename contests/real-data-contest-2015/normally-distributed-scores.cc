#include <cmath>
#include <cstdio>
using namespace std;

int main()
{
  double l = 2000, h = 1e9;
  while (h-l > 1e-3) {
    double m = (l+h)/2;
    if (0.5 * (1 + erf((m-2000)/200 * M_SQRT1_2)) < 0.9)
      l = m;
    else
      h = m;
  }
  printf("%.2lf\n", (l+h)/2);
}
