/*
 * Construction: |set| = K = floor(2*n/3)+1
 * For a set of tuples whose cardinality = K, its sum = K*N >= K*(K-1)/2*3, thus K <= floor(2*n/3)+1
 */
#include <iostream>
#include <type_traits>
using namespace std;

#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

int main()
{
  long n, m;
  cin >> n;
  m = n*2/3+1;
  cout << m << '\n';
  REP(i, m) {
    long j = n%3 < 2 ? (n/3+i) % m : (n/3+2+i) % (m+1);
    cout << i << ' ' << j << ' ' << n-i-j << '\n';
  }
}
