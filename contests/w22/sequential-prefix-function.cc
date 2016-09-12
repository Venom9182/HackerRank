#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>
using namespace std;

#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

const long N = 200000;
long a[N], ans[N], pi[N];
vector<long> qs[N+1], st;
vector<pair<long, long>> ch[N+1];

void knuth_morris_pratt(long i, long x, long jj)
{
  for (auto& c: ch[x]) {
    a[i] = c.first;
    long j = jj;
    if (i)
      pi[i-1] = j >= 0 && a[i] == a[j] ? j ? pi[j-1] : -1 : j;
    while (j >= 0 && a[j] != c.first)
      j = j ? pi[j-1] : -1;
    j++;
    for (long q: qs[c.second])
      ans[q] = j;
    knuth_morris_pratt(i+1, c.second, j);
  }
}

int main()
{
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  long n, x, id = 1;
  char op;
  st.push_back(0);
  cin >> n;
  REP(i, n) {
    cin >> op;
    if (op == '+') {
      cin >> x;
      ch[st.back()].emplace_back(x, id);
      st.push_back(id++);
    } else
      st.pop_back();
    qs[st.back()].push_back(i);
  }
  knuth_morris_pratt(0, 0, -1);
  REP(i, n)
    cout << ans[i] << '\n';
}
