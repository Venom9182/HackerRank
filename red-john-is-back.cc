#include <algorithm>
#include <cstdio>
#include <numeric>
using namespace std;
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int P = 1822474;
int prime[P];

int main()
{
  int a[40];
  fill_n(a, 4, 1);
  FOR(i, 4, 41)
    a[i] = a[i-1]+a[i-4];
  fill_n(prime, P, 1);
  prime[0] = prime[1] = 0;
  for (int i = 2; i*i <= P; i++)
    if (prime[i])
      for (int j = i*i; j < P; j += i)
        prime[j] = 0;
  partial_sum(prime, prime+P, prime);
  for (int cc = ri(); cc--; )
    printf("%d\n", prime[a[ri()]]);
}
