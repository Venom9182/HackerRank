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

const int N = 10000, Q = 10000, K = 1001, LOGK = 10;

int a[N];
extern struct Node null, *allo;
struct Node
{
  int size, key;
  Node *ch[2], *p;
  Node() {}
  Node(int key) : key(key), size(1) { ch[0] = ch[1] = &null; }
  void *operator new(size_t) { return allo++; }
} pool[(N+Q)*(LOGK+1)], null, *allo, *fenwick[K];

void zag(Node *&x, int d)
{
  Node *y = x->ch[d];
  x->ch[d] = y->ch[!d];
  y->ch[!d] = x;
  y->size = x->size;
  x->size = x->ch[0]->size + x->ch[1]->size + 1;
  x = y;
}

void maintain(Node *&x, int d)
{
  if (x == &null) return;
  if (x->ch[d]->ch[d]->size > x->ch[!d]->size)
    zag(x, d);
  else if (x->ch[d]->ch[!d]->size > x->ch[!d]->size)
    zag(x->ch[d], !d), zag(x, d);
  else return;
  maintain(x->ch[0], 0);
  maintain(x->ch[1], 1);
  maintain(x, 0);
  maintain(x, 1);
}

void insert(Node *&x, int key)
{
  if (x == &null) {
    x = new Node(key);
    return;
  }
  int d = x->key < key;
  ++x->size;
  insert(x->ch[d], key);
  maintain(x, d);
}

Node *remove(Node *&x, int key)
{
  if (x == &null) return &null;
  x->size --;
  if (key == x->key || key < x->key && x->ch[0] == &null || key > x->key && x->ch[1] == &null) {
    if (x->ch[0] == &null || x->ch[1] == &null) {
      Node *p = x;
      x = x->ch[x->ch[0] == &null];
      return p;
    }
    Node *p = remove(x->ch[1], key-1);
    x->key = p->key;
    return &null;
  }
  return remove(x->ch[x->key < key], key);
}

int cntLT(Node *x, int k)
{
  int c = 0;
  while (x != &null) {
    if (x->key < k) {
      c += x->ch[0]->size + 1;
      x = x->ch[1];
    } else
      x = x->ch[0];
  }
  return c;
}

void insert(int x, int i)
{
  for (; x < K; x |= x+1)
    insert(fenwick[x], i);
}

void remove(int x, int i)
{
  for (; x < K; x |= x+1)
    remove(fenwick[x], i);
}

int main()
{
  null.size = 0;
  null.ch[0] = null.ch[1] = &null;
  for (int cc = ri(); cc--; ) {
    int n = ri();
    allo = pool;
    fill_n(fenwick, K, &null);
    REP(i, n) {
      a[i] = ri();
      insert(a[i], i);
    }
    for (int q = ri(); q--; ) {
      int op = ri(), x = ri()-1, y = ri();
      if (op) {
        remove(a[x], x);
        insert(a[x] = y, x);
      } else {
        int k = ri(), z = -1;
        for (int p = 1 << LOGK-1; p; p >>= 1)
          if (z+p < K) {
            int c = cntLT(fenwick[z+p], y) - cntLT(fenwick[z+p], x);
            if (c < k)
              z += p, k -= c;
          }
        printf("%d\n", z+1);
      }
    }
  }
}
