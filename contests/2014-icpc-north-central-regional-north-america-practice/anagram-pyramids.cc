#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <string>
#include <unordered_set>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int L = 31;
unordered_set<string> a[L];

bool f(const string &b, const string &c)
{
  if (b == c)
    return true;
  REP(i, c.size()) {
    string cc = c;
    cc.erase(i, 1);
    if (a[cc.size()].count(cc) && f(b, cc))
      return true;
  }
  return false;
}

int main()
{
  char b[L], c[L];
  int cases = 0, n;
  auto g = [](char *b, int l) {
    transform(b, b+l, b, ::tolower);
    sort(b, b+l);
  };
  while (scanf("%d", &n) == 1) {
    REP(i, L)
      a[i].clear();
    REP(i, n) {
      scanf("%s", b);
      int l = strlen(b);
      g(b, l);
      a[l].insert(b);
    }
    printf("Case %d:\n", ++cases);
    int m = ri();
    REP(i, m) {
      scanf("%s%s", b, c);
      int l0 = strlen(b), l1 = strlen(c);
      g(b, l0);
      g(c, l1);
      puts(a[l0].count(b) && a[l1].count(c) && f(b, c) ? "yes" : "no");
    }
  }
}
