#include <iostream>
#include <type_traits>
using namespace std;

#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

const long N = 1000000;
char a[N+1];

int main()
{
  long n, h = 0, c = 0;
  cin >> n >> a;
  REP(i, n)
    if (a[i] == 'D')
      h--;
    else if (! ++h)
      c++;
  cout << c << endl;
}
