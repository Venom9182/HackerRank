#include <algorithm>
#include <climits>
#include <cstdio>
#include <map>
#include <set>
using namespace std;

typedef long long ll;
#define REP(i, n) for (int i = 0; i < (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 2000;
int m, a[N], num[N], nxt[N];

ll gcd(ll a, ll b)
{
  ll t;
  while (b)
    t = a%b, a = b, b = t;
  return a;
}

int next(int i)
{
  if (num[i])
    return i;
  return nxt[i] = nxt[i] == i ? next((i+1)%m) : next(nxt[i]);
}

int main()
{
  int n = ri(), s = ri(), delay = ri();
  ll mx = 0, mn = LLONG_MAX, tot = 0;
  set<int> pos;
  map<int, int> p2i, i2p;
  REP(i, n)
    pos.insert(a[i] = ri());
  for (int p: pos) {
    p2i[p] = m;
    i2p[m++] = p;
  }
  REP(i, m) {
    fill_n(num, m, 0);
    REP(i, n)
      num[p2i[a[i]]]++;
    REP(i, m)
      nxt[i] = i;
    ll time = 0;
    int p = i2p[i];
    REP(j, n) {
      int q = p;
      auto it = pos.lower_bound(p);
      if (it == pos.end())
        it = pos.begin();
      int pi = next(p2i[*it]);
      p = i2p[pi];
      num[pi]--;
      time += (p-q+s)%s+delay;
      p = (p+delay)%s;
    }
    ll fr = (i2p[i]-i2p[(i+m-1)%m]+s)%s;
    if (! fr)
      fr = s;
    mn = min(mn, time);
    mx = max(mx, time+fr-1);
    tot += time*fr+fr*(fr-1)/2;
  }
  ll d = gcd(tot, s);
  printf("%lld\n%lld\n%lld/%lld\n", mn, mx, tot/d, s/d);
}
