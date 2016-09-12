#include <algorithm>
#include <cctype>
#include <cstring>
#include <iostream>
#include <type_traits>
using namespace std;

#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

const long N = 1000;
char a[N+1], b[N+1], c[N+1][N+1];

int main()
{
  long cases, m, n;
  for (cin >> cases; cases--; ) {
    cin >> a >> b;
    m = strlen(a);
    n = strlen(b);
    fill_n(c[0]+1, n, 0);
    c[0][0] = 1;
    REP(i, m) {
      c[i+1][0] = c[i][0] && islower(a[i]);
      REP(j, n)
        c[i+1][j+1] = c[i][j] && (islower(b[j]) ? a[i] == b[j] : toupper(a[i]) == b[j]) || islower(a[i]) && c[i][j+1];
    }
    cout << (c[m][n] ? "YES" : "NO") << endl;
  }
}
