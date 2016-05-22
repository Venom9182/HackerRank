#include <algorithm>
#include <iostream>
#include <type_traits>
#include <vector>
using namespace std;

#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

const long N = 200000;
long dep[N];
vector<long> es[N];

unsigned marsaglia_xor32()
{
  static unsigned x = 1;
  x ^= x << 13;
  x ^= x >> 17;
  return x ^= x << 5;
}

struct Node
{
  long size = 1, pri = marsaglia_xor32();
  Node *l = 0, *r = 0, *p = 0;
  Node* mconcat() {
    int size(Node *x);
    this->size = size(l) + 1 + size(r);
    if (l) l->p = this;
    if (r) r->p = this;
    return this;
  }
} *pre[N], *post[N], *tr = 0;

long size(Node* x)
{
  return x ? x->size : 0;
}

Node* root(Node* x)
{
  while (x->p)
    x = x->p;
  return x;
}

long order_of(Node* x)
{
  bool f = true;
  long r = size(x->l);
  while (x->p) {
    if (x->p->r == x)
      r += size(x->p->l) + 1;
    x = x->p;
  }
  return r;
}

Node* join(Node* x, Node* y)
{
  if (! x) return y;
  if (! y) return x;
  if (x->pri < y->pri) {
    x->r = join(x->r, y);
    return x->mconcat();
  } else {
    y->l = join(x, y->l);
    return y->mconcat();
  }
}

void split(Node* x, long k, Node*& l, Node*& r)
{
  if (! x)
    l = r = 0;
  else {
    long c = size(x->l) + 1;
    if (k < c) {
      split(x->l, k, l, x->l);
      r = x;
    } else {
      split(x->r, k-c, x->r, r);
      l = x;
    }
    x->mconcat();
    x->p = 0;
  }
}

void dfs(long u, long p)
{
  pre[u] = new Node;
  tr = join(tr, pre[u]);
  for (long v: es[u])
    if (v != p) {
      dep[v] = dep[u]+1;
      dfs(v, u);
    }
  post[u] = new Node;
  tr = join(tr, post[u]);
}

void cut(long u, long v)
{
  if (dep[v] < dep[u])
    swap(v, u);
  long il = order_of(pre[v]), ir = order_of(post[v])+1;
  Node *x, *y = root(pre[v]), *z;
  split(y, ir, y, z);
  split(y, il, x, y);
  join(x, z);
}

int main()
{
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  long n, m, u, v, ans = 0;
  cin >> n;
  REP(i, n-1) {
    cin >> u >> v;
    u--; v--;
    es[u].push_back(v);
    es[v].push_back(u);
  }
  dfs(0, -1);
  for (cin >> m; m--; ) {
    cin >> u;
    u = (ans ^ u) - 1;
    ans = size(root(pre[u])) / 2;
    cout << ans << '\n';
    for (long v: es[u])
      cut(u, v);
  }
}
