#include <iostream>
#include <type_traits>
using namespace std;

#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

int main()
{
  long n, k, a, s = 0;
  cin >> n >> k;
  REP(i, n) {
    cin >> a;
    if (i != k) s += a;
  }
  cin >> a;
  s = a-s/2;
  if (s > 0) cout << s << endl;
  else cout << "Bon Appetit\n";
}
