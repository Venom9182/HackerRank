#include <algorithm>
#include <cstdio>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100000;

extern struct Node null, *root;
struct Node
{
  bool flip;
  int key, size;
  Node *c[2], *p;
  void init() {
    c[0] = c[1] = p = &null;
    flip = false;
    size = 1;
  }
  void untag() {
    if (flip) {
      flip = false;
      swap(c[0], c[1]);
      c[0]->flip ^= 1;
      c[1]->flip ^= 1;
    }
  }
  void setc(int d, Node *x) {
    c[d] = x;
    x->p = this;
    size = c[0]->size + 1 + c[1]->size;
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
  void splay(Node *top) {
    Node *x, *y;
    int dd = -1;
    while (p != top) {
      int d = zag(x);
      if (d == dd)
        y->zag(y), dd = -1;
      else
        dd = d;
      y = x;
    }
    if (top == &null)
      root = this;
  }
} *root, node[N+2], null;

Node *select(int k)
{
  Node *x = root;
  for(;;) {
    x->untag();
    if (k < x->c[0]->size)
      x = x->c[0];
    else if (k > x->c[0]->size)
      k -= x->c[0]->size + 1, x = x->c[1];
    else
      break;
  }
  return x;
}

int main()
{
  int n = ri(), q = ri();
  null.init();
  null.size = 0;
  REP(i, n+2) {
    node[i].init();
    node[i].key = i;
    if (i)
      node[i].setc(0, &node[i-1]);
  }
  root = &node[n+1];
  while (q--) {
    int op = ri(), x = ri();
    if (op == 1) {
      int y = ri();
      Node *p = select(x-1), *q = select(y+1);
      p->splay(&null);
      q->splay(p);
      q->c[0]->flip ^= 1;
    } else if (op == 2) {
      node[x].splay(&null);
      printf("element %d is at position %d\n", x, node[x].c[0]->size);
    } else {
      Node *p = select(x);
      p->splay(&null);
      printf("element at position %d is %d\n", x, p->key);
    }
  }
}
