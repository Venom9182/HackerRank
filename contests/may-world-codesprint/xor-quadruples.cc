#include <algorithm>
#include <iostream>
#include <type_traits>
#include <unordered_map>
using namespace std;

#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP1(i, n) for (remove_cv<remove_reference<decltype(n)>::type>::type i = 1; i <= (n); i++)

int main()
{
  long x[4], a, b, c, d, s = 0, t = 0;
  unordered_map<long, long> e;
  cin >> x[0] >> x[1] >> x[2] >> x[3];
  sort(x, x+4);
  a = x[0];
  b = x[1];
  c = x[2];
  d = x[3];
  REP1(i, c) {
    if (i <= b)
      REP1(k, min(a, i))
        e[k^i]++;
    FOR(j, i, d+1) {
      if (e.count(i^j))
        s += e[i^j];
      if (i <= a)
        t += i*(i+1)/2;
      else
        t += a*(a+1)/2+(min(b,i)-a)*a;
    }
  }
  cout << t-s << endl;
}
