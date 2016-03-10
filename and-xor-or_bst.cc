#include <algorithm>
#include <cstdio>
#include <utility>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef pair<int, int> pii;
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define fi first
#define se second

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 1000000;
pii a[N];

int main()
{
  tree<int, int> t;
  int n = ri(), ans = 0;
  REP(i, n)
    a[i] = {ri(), i};
  sort(a, a+n);
  REP(i, n) {
    t[a[i].se] = a[i].fi;
    auto succ = t.upper_bound(a[i].se);
    if (succ != t.end())
      ans = max(ans, a[i].fi ^ succ->se);
    auto pred = t.find(a[i].se);
    if (pred != t.begin()) {
      --pred;
      ans = max(ans, a[i].fi ^ pred->se);
    }
  }
  printf("%d\n", ans);
}
