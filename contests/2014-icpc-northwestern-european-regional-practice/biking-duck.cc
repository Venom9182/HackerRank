#include <algorithm>
#include <cmath>
#include <iostream>
#include <utility>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); i++)

const int N = 1000;
double vw, vb, m[2][2], s[2][2], b[N][2], first[N], second[N];

double dist(double p[2], double q[2])
{
  return hypot(p[0]-q[0], p[1]-q[1]);
}

double bike(double p[2], double q[2])
{
  return dist(p, q) / vb;
}

double walk(double p[2], double q[2])
{
  return dist(p, q) / vw;
}

double transfer(double p[2], double q[2], double r[2], bool twice)
{
  double f(double p[2], double q[2], bool twice);
  return twice ? walk(p, q) + f(q, r, false) : bike(p, q) + walk(q, r);
}

// ! twice : p --bike-> border --walk-> q
// twice   : p --walk-> border --bike-> border --walk->q
double f(double p[2], double q[2], bool twice)
{
  double ret = 1e9;
  REP(x, 2) REP(y, 2) {
    double l = m[0][y], h = m[1][y];
    REP(_, 100) {
      double u[2] = {l+(h-l)/3, m[x][1-y]},
        v[2] = {h-(h-l)/3, m[x][1-y]};
      if (y == 1)
        swap(u[0], u[1]), swap(v[0], v[1]);
      if (transfer(p, u, q, twice) > transfer(p, v, q, twice))
        l = u[y];
      else
        h = v[y];
    }
    double u[2] = {(l+h)/2, m[x][1-y]};
    if (y == 1)
      swap(u[0], u[1]);
    ret = min(ret, transfer(p, u, q, twice));
  }
  return ret;
}

int main()
{
  int n;
  cin >> vw >> vb;
  REP(i, 2) REP(j, 2)
    cin >> m[i][j];
  REP(i, 2) REP(j, 2)
    cin >> s[i][j];
  cin >> n;
  REP(i, n) REP(j, 2)
    cin >> b[i][j];
  double opt = min(walk(s[0], s[1]), f(s[0], s[1], true));
  REP(i, n) {
    first[i] = min(walk(s[0], b[i]), f(b[i], s[0], false));
    second[i] = min(walk(b[i], s[1]), f(b[i], s[1], false));
  }
  REP(i, n) REP(j, n)
    opt = min(opt, first[i] + bike(b[i], b[j]) + second[j]);
  cout.precision(6);
  cout.setf(ios::fixed);
  cout << opt << endl;
}
