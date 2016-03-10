#include <cstdio>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

int c[100];

int main()
{
  int n = ri();
  REP(i, n)
    c[ri()]++;
  REP(i, 100)
    printf("%d%c", c[i], i == 99 ? '\n' : ' ');
}
