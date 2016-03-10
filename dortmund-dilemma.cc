/* Problem
   Number of strings of length K with exactly K different characters, having at least one proper prefix & suffix in common

   f[n][k]: Number of strings of length N consisting of characters 1..K (not necessarily all of them), having no proper prefix & suffix in common
   f[n][1] = n

   Lemma: if a string of length N has proper prefix & suffix in common, it has a proper prefix & suffix of length X that 2X <= N

   if n is even, the strings of f[n][k] can be constructed be inserting a character in the middle of f[n-1][k]
   if n is odd, inserting a charater in the middle of f[n-1][k], exactly f[n/2][k] of them are invalid
 */
#include <algorithm>
#include <cstdio>
using namespace std;

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) for (int i = 0; i < (n); i++)
#define REP1(i, n) for (int i = 1; i <= (n); i++)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100000, K = 26, MOD = 1000000009;
long c[K+1][K+1], f[N+1][K+1], g[N+1][K+1];

int main()
{
  REP(i, K+1) {
    c[i][0] = c[i][i] = 1;
    FOR(j, 1, i)
      c[i][j] = (c[i-1][j-1]+c[i-1][j]) % MOD;
  }
  iota(f[1], f[1]+K+1, 0);
  REP1(j, K) {
    long jn = j;
    FOR(i, 2, N+1) {
      jn = jn*j % MOD;
      f[i][j] = (i % 2 ? f[i-1][j]*j : f[i-1][j]*j-f[i/2][j]) % MOD;
      g[i][j] = jn-f[i][j];
      FOR(k, 1, j)
        g[i][j] = (g[i][j]-g[i][k]*c[j][k]) % MOD;
    }
  }

  ROF(_, 0, ri()) {
    int n = ri(), k = ri();
    printf("%ld\n", (g[n][k]*c[26][k]%MOD+MOD) % MOD);
  }
}
