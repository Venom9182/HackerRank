#include <iostream>
#include <type_traits>
using namespace std;

#define REP1(i, n) for (remove_cv<remove_reference<decltype(n)>::type>::type i = 1; i <= (n); i++)

const long N = 100000;
long a[N];

bool f(long n, long k, long b)
{
  long l = n/b-(b-1)/2;
  if (n < (2*l+b-1)*b/2) l--;
  long r = l+b-1, d = 0;
  n -= (2*l+b-1)*b/2;
  a[0] = l;
  REP1(i, b-1) {
    long t = n/(b-i);
    n -= t*(b-i);
    d += t;
    a[i] = l+i+d;
  }
  return 1 <= l && a[b-1] <= k;
}

int main()
{
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  long cases, n, k, b;
  for (cin >> cases; cases--; ) {
    cin >> n >> k >> b;
    if (! f(n, k, b)) {
      cout << -1 << endl;
      continue;
    }
    cout << a[0];
    REP1(i, b-1)
      cout << ' ' << a[i];
    cout << endl;
  }
}
