#include <iostream>
#include <type_traits>
using namespace std;

#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

int main()
{
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  long cases, n, k;
  for (cin >> cases; cases--; ) {
    cin >> n >> k;
    if (! k)
      REP(i, n)
        cout << i+1 << " \n"[i == n-1];
    else if (n%k || n/k%2)
      cout << -1 << '\n';
    else
      for (long i = 0; i < n; i += 2*k) {
        REP(j, k)
          cout << i+j+k+1 << ' ';
        REP(j, k)
          cout << i+j+1 << " \n"[i+j+k+1 == n];
      }
  }
}
