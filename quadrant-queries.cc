#include <algorithm>
#include <cstdio>
#include <utility>
using namespace std;

typedef pair<int, int> pii;
#define REP(i, n) for (int i = 0; i < (n); i++)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )
#define fi first
#define se second

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100000, NN = 131072;
int seg[2*NN][4], tag[2*NN];

void mconcat(int i)
{
  REP(j, 4)
    seg[i][j] = seg[2*i][j]+seg[2*i+1][j];
}

void apply(int i, int v)
{
  int t[4];
  REP(j, 4)
    t[j^v] = seg[i][j];
  copy_n(t, 4, seg[i]);
  tag[i] ^= v;
}

void untag(int i)
{
  if (i < 0 || i >= NN) return;
  i += NN;
  for (int j, h = 31-__builtin_clz(NN); h; h--)
    if (tag[j = i>>h]) {
      apply(2*j, tag[j]);
      apply(2*j+1, tag[j]);
      tag[j] = 0;
    }
}

void change(int l, int r, int v)
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

pair<pii, pii> query(int l, int r)
{
  int t[4] = {};
  untag(l-1);
  untag(r);
  for (l += NN, r += NN; l < r; l >>= 1, r >>= 1) {
    if (l & 1) {
      REP(j, 4)
        t[j] += seg[l][j];
      l++;
    }
    if (r & 1) {
      r--;
      REP(j, 4)
        t[j] += seg[r][j];
    }
  }
  return {{t[0], t[1]}, {t[3], t[2]}};
}

int main()
{
  int n = ri();
  REP(i, n) {
    int x = ri(), y = ri();
    seg[NN+i][2*(y<0)+(x<0)] = 1;
  }
  ROF(i, 1, NN)
    mconcat(i);
  for (int m = ri(); m--; ) {
    char op;
    scanf(" %c", &op);
    int l = ri()-1, r = ri();
    if (op == 'X')
      change(l, r, 2);
    else if (op == 'Y')
      change(l, r, 1);
    else {
      auto t = query(l, r);
      printf("%d %d %d %d\n", t.fi.fi, t.fi.se, t.se.fi, t.se.se);
    }
  }
}
