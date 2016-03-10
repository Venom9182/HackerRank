#include <algorithm>
#include <cstdio>
using namespace std;

typedef long long ll;
#define REP(i, n) for (int i = 0; i < (n); i++)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

void readCF(int n, ll &p, ll &q)
{
  int r[9];
  REP(i, n)
    r[i] = ri();
  p = r[n-1];
  q = 1;
  ROF(i, 0, n-1) {
    ll t = p;
    p = q + p * r[i];
    q = t;
  }
}

void print(ll p, ll q)
{
  bool f = true;
  for(;;) {
    if (f) f = false;
    else putchar(' ');
    printf("%lld", p / q);
    p %= q;
    if (! p) break;
    swap(p, q);
  }
  puts("");
}

int main()
{
  int n1, n2, cases = 0;
  while (scanf("%d%d", &n1, &n2) == 2) {
    ll p1, q1, p2, q2;
    readCF(n1, p1, q1);
    readCF(n2, p2, q2);
    printf("Case %d:\n", ++cases);
    print(p1 * q2 + p2 * q1, q1 * q2);
    print(p1 * q2 - p2 * q1, q1 * q2);
    print(p1 * p2, q1 * q2);
    print(p1 * q2, p2 * q1);
  }
}
