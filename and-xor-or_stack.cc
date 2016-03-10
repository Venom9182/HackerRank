#include <algorithm>
#include <cstdio>
#include <stack>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

int main()
{
  stack<int> s;
  int n = ri(), ans = 0;
  REP(i, n) {
    int x = ri();
    while (! s.empty() && s.top() > x) {
      ans = max(ans, s.top() ^ x);
      s.pop();
    }
    if (! s.empty())
      ans = max(ans, s.top() ^ x);
    s.push(x);
  }
  printf("%d\n", ans);
}
