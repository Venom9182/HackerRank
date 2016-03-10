// Dilworth's theorem
#include <algorithm>
#include <cstdio>
#include <utility>
using namespace std;

typedef pair<int, int> pii;
#define REP(i, n) for (int i = 0; i < (n); i++)
#define se second

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100000;
pii a[N];
int b[N];

int main()
{
  int n = ri();
  REP(i, n) {
    int t = ri(), f = ri();
    a[i] = {t+f, t-f}; // antichain: f1+t1 > f2+t2 && t1-f1 < t2-f2
  }
  sort(a, a+n);
  reverse(a, a+n);
  int m = 0;
  REP(i, n) {
    int j = lower_bound(b, b+m, a[i].se) - b;
    b[j] = a[i].se;
    if (j == m)
      m++;
  }
  printf("%d\n", m);
}
