#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100000, V = (N+2)*2;
struct Vec {
  double x, y;
  Vec(double x = 0, double y = 0) : x(x), y(y) {}
  Vec operator +(Vec q) { return Vec(x + q.x, y + q.y); }
  Vec operator -(Vec q) { return Vec(x - q.x, y - q.y); }
  Vec operator *(double t) { return Vec(x * t, y * t); }
  Vec operator /(double t) { return Vec(x / t, y / t); }
  double operator *(Vec q) { return x * q.x + y * q.y; }
  double operator %(Vec q) { return x * q.y - y * q.x; }
} a[N];
double abs(const Vec &p) { return hypot(p.x, p.y); }

struct Circle {
  double x, y, r;
  Circle(Vec a, double r) : x(a.x), y(a.y), r(r) {}
};

bool inCircle(const Circle &c, const Vec &a)
{
  return hypot(a.x-c.x, a.y-c.y) <= c.r;
}

Vec circumcenter(Vec p, Vec q, Vec r)
{
  Vec a = p - r, b = q - r, c = Vec(a * (p + r) / 2, b * (q + r) / 2);
  return Vec(c % Vec(a.y, b.y), Vec(a.x, b.x) % c) / (a % b);
}

Circle smallestEnclosingCircle(int n)
{
  random_shuffle(a, a+n);
  Circle C(Vec{0, 0}, -1);
  REP(i, n)
    if (! inCircle(C, a[i])) {
      C = Circle(a[i], 0);
      REP(j, i)
        if (! inCircle(C, a[j])) {
          C = Circle((a[i]+a[j])/2, abs(a[i]-a[j])/2);
          REP(k, j)
            if (! inCircle(C, a[k])) {
              Vec o = circumcenter(a[i], a[j], a[k]);
              C = Circle(o, abs(o-a[k]));
            }
        }
    }
  return C;
}

int y[N], ny;
extern struct Node null;
struct Node {
  bool flp;
  Node *l, *r;
  int key, size;
  void init(int k, int s) {
    flp = false;
    key = k;
    size = s;
    l = r = &null;
  }
  int cmp(int k) { return l->size == k ? -1 : l->size < k; }
  void mconcat() { size = l->size + 1 + r->size; }
  void untag() {
    if (flp) {
      flp = false;
      l->flip();
      r->flip();
    }
  }
  void flip() {
    if (this == &null) return;
    swap(l, r);
    flp = ! flp;
  }
} pool[V], null, *allo = pool;

void splay(Node *&x, int k)
{
  Node *lspine = &null, *rspine = &null;
  for(;;) {
    x->untag();
    if (x->l->size == k) break;

#define F(d,l,r)                      \
    do {                              \
      Node *y = x->l;                 \
      y->untag();                     \
      if (x->l->cmp(k) == d) {        \
        if (d) k -= x->l->r->size+1;  \
        x->l = y->r;                  \
        y->r = x;                     \
        x->mconcat();                 \
        x = y->l;                     \
        y->l = r##spine;              \
        r##spine = y;                 \
      } else {                        \
        x->l = r##spine;              \
        r##spine = x;                 \
        x = y;                        \
      }                               \
    } while (0)

    if (x->l->size < k) { k -= x->l->size+1; F(1,r,l); } else F(0,l,r);
#undef F
  }

#define G(l,r)                            \
  do {                                    \
    Node *z = x->l;                       \
    while (l##spine != &null) {            \
      Node *y = l##spine->r;              \
      l##spine->r = z;                    \
      l##spine->mconcat();                \
      z = l##spine;                       \
      l##spine = y;                       \
    }                                     \
    x->l = z;                             \
  } while (0)

  G(l,r);
  G(r,l);
#undef G
  x->mconcat();
}

Node *&range(Node *&rt, int L, int R)
{
  splay(rt, L-1);
  splay(rt->r, R-L);
  return rt->r->l;
}

void inorder(Node *rt, int d)
{
  if (rt != &null) {
    rt->untag();
    inorder(rt->l, d+1);
    y[ny++] = rt->key;
    inorder(rt->r, d+1);
  }
}

int main()
{
#define UPDATE(rt) { rt->r->mconcat(); rt->mconcat(); }
  int n = ri(), m = ri();
  Node *rt[2] = {allo++, allo++};
  null.init(0, 0);
  REP(d, 2) {
    rt[d]->init(-1, 1);
    REP(i, n+1) {
      allo->init(i == n ? -1 : ri(), i+2);
      allo->l = rt[d];
      rt[d] = allo++;
    }
  }
  while (m--) {
    Node *p, *q;
    int id, l0, r0, l1, r1;
    switch (ri()) {
    case 1:
      id = ri();
      l0 = ri();
      r0 = ri();
      range(rt[id], l0, r0+1)->flip();
      break;
    case 2:
      id = ri();
      l0 = ri();
      r0 = ri();
      l1 = ri();
      r1 = ri();
      if (r0+1 == l1) {
        range(rt[id], l0, r0+1)->flip();
        range(rt[id], l1, r1+1)->flip();
        range(rt[id], l0, r1+1)->flip();
      } else {
        q = range(rt[id], l1, r1+1);
        rt[id]->r->l = &null;
        UPDATE(rt[id]);
        p = range(rt[id], l0, r0+1);
        rt[id]->r->l = q;
        UPDATE(rt[id]);
        int s = l1+(r1-r0)-(l1-l0);
        range(rt[id], s, s) = p;
        UPDATE(rt[id]);
      }
      break;
    case 3:
      l0 = ri();
      r0 = ri();
      {
        p = range(rt[0], l0, r0+1);
        q = range(rt[1], l0, r0+1);
        rt[0]->r->l = q;
        UPDATE(rt[0]);
        rt[1]->r->l = p;
        UPDATE(rt[1]);
      }
      break;
    case 4:
      l0 = ri();
      r0 = ri();
      ny = 0;
      inorder(range(rt[0], l0, r0+1), 0);
      id = ny;
      REP(i, id)
        a[i].x = y[i];
      ny = 0;
      inorder(range(rt[1], l0, r0+1), 0);
      REP(i, id)
        a[i].y = y[i];
      printf("%.2lf\n", smallestEnclosingCircle(id).r);
      break;
    }
  }
}
