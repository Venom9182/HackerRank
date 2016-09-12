#include <algorithm>
#include <iostream>
#include <type_traits>
using namespace std;

#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)

const long N = 10810801;
long f[N+1], pr[714823], np = 0;
bool sieved[N];

int main()
{
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  f[1] = 1;
  FOR(i, 2, N) {
    if (! sieved[i]) {
      f[i] = 2;
      pr[np++] = i;
    }
    for (long j = 0; j < np && i*pr[j] < N; j++) {
      sieved[i*pr[j]] = true;
      long t = i, c = 1;
      for (; t%pr[j] == 0; t /= pr[j])
        c++;
      f[i*pr[j]] = f[t]*(c+1);
      if (c > 1) break;
    }
  }
  FOR(i, 2, N)
    f[i] = max(f[i], f[i-1]);
  for (long t = f[1], j = 1, i = 1; i < N; ) {
    while (++j < N && f[j] == t);
    if (j < N)
      t = f[j];
    while (i < j)
      f[++i] = j;
  }
  long q, n;
  for (cin >> q; q--; ) {
    cin >> n;
    cout << f[n] << '\n';
  }
}
