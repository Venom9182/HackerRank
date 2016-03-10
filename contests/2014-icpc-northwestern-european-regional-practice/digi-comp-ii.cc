#include <cstdio>
using namespace std;

typedef long long ll;
#define REP(i, n) for (int i = 0; i < (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

ll rl()
{
  ll x;
  scanf("%lld", &x);
  return x;
}

const int M = 500000;
char st[M+1];
int l[M], r[M], d[M];
ll c[M];

int main()
{
  ll n = rl();
  int m = ri();
  REP(i, m) {
    scanf(" %c", &st[i]);
    l[i] = ri()-1;
    r[i] = ri()-1;
    if (~ l[i]) d[l[i]]++;
    if (~ r[i]) d[r[i]]++;
  }
  int top = -1;
  REP(i, m)
    if (! d[i])
      d[i] = top, top = i;
  c[0] = n;
  while (~ top) {
    int u = top;
    top = d[top];
    if (~ l[u]) {
      c[l[u]] += c[u]/2 + (c[u]%2 && st[u] == 'L');
      if (! --d[l[u]])
        d[l[u]] = top, top = l[u];
    }
    if (~ r[u]) {
      c[r[u]] += c[u]/2 + (c[u]%2 && st[u] == 'R');
      if (! --d[r[u]])
        d[r[u]] = top, top = r[u];
    }
    if (c[u]%2)
      st[u] = 'L'^'R'^st[u];
  }
  puts(st);
}
