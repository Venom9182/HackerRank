#include <algorithm>
#include <iostream>
#include <type_traits>
using namespace std;

#define PER1(i, n) for (remove_cv<remove_reference<decltype(n)>::type>::type i = (n); i > 0; i--)
#define REP1(i, n) for (remove_cv<remove_reference<decltype(n)>::type>::type i = 1; i <= (n); i++)

const long N = 100001;
long a[N], b[N], c[N];

int main()
{
  ios_base::sync_with_stdio(0);
  long n1, n2, n3;
  cin >> n1 >> n2 >> n3;
  PER1(i, n1) cin >> a[i];
  PER1(i, n2) cin >> b[i];
  PER1(i, n3) cin >> c[i];
  REP1(i, n1) a[i] += a[i-1];
  REP1(i, n2) b[i] += b[i-1];
  REP1(i, n3) c[i] += c[i-1];
  while (a[n1] != b[n2] || b[n2] != c[n3] || c[n3] != a[n1]) {
    long t = min(min(a[n1], b[n2]), c[n3]);
    t < a[n1] && n1--;
    t < b[n2] && n2--;
    t < c[n3] && n3--;
  }
  cout << a[n1] << endl;
}
