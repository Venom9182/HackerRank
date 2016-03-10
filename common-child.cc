#include <algorithm>
#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 5001;
char a[N], b[N];
int s[2][N];

int main()
{
  scanf("%s%s", a, b);
  int m = strlen(a), n = strlen(b);
  REP(i, m)
    REP(j, n)
      s[i+1&1][j+1] = a[i] == b[j] ? s[i&1][j]+1 : max(s[i&1][j+1], s[i+1&1][j]);
  printf("%d\n", s[m&1][n]);
}
