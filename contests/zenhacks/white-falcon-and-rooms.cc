#include <algorithm>
#include <cstdio>
#include <set>
using namespace std;

#define REP1(i, n) for (int i = 1; i <= (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 200000, LOGN = 18, Q = 200000;
extern struct Node *allo;
struct Node
{
  int close, open;
  Node *c[2];
  Node() {}
  Node(int l, int r) {
    close = open = 0;
    if (l < r-1) {
      int m = l+r >> 1;
      c[0] = new Node(l, m);
      c[1] = new Node(m, r);
    }
  }
  void *operator new(size_t) { return allo++; }
  void *operator new(size_t, Node *x) { return x; }
  void mconcat() {
    int t = min(c[0]->open, c[1]->close);
    close = c[0]->close + c[1]->close - t;
    open = c[0]->open + c[1]->open - t;
  }
  Node *add(int l, int r, int i, bool typ) {
    if (i < l || r <= i)
      return this;
    Node *ret = allo++;
    if (l == r-1) {
      ret->open = open+typ;
      ret->close = close+!typ;
      int t = min(ret->open, ret->close);
      ret->open -= t;
      ret->close -= t;
    } else {
      int m = l+r >> 1;
      ret->c[0] = c[0]->add(l, m, i, typ);
      ret->c[1] = c[1]->add(m, r, i, typ);
      ret->mconcat();
    }
    return ret;
  }
} pool[2*N+(LOGN+1)*Q], *allo = pool, empty;

extern struct Segment *allo2;
struct Segment
{
  Node *v;
  Segment *c[2];
  Segment() {}
  Segment(int l, int r) {
    if (l < r-1) {
      int m = l+r >> 1;
      c[0] = new Segment(l, m);
      c[1] = new Segment(m, r);
    } else
      v = &empty;
  }
  void *operator new(size_t) { return allo2++; }
  Segment *set(int l, int r, int i, Node *v) {
    if (i < l || r <= i) return this;
    Segment *ret = allo2++;
    if (l == r-1)
      ret->v = v;
    else {
      int m = l+r >> 1;
      ret->c[0] = c[0]->set(l, m, i, v);
      ret->c[1] = c[1]->set(m, r, i, v);
    }
    return ret;
  }
  Node *get(int l, int r, int i) {
    Segment *x = this;
    while (l < r-1) {
      int m = l+r >> 1;
      if (i < m)
        r = m, x = x->c[0];
      else
        l = m, x = x->c[1];
    }
    return x->v;
  }
} pool2[2*N+(LOGN+1)*Q], *allo2 = pool2, *seg[Q+1];

int main()
{
  int n = ri(), q = ri();
  new(&empty) Node(0, n);
  seg[0] = new Segment(0, n);
  REP1(i, q) {
    char op;
    scanf(" %c", &op);
    int x = ri();
    if (op == 'B') {
      x--;
      int y = ri()-1;
      Node *v = seg[i-1]->get(0, n, y)->add(0, n, x, false);
      seg[i] = seg[i-1]->set(0, n, y, v);
      puts(v->open ? "NO" : "YES");
    } else if (op == 'I') {
      x--;
      int y = ri()-1;
      Node *v = seg[i-1]->get(0, n, y)->add(0, n, x, true);
      seg[i] = seg[i-1]->set(0, n, y, v);
      puts(v->open ? "NO" : "YES");
    } else
      seg[i] = x == i ? seg[i-1] : seg[x];
  }
}
