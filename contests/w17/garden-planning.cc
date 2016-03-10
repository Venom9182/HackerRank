#include <algorithm>
#include <cstdio>
#include <map>
using namespace std;

#define REP(i, n) FOR(i, 0, n)
#define FOR(i, a, b) for (int i = (a); i < (b); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int MOD = 1000000007, N = 100, M = 8, S = 844, P = 853;
char a[N][M+1];
int n, m;

inline int get(int s, int j)
{
  return s >> 3*j & 7;
}

void replace(int &s, int c)
{
  if (c)
    REP(i, m)
      if (get(s, i) == c)
        s |= 7 << 3*i;
}

int normalize(int s)
{
  int v[M], id = 1;
  fill_n(v, M, -1);
  v[0] = 0;
  REP(i, m) {
    int t = get(s, i);
    if (v[t] < 0)
      v[t] = id++;
    s ^= (t ^ v[t]) << 3*i;
  }
  return s;
}

bool connected(int s)
{
  REP(i, m)
    if (get(s, i) > 1)
      return false;
  return true;
}

int main()
{
  n = ri();
  m = ri();
  int remain = 0, ans = 0;
  REP(i, n) {
    scanf("%s", a[i]);
    remain += count(a[i], a[i]+m, '.');
  }

  map<int, int> cur;
  cur[0] = 1;
  if (! remain)
    ans++;
  REP(i, n)
    REP(j, m) {
      map<int, int> suc;
      remain -= a[i][j] == '.';
      for (auto &it: cur) {
        int s = it.first;
        if (a[i][j] != '.') {
          bool flag = ! get(s, j);
          for (int k = 0; k < m && ! flag; k++)
            flag = k != j && get(s, k) == get(s, j);
          if (flag)
            (suc[s & ~ (7 << 3*j)] += it.second) %= MOD;
        }
        if (a[i][j] != '#') {
          if (j)
            replace(s, get(s, j-1));
          if (get(s, j) != 7) {
            replace(s, get(s, j));
            s = normalize(s | 7 << 3*j);
            (suc[s] += it.second) %= MOD;
            if (! remain && connected(s))
              (ans += it.second) %= MOD;
          }
        }
      }
      cur.swap(suc);
    }

  printf("%d\n", ans);
}
