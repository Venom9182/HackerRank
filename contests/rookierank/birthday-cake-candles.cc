#include <climits>
#include <iostream>
#include <type_traits>
using namespace std;

#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

const long N = 100000;
long a[N];

int main()
{
  ios_base::sync_with_stdio(0);
  long n, a, mx = LONG_MIN, c = 0;
  cin >> n;
  REP(i, n) {
    cin >> a;
    if (a > mx)
      mx = a, c = 1;
    else if (a == mx)
      c++;
  }
  cout << c << endl;
}
