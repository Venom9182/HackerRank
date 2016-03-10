#include <cstdio>
#include <utility>
using namespace std;

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) for (int i = 0; i < (n); i++)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100000, NN = 131072;
char a[2][N+1];
int same[2*NN], first[2*NN][2];

void apply(int i, int v)
{
  same[i] = v;
  first[i][v] = (i << __builtin_clz(i)-__builtin_clz(NN)) - NN;
  first[i][v^1] = -1;
}

void mconcat(int i)
{
  REP(d, 2)
    first[i][d] = ~ first[2*i][d] ? first[2*i][d] : first[2*i+1][d];
}

void untag(int i)
{
  if (i < 0 || i >= NN) return;
  i += NN;
  for (int j, h = __builtin_ctz(NN); h; h--)
    if (~ same[j = i>>h]) {
      apply(2*j, same[j]);
      apply(2*j+1, same[j]);
      same[j] = -1;
    }
}

int getFirst(int l, int r, int v)
{
  int ret = -1;
  untag(l-1);
  untag(r);
  for (l += NN, r += NN; l < r; l >>= 1, r >>= 1) {
    if (l & 1 && ~ first[l++][v])
      return first[l-1][v];
    if (r & 1 && ~ first[--r][v])
      ret = first[r][v];
  }
  return ret;
}

void setSame(int l, int r, int v)
{
  untag(l-1);
  untag(r);
  bool lf = false, rf = false;
  for (l += NN, r += NN; l < r; ) {
    if (l & 1) lf = true, apply(l++, v);
    l >>= 1;
    if (lf) mconcat(l-1);
    if (r & 1) rf = true, apply(--r, v);
    r >>= 1;
    if (rf) mconcat(r);
  }
  for (l--; l >>= 1, r >>= 1; ) {
    if (lf || l == r) mconcat(l);
    if (rf && l != r) mconcat(r);
  }
}

int main()
{
  int n = ri(), q = ri(), c = 0;
  scanf("%s%s", a[0], a[1]);
  REP(i, n) {
    int t = a[0][n-1-i]-'0'+a[1][n-1-i]-'0'+c;
    apply(NN+i, t%2);
    c = t/2;
  }
  apply(NN+n, c);
  FOR(i, n+1, NN)
    apply(NN+i, c);
  ROF(i, 1, NN) {
    same[i] = -1;
    mconcat(i);
  }
  while (q--) {
    char op[9];
    int x, y;
    scanf("%s%d", op, &x);
    if (*op == 'g')
      printf("%d", x <= n ? ! ~ getFirst(x, x+1, 0) : 0);
    else {
      int w = op[4]-'a';
      y = ri();
      if (a[w][n-1-x] != '0'+y) {
        a[w][n-1-x] = '0'+y;
        int z = getFirst(x, n+1, y^1);
        setSame(x, z, y^1);
        setSame(z, z+1, y);
      }
    }
  }
}
