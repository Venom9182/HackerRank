#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <type_traits>
using namespace std;

#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

int main()
{
  long a[9], p[9], ans = 81;
  REP(i, 9)
    cin >> a[i];
  iota(p, p+9, 1);
  do {
    if (p[0]+p[1]+p[2] == 15 &&
        p[3]+p[4]+p[5] == 15 &&
        p[6]+p[7]+p[8] == 15 &&
        p[0]+p[3]+p[6] == 15 &&
        p[1]+p[4]+p[7] == 15 &&
        p[2]+p[5]+p[8] == 15 &&
        p[0]+p[4]+p[8] == 15 &&
        p[2]+p[4]+p[6] == 15) {
      long t = 0;
      REP(i, 9)
        t += abs(p[i]-a[i]);
      ans = min(ans, t);
    }
  } while (next_permutation(p, p+9));
  cout << ans << endl;
}
