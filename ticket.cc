#include <algorithm>
#include <climits>
#include <iostream>
#include <map>
#include <string>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); i++)
#define SIZE(x) (sizeof(x)/sizeof(*x))

const int N = 500, V = N*2+2;
const double EPS = 1e-8;
string dest[N];
bool in[V];
int q[V], window[N];
double dist[V];
struct Edge { int v, c; double w; Edge *next, *twain; } *es[V], *pred[V], pool[N*(N-1)+3*N << 1], *allo = pool;

void add(int u, int v, int c, double w)
{
  allo[0] = {v, c, w, es[u], allo+1};
  allo[1] = {u, 0, - w, es[v], allo};
  es[u] = allo++;
  es[v] = allo++;
}

bool labelCorrecting(int n, int src, int sink)
{
  fill_n(in, n, false);
  fill_n(pred, n, nullptr);
  fill_n(dist, n, numeric_limits<double>::max());
  dist[src] = 0;
  int *fr = q, *re = q;
  *re++ = src;
  while (fr != re) {
    int u = *fr++;
    if (fr == q+SIZE(q))
      fr = q;
    in[u] = false;
    for (Edge *e = es[u]; e; e = e->next)
      if (e->c > 0) {
        double t = dist[u]+e->w;
        if (t+EPS < dist[e->v]) {
          dist[e->v] = t;
          pred[e->v] = e;
          if (! in[e->v]) {
            in[e->v] = true;
            *re++ = e->v;
            if (re == q+SIZE(q))
              re = q;
          }
        }
      }
  }
  return dist[sink] < numeric_limits<double>::max();
}

double minCostMaxFlow(int n, int src, int sink, int m)
{
  int flow = 0;
  double cost = 0;
  while (flow < m && labelCorrecting(n, src, sink) && dist[sink] < 0) {
    int f = m-flow;
    for (int v = sink; v != src; v = pred[v]->twain->v)
      f = min(f, pred[v]->c);
    flow += f;
    cost += f*dist[sink];
    for (int v = sink; v != src; v = pred[v]->twain->v) {
      pred[v]->c -= f;
      pred[v]->twain->c += f;
    }
  }
  return cost;
}

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n, m, k;
  cin >> n >> m >> k;
  map<string, int> price;
  REP(i, k) {
    int p;
    cin >> dest[0] >> p;
    price[dest[0]] = p;
  }
  int src = 2*n, sink = src+1;
  REP(i, n) {
    cin >> dest[i];
    double t = price[dest[i]];
    add(src, i, 1, t);
    add(i, n+i, 1, -100*n);
    add(n+i, sink, 1, 0);
    REP(j, i)
      add(n+j, i, 1, dest[j] == dest[i] ? 0.8*t : t);
  }
  cout << minCostMaxFlow(sink+1, src, sink, m)+100*n*n << '\n';
  int id = 0;
  for (Edge *e = es[src]; e; e = e->next)
    if (e->c == 0)
      window[e->v] = ++id;
  REP(i, n)
    for (Edge *e = es[n+i]; e; e = e->next)
      if (e->v < n && i < e->v && e->c == 0)
        window[e->v] = window[i];
  REP(i, n)
    cout << window[i] << '\n';
}
