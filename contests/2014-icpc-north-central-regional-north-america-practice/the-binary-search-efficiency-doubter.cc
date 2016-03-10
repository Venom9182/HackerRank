#include <cstdio>
using namespace std;

#define FOR(i, a, b) for (int i = (a); i < (b); i++)

const int N = 10000000;
int a[N];

int main()
{
  int cases = 0, n;
  FOR(i, 1, N)
    a[i] = i + a[i/2] + a[(i-1)/2];
  while (scanf("%d", &n) == 1)
    printf("Case %d: %d\n", ++cases, a[n]);
}
