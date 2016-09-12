#include <algorithm>
#include <iostream>
#include <type_traits>
using namespace std;

#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

const long N = 100000;
long a[N], b[N];

int main()
{
  long n, pos = 0, neg = 0;
  cin >> n;
  REP(i, n)
    cin >> a[i];
  REP(i, n)
    cin >> b[i];
  sort(a, a+n);
  sort(b, b+n);
  REP(i, n) {
    b[i] -= a[i];
    if (b[i] > 0) pos += b[i];
    else neg -= b[i];
  }
  cout << (pos == neg ? pos : -1) << endl;
}
