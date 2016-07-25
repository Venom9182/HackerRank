#include <algorithm>
#include <iostream>
#include <type_traits>
#include <vector>
using namespace std;

#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define REP1(i, n) for (remove_cv<remove_reference<decltype(n)>::type>::type i = 1; i <= (n); i++)

const long N = 50000, C = 100000, F = 20+1, MOD = 1000000009;
long fac[C+1], f[5], p[N], tr[F][5][F], dp[N][5][F];
vector<long> adj[N];

#define A(x, y) (((x) + (y)) % MOD)
#define M(x, y) ((x) * (y) % MOD)
#define D(x, y) ((x) * inv(y) % MOD)

long S(long r, long x, long n)
{
  for (; n; n >>= 1) {
    if (n & 1)
      r = M(r, x);
    x = M(x, x);
  }
  return r;
}

long inv(long a)
{
  long r = 1;
  for (; a > 1; a = MOD%a)
    r = M(r, MOD-MOD/a);
  return r;
}

long binom(long n, long m)
{
  return n >= m ? D(fac[n], M(fac[m], fac[n-m])) : 0;
}

long tetrahedron(long c) { return A(D(S(11,c,2),12), D(S(1,c,4),12)); }
long cube(long c) { return A(A(A(D(S(1,c,2),3), D(S(1,c,3),2)), D(S(1,c,4),8)), D(S(1,c,6),24)); }
long octahedron(long c) { return A(A(D(S(1,c,2),4), D(S(17,c,4),24)), D(S(1,c,8),24)); }
long dodecahedron(long c) { return A(A(D(S(11,c,4),15), D(S(1,c,6),4)), D(S(1,c,12),60)); }
long icosahedron(long c) { return A(A(A(D(S(2,c,4),5), D(S(1,c,8),3)), D(S(1,c,10),4)), D(S(1,c,20),60)); }
long nf;

void dfs(long u, long p)
{
  for (long v: adj[u])
    if (v != p) {
      dfs(v, u);
      REP(j, nf)
        REP1(jj, f[j]) {
          long t = 0;
          REP(k, nf)
            if (j != k)
              REP1(kk, f[k])
                t = A(t, M(dp[v][k][kk], tr[jj][k][kk]));
          dp[u][j][jj] = M(dp[u][j][jj], t);
        }
    }
}

int main()
{
  long n, nc;
  cin >> n >> nc >> nf;
  REP(i, nf)
    cin >> f[i];
  REP1(i, n-1) {
    long p;
    cin >> p;
    adj[p-1].push_back(i);
  }
  long (*fns[F])(long);
  fns[4] = tetrahedron;
  fns[6] = cube;
  fns[8] = octahedron;
  fns[12] = dodecahedron;
  fns[20] = icosahedron;

  fac[0] = 1;
  REP1(i, max(nc, F-1))
    fac[i] = M(fac[i-1], i);
  REP(j, nf) {
    long t[F];
    t[0] = 0;
    REP1(jj, f[j]) {
      auto fn = fns[f[j]];
      t[jj] = fn(jj);
      REP1(l, jj-1)
        t[jj] = (t[jj] - binom(jj, l) * t[l]) % MOD;
      REP(i, F)
        tr[i][j][jj] = A(tr[i][j][jj], M(binom(nc-i, jj), t[jj]));
    }
  }
  REP(i, n)
    REP(j, nf)
      fill_n(dp[i][j]+1, f[j], 1);
  dfs(0, -1);
  long ans = 0;
  REP(i, nf)
    REP1(ii, f[i])
      ans = A(ans, M(dp[0][i][ii], tr[0][i][ii]));
  if (ans < 0)
    ans += MOD;
  cout << ans << endl;
}
