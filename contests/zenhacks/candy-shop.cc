#include <algorithm>
#include <cstdio>
using namespace std;

#define FOR(i, a, b) for (int i = (a); i < (b); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 250;
const int dom[] = {1,2,5,10,20,50,100};
int a[N+1];

int main()
{
  int n = ri();
  a[0] = 1;
  for (int x: dom)
    FOR(i, x, n+1)
      a[i] += a[i-x];
  printf("%d\n", a[n]);
}
