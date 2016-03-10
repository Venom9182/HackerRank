#include <cstdio>
#include <vector>
using namespace std;

typedef long long ll;
#define REP(i, n) for (int i = 0; i < (n); i++)
#define pb push_back

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 50000, MOD = 1000000007;
vector<int> e[N];

void merge(int a, int b, int aa, int bb, int &sa, int &sb)
{
  sa = ll(a)*aa%MOD;
  sb = (ll(aa)*b+bb)%MOD;
}

namespace LCT
{
  extern struct Node null;
  struct Node {
    bool same;
    int size, a, b, a0, b0, a1, b1;
    Node *c[2], *p;
    void init() {
      c[0] = c[1] = p = &null;
      same = false;
      size = 1;
      a = a0 = a1 = 1;
      b = b0 = b1 = 0;
    }
    void setc(int d, Node *x) {
      c[d] = x;
      x->p = this;
      size = c[0]->size + 1 + c[1]->size;
      merge(c[0]->a0, c[0]->b0, a, b, a0, b0);
      merge(a0, b0, c[1]->a0, c[1]->b0, a0, b0);
      merge(c[1]->a1, c[1]->b1, a, b, a1, b1);
      merge(a1, b1, c[0]->a1, c[0]->b1, a1, b1);
    }
    void untag() {
      if (! same) return;
      same = false;
      REP(d, 2)
        if (c[d] != &null)
          c[d]->assign(a, b);
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
    void assign(int aa, int bb) {
      a = aa;
      b = bb;
      a0 = 1;
      b0 = 0;
      for (int s = size; s; s /= 2) {
        if (s & 1) {
          b0 = (ll(aa)*b0+bb)%MOD;
          a0 = ll(aa)*a0%MOD;
        }
        bb = (ll(aa)*bb+bb)%MOD;
        aa = ll(aa)*aa%MOD;
      }
      a1 = a0;
      b1 = b0;
      same = true;
    }
    void assign(Node *x, int aa, int bb) {
      access();
      Node *y = &null;
      for (; ; y = x, x = x->p) {
        x->splay();
        if (x->p == &null) break;
        x->setc(1, y);
      }
      if (x->c[1] != &null)
        x->c[1]->assign(aa, bb);
      x->a = aa;
      x->b = bb;
      if (y != &null)
        y->assign(aa, bb);
      x->setc(1, y);
    }
    int query(Node *x, int var) {
      access();
      Node *y = &null;
      for (; ; y = x, x = x->p) {
        x->splay();
        if (x->p == &null) break;
        x->setc(1, y);
      }
      ll ret = (ll(x->c[1]->a1) * var + x->c[1]->b1) % MOD;
      ret = (ret * x->a + x->b) % MOD;
      return (ret * y->a0 + y->b0) % MOD;
    }
  } null, node[N];
};

void dfs(int v, int p)
{
  for (int u: e[v])
    if (u != p) {
      LCT::node[u].p = &LCT::node[v];
      dfs(u, v);
    }
}

int main()
{
  LCT::null.init();
  LCT::null.size = 0;
  int n = ri();
  REP(i, n) {
    LCT::node[i].init();
    LCT::node[i].a = ri();
    LCT::node[i].b = ri();
  }
  REP(i, n-1) {
    int v = ri()-1, u = ri()-1;
    e[v].pb(u);
    e[u].pb(v);
  }
  dfs(0, -1);
  for (int q = ri(); q--; ) {
    int op = ri(), v = ri()-1, u = ri()-1;
    if (op == 1) {
      int a = ri(), b = ri();
      LCT::node[v].assign(&LCT::node[u], a, b);
    } else {
      int x = ri();
      printf("%d\n", LCT::node[v].query(&LCT::node[u], x));
    }
  }
}
