#include <algorithm>
#include <cstdio>
#include <map>
#include <stack>
#include <utility>
using namespace std;

#define REP(i, n) for (decltype(n) i = 0; i < (n); i++)

const int N = 300000, MOD = 1e9+7;
int a[N];
map<int, int> l, r, d, rnk;

int main()
{
  int n, x;
  map<int, int> m;
  scanf("%d", &n);
  REP(i, n) {
    scanf("%d", &x);
    rnk[x] = i;
    a[i] = x;
    char p = 'p';
    int pp = -1;
    int lv = 0;
    auto it = m.lower_bound(x);
    if (it != m.end())
      lv = it->second+1, p = 'l', pp = it->first;
    if (it != m.begin()) {
      --it;
      if (it->second+1 > lv)
        lv = it->second+1, p = 'r', pp = it->first;
    }
    if (p == 'l')
      l[pp] = x;
    if (p == 'r')
      r[pp] = x;
    m[x] = lv;
  }

  stack<pair<int,int> > st;
  pair<int, int> p{a[0], 1};
  for(;;) {
    while (p.second >= 0) {
      st.push(p);
      if (l.count(p.first))
        p = {l[p.first], p.second*2%MOD};
      else
        p.second = -1;
    }
    if (st.empty()) break;
    p = st.top();
    st.pop();
    a[rnk[p.first]] = p.second;
    if (r.count(p.first))
      p = {r[p.first], (p.second*2+1)%MOD};
    else
      p.second = -1;
  }
  REP(i, n)
    printf("%d ", a[i]);
  puts("");
}
