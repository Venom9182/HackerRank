#include <cmath>
#include <iostream>
using namespace std;

double n, p, s, v;

double f(double c)
{
  return n*pow(log(n)/log(2), sqrt(2)*c)/p+s/(c*v);
}

double goldenSectionSearch(double a, double b)
{
  double r = (sqrt(5)-1)/2;
  double x1 = b-(b-a)*r, x2 = a+(b-a)*r, f1 = f(x1), f2 = f(x2);
  while (b-a > 1e-10) {
    if (f1 < f2) {
      b = x2; x2 = x1; f2 = f1;
      x1 = b-(b-a)*r; f1 = f(x1);
    } else {
      a = x1; x1 = x2; f1 = f2;
      x2 = a+(b-a)*r; f2 = f(x2);
    }
  }
  return (a+b)/2;
}

int main()
{
  cin >> n >> p >> s >> v;
  p *= 1e9;
  double c = goldenSectionSearch(1, 40);
  cout.setf(ios::fixed);
  cout.precision(46);
  cout << f(c)+s/v << ' ' << c << endl;
}
