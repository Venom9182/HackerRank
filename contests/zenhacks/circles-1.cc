#include <algorithm>
#include <cfloat>
#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;

#define ALL(x) (x).begin(), (x).end()
#define REP(i, n) for (int i = 0; i < (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const double EPS = 1e-9;

void pivot(vector<int> &N, vector<int> &B, vector<vector<double>> &A, vector<double> &c, double &v, int out, int in)
{
  int m = A.size(), n = c.size();
  A[out][in] = 1 / A[out][in];
  REP(j, n+1)
    if (j != in)
      A[out][j] *= A[out][in];
  REP(i, m)
    if (i != out) {
      REP(j, n+1)
        if (j != in)
          A[i][j] -= A[i][in] * A[out][j];
      A[i][in] *= - A[out][in];
    }
  v += c[in] * A[out][n];
  REP(j, n)
    if (j != in)
      c[j] -= c[in] * A[out][j];
  c[in] *= - A[out][in];
  swap(N[in], B[out]);
}

int simplexFeasibleInitial(vector<vector<double>> &A, vector<double> &c, double &v)
{
  int m = A.size(), n = c.size();
  vector<int> N(n), B(m);
  iota(ALL(N), 0);
  iota(ALL(B), n);
  for(;;) {
    int in = -1, out = -1;
    double outv = DBL_MAX;
    REP(j, n)
      if (c[j] > EPS && (in < 0 || N[j] < N[in]))
        in = j;
    if (in < 0) break;
    REP(i, m)
      if (A[i][in] > EPS) {
        double t = A[i][n] / A[i][in];
        if (t < outv-EPS || t < outv+EPS && A[i][n] < A[out][n])
          out = i, outv = t;
      }
    if (out < 0) return -1;
    pivot(N, B, A, c, v, out, in);
  }
  fill(ALL(c), 0);
  REP(i, m)
    if (B[i] < n)
      c[B[i]] = A[i][n];
  return 1;
}

int main()
{
  int n = ri(), m = n*(n-1)/2, s = 0;
  vector<vector<double>> A(m, vector<double>(n+1, 0));
  vector<double> x(n), y(n), c(n, 1);
  double v = 0;
  REP(i, n) {
    x[i] = ri();
    y[i] = ri();
    REP(j, i) {
      A[s][i] = A[s][j] = 1;
      A[s][n] = hypot(x[i]-x[j], y[i]-y[j]);
      s++;
    }
  }
  simplexFeasibleInitial(A, c, v);
  printf("%lf\n", 2*M_PI*v);
}
