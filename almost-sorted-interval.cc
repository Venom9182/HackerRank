#include <cstdio>
#include <stack>
using namespace std;

typedef long long ll;
#define REP(i, n) for (int i = 0; i < (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 1000000;
int c[N];

int main()
{
  int n = ri();
  ll ans = 0;
  stack<int> inc, dec;
  REP(i, n) {
    int x = ri()-1;
    for (; ! inc.empty() && inc.top() > x; inc.pop())
      if (! --c[dec.top()])
        dec.pop();
    inc.push(x);
    c[x] = 1;
    for (; ! dec.empty() && dec.top() < x; dec.pop())
      c[x] += c[dec.top()];
    dec.push(x);
    ans += c[x];
  }
  printf("%lld\n", ans);
}
