#include <algorithm>
#include <climits>
#include <cstdio>
#include <utility>
#include <vector>
using namespace std;

typedef pair<int, int> pii;
#define ALL(x) (x).begin(), (x).end()
#define REP(i, n) for (int i = 0; i < (n); i++)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )
#define fi first
#define mp make_pair
#define pb push_back
#define se second

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 1000, M = 100000;
vector<pii> fenwick[M];
struct E
{
  int x, y, w;
  bool operator<(int o) const {
    return w < o;
  }
  bool operator<(const E &o) const {
    return w < o.w;
  }
} es[M];

bool operator<(int w, const E &o)
{
  return w < o.w;
}

void add(int m, int x, int t, int dlt)
{
  for (; x < m; x |= x+1)
    fenwick[x].emplace_back(t, fenwick[x].back().se + dlt);
}

int getSum(int x, int t)
{
  int sum = 0;
  for (; x; x &= x-1)
    sum += lower_bound(ALL(fenwick[x-1]), mp(t, INT_MIN))->se;
  return sum;
}

namespace LCT
{
  extern struct Node null;
  struct Edge;
  struct Node {
    int flip, w;
    Node *c[2], *p, *opt;
    void init() {
      c[0] = c[1] = p = &null;
      flip = w = 0;
      opt = this;
    }
    void setc(int d, Node *x) {
      c[d] = x;
      x->p = this;
      opt = this;
      REP(d, 2)
        if (c[d]->opt->w > opt->w)
          opt = c[d]->opt;
    }
    void untag() {
      if (! flip) return;
      flip = 0;
      c[0]->flip ^= 1;
      c[1]->flip ^= 1;
      swap(c[0], c[1]);
    }
    int zag(Node *&par) {
      par = p;
      p->untag();
      untag();
      REP(d, 2)
        if (p->c[d] == this) {
          Node *g = p->p;
          p->setc(d, c[d^1]);
          setc(d^1, p);
          REP(dd, 2)
            if (g->c[dd] == p)
              g->c[dd] = this;
          p = g;
          return d;
        }
      return -1;
    }
    void splay() {
      int dd = -1;
      Node *x, *y;
      for(;;) {
        int d = zag(x);
        if (d < 0) break;
        if (d == dd)
          y->zag(y), dd = -1;
        else
          dd = d;
        y = x;
      }
    }
    void access() {
      Node *x = this, *y = &null;
      for (; x != &null; y = x, x = x->p) {
        x->splay();
        x->setc(1, y);
      }
      splay();
    }
    void evert() {
      access();
      flip = 1;
    }
    bool sameRoot(Node *o) {
      access();
      o->access();
      return p != &null;
    }
    void link(Node *o) {
      o->evert();
      o->p = this;
    }
    void cut(Node *o) {
      evert();
      o->access();
      p = &null;
      o->setc(0, &null);
    }
    Edge *query(Node *o) {
      evert();
      o->access();
      return (Edge *)o->opt;
    }
  } null, node[N];
  struct Edge : Node { Node *x, *y; } edge[M];
};

int main()
{
  LCT::null.init();
  for (int cases = ri(); cases--; ) {
    int n = ri(), m = ri();
    REP(i, n)
      LCT::node[i].init();
    REP(i, m) {
      es[i].x = ri()-1;
      es[i].y = ri()-1;
      es[i].w = ri();
      fenwick[i].assign(1, mp(m, 0));
    }
    sort(es, es+m);
    ROF(i, 0, m) {
      int x = es[i].x, y = es[i].y;
      LCT::Edge *e = &LCT::edge[i];
      e->init();
      e->w = es[i].w;
      e->x = &LCT::node[x];
      e->y = &LCT::node[y];
      if (e->x->sameRoot(e->y)) {
        LCT::Edge *f = e->x->query(e->y);
        f->cut(f->x);
        f->cut(f->y);
        add(m, f-LCT::edge, i, - f->w);
      }
      e->link(e->x);
      e->link(e->y);
      add(m, i, i, es[i].w);
    }
    REP(i, m)
      reverse(ALL(fenwick[i]));
    for (int t = 0, q = ri(); q--; ) {
      int l = ri()-t, h = ri()-t;
      l = lower_bound(es, es+m, l) - es;
      h = upper_bound(es, es+m, h) - es;
      t = getSum(h, l);
      printf("%d\n", t);
    }
  }
}
