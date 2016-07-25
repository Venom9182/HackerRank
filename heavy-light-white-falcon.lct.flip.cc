#include <algorithm>
#include <climits>
#include <iostream>
#include <type_traits>
#include <vector>
using namespace std;

#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

const long N = 50000;
vector<long> adj[N];

namespace LCT {
extern struct Node null;
struct Node {
  char flip;
  long w, opt;
  Node *c[2], *p;
  void init() {
    flip = w = opt = 0;
    c[0] = c[1] = p = &null;
  }
  void mconcat() {
    opt = max(max(c[0]->opt, w), c[1]->opt);
  }
  void untag() {
    if (! flip) return;
    flip = 0;
    c[0]->flip ^= 1;
    c[1]->flip ^= 1;
    swap(c[0], c[1]);
  }
  void setc(long d, Node* x) {
    c[d] = x;
    x->p = this;
  }
  void zag(long d) {
    Node *x = c[d], *p = this->p;
    setc(d, x->c[d^1]);
    mconcat();
    x->setc(d^1, this);
    x->p = p;
    if (p->c[0] == this)
      p->c[0] = x;
    else if (p->c[1] == this)
      p->c[1] = x;
  }
  void splay() {
    while (p->c[0] == this || p->c[1] == this) {
      Node *p = this->p, *g = p->p;
      if (g->c[0] == p || g->c[1] == p) {
        g->untag(); p->untag(); untag();
        if (g->c[0] == p) {
          if (p->c[0] == this) g->zag(0), p->zag(0);
          else p->zag(1), g->zag(0);
        } else {
          if (p->c[0] != this) g->zag(1), p->zag(1);
          else p->zag(0), g->zag(1);
        }
      } else {
        p->untag(); untag();
        p->zag(p->c[0] != this);
      }
    }
    untag();
    mconcat();
  }
  void expose() {
    Node *x = this, *y = &null;
    for (; x != &null; y = x, x = x->p) {
      x->splay();
      x->c[1] = y; // mconcat in last splay
    }
    splay();
  }
  void evert() {
    expose();
    flip = 1;
  }
  void link(Node* par) {
    evert();
    p = par;
  }
  void cut(Node* par) {
    par->evert();
    expose();
    par->p = &null;
    setc(0, &null);
    mconcat();
  }
  long query(Node* x) {
    evert();
    x->expose();
    return x->opt;
  }
} null, nodes[N];
};

int main()
{
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  long n, q, op, u, v;
  cin >> n >> q;
  LCT::Node* null = &LCT::null;
  null->init();
  null->opt = LONG_MIN;
  REP(i, n)
    LCT::nodes[i].init();
  REP(i, n-1) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
    LCT::nodes[v].link(&LCT::nodes[u]);
  }
  while (q--) {
    cin >> op >> u >> v;
    if (op == 1) {
      LCT::nodes[u].expose();
      LCT::nodes[u].w = v;
      LCT::nodes[u].mconcat();
    } else
      cout << LCT::nodes[u].query(&LCT::nodes[v]) << '\n';
  }
}
