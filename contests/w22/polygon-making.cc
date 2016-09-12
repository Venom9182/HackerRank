#include <algorithm>
#include <iostream>
#include <type_traits>
using namespace std;

#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

long a[50];

int main()
{
  long n, tot = 0, s = 0;
  cin >> n;
  REP(i, n) {
    cin >> a[i];
    tot += a[i];
  }
  if (n < 3)
    cout << 3-n;
  else {
    s = *max_element(a, a+n);
    cout << s/(tot-s);
  }
  cout << endl;
}
