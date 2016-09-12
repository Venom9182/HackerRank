#include <algorithm>
#include <iostream>
#include <type_traits>
using namespace std;

#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

const long N = 128;
long a[2*N][2*N];

int main()
{
  long cases, n;
  for (cin >> cases; cases--; ) {
    long s = 0;
    cin >> n;
    REP(i, 2*n)
      REP(j, 2*n)
        cin >> a[i][j];
    REP(i, n)
      REP(j, n)
        s += max(max(a[i][j], a[2*n-1-i][j]), max(a[i][2*n-1-j], a[2*n-1-i][2*n-1-j]));
    cout << s << endl;
  }
}
