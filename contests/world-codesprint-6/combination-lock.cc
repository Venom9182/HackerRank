#include <cstdlib>
#include <iostream>
#include <type_traits>
using namespace std;

#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

int main()
{
  long a[5], b, s = 0;
  REP(i, 5)
    cin >> a[i];
  REP(i, 5) {
    cin >> b;
    b = abs(b-a[i]);
    s += min(b, 10-b);
  }
  cout << s << endl;
}
