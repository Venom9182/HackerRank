#include <cstdio>
#include <set>
using namespace std;

#define REP(i, n) for (decltype(n) i = 0; i < (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

int main()
{
  int n = ri(), d = ri(), s = 0;
  set<int> c;
  REP(i, n) {
    int a = ri();
    c.insert(a);
    if (c.count(a-d) && c.count(a-2*d))
      s++;
  }
  printf("%d\n", s);
}
