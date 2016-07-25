#include <algorithm>
#include <iostream>
#include <type_traits>
using namespace std;

#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

const long R = 200;
char a[R][R+1], b[R][R+1];

int main()
{
  long r, c, n;
  cin >> r >> c >> n;
  REP(i, r)
    cin >> a[i];
  if (n%2 == 0) {
    fill_n(a[0], c, 'O');
    REP(i, r)
      cout << a[0] << '\n';
  } else {
    n = n-1>>1;
    if (n > 1)
      n = (n+1)%2+1;
    while (n--) {
      REP(i, r)
        REP(j, c)
          b[i][j] =
            a[i][j] == 'O' ||
            i && a[i-1][j] == 'O' ||
            i+1 < r && a[i+1][j] == 'O' ||
            j && a[i][j-1] == 'O' ||
            j+1 < c && a[i][j+1] == 'O' ? '.' : 'O';
      REP(i, r)
        copy_n(b[i], c, a[i]);
    }
    REP(i, r)
      cout << a[i] << '\n';
  }
}
