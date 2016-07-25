#include <algorithm>
#include <climits>
#include <iostream>
#include <numeric>
#include <set>
#include <stack>
#include <type_traits>
#include <utility>
#include <vector>
using namespace std;

typedef pair<long, long> pll;
#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

const long N = 500000, M = 1000, V = N+2, INF = LONG_MAX/3;
bool in[V];
long size[N], dep[N], par[N], d[V], h[V], heap[V], lkp[V], vs[V], src, sink, nvs;
set<pll> adj[N];
struct Edge { long v, c, w; Edge *next, *dual; } *e[V], *pre[V], pool[N*2+M << 1], *allo;

void insert(long u, long v, long c, long w)
{
  allo->v = v; allo->c = c; allo->w = w; allo->next = e[u]; e[u] = allo++;
  allo->v = u; allo->c = 0; allo->w = - w; allo->next = e[v]; e[v] = allo++;
  e[u]->dual = e[v];
  e[v]->dual = e[u];
}

bool label()
{
  fill_n(h, sink+1, INF);
  fill_n(in, sink+1, false);
  h[src] = 0;
  long fore = 0, rear = 1;
  heap[0] = src;
  in[src] = true;
  while (fore != rear) {
    long u = heap[fore++];
    if (fore == sizeof(heap)/sizeof(*heap)) fore = 0;
    in[u] = false;
    for (Edge* it = e[u]; it; it = it->next)
      if (it->c > 0 && h[u]+it->w < h[it->v]) {
        h[it->v] = h[u]+it->w;
        pre[it->v] = it;
        if (! in[it->v]) {
          heap[rear++] = it->v;
          if (rear == sizeof(heap)/sizeof(*heap)) rear = 0;
          in[it->v] = true;
        }
      }
  }
  return h[sink] < INF;
}

void heap_up(long n, long x)
{
  long key = heap[x];
  for (; x && d[key] < d[heap[(x-1)/2]]; x = (x-1)/2)
    lkp[heap[x] = heap[(x-1)/2]] = x;
  lkp[heap[x] = key] = x;
}

void heap_down(long n, long x)
{
  long key = heap[x];
  for (long y; y = 2*x+1, y < n; x = y) {
    if (y+1 < n && d[heap[y+1]] < d[heap[y]]) y++;
    if (!(d[heap[y]] < d[key])) break;
    lkp[heap[x] = heap[y]] = x;
  }
  lkp[heap[x] = key] = x;
}

bool dijkstra()
{
  long size = nvs;
  REP(i, nvs) {
    lkp[heap[i] = vs[i]] = i;
    d[vs[i]] = INF;
  }
  d[src] = 0;
  heap_up(size, lkp[src]);
  while (size > 1) {
    long u = heap[0], t;
    lkp[u] = -1;
    heap[0] = heap[--size];
    heap_down(size, 0);
    if (d[u] >= INF) break;
    //if (d[u] >= INF || u == sink) break;
    for (Edge* it = e[u]; it; it = it->next)
      if (it->c > 0 && (t = d[u]+it->w+h[u]-h[it->v]) < d[it->v]) {
        d[it->v] = t;
        heap_up(size, lkp[it->v]);
        pre[it->v] = it;
      }
  }
  long m = 0;
  REP(i, nvs) {
    h[vs[i]] = min(h[vs[i]]+d[vs[i]], INF);
    if (h[vs[i]] < INF)
      vs[m++] = vs[i];
  }
  nvs = m;
  return h[sink] < INF;
}

long ssap()
{
  static long g  = 0;
  long ret = 0;
  if (! label()) return 0;
  iota(vs, vs+sink+1, 0);
  nvs = sink+1;
  do {
    long d = INF;
    for (long v = sink; v != src; v = pre[v]->dual->v)
      d = min(d, pre[v]->c);
    for (long v = sink; v != src; v = pre[v]->dual->v) {
      pre[v]->c -= d;
      pre[v]->dual->c += d;
    }
    ret += d*h[sink];
  } while (g++, dijkstra());
  return ret;
}

long get_size(long u, long p, long d)
{
  dep[u] = d;
  par[u] = p;
  long s = 1;
  for (auto e: adj[u])
    if (e.first != p)
      s += get_size(e.first, u, d+1);
  return size[u] = s;
}

bool prune(long u, long p)
{
  static stack<long> st;
  if (in[u])
    st.push(u);
  bool good = false;
  auto tadj = adj[u];
  for (auto e: tadj)
    if (e.first != p)
      good |= prune(e.first, u);
  if (in[u]) {
    st.pop();
    if (st.size()) {
      long v = st.top();
      if (size[v]-size[u] == dep[u]-dep[v]) {
        long mind = LONG_MAX;
        auto it = adj[u].lower_bound(make_pair(p, LONG_MIN));
        adj[u].erase(it);
        for (long x = u; x != v; x = par[x]) {
          it = adj[par[x]].lower_bound(make_pair(x, LONG_MIN));
          mind = min(mind, it->second);
          adj[par[x]].erase(it);
        }
        adj[v].emplace(u, mind);
      }
    }
  }
  good |= in[u];
  if (! good)
    adj[u].clear();
  return good;
}

void dfs(long u, long p, long dd)
{
  vs[nvs++] = u;
  for (auto e: adj[u])
    if (e.first != p) {
      dfs(e.first, u, e.second);
      dd -= e.second;
      insert(e.first, u, INF, 0);
    }
  if (dd > 0)
    insert(src, u, dd, 0);
  else if (dd < 0)
    insert(u, sink, - dd, 0);
}

int main()
{
  ios_base::sync_with_stdio(0);
  long cases, n, m, u, v, w;
  for (cin >> cases; cases--; ) {
    allo = pool;
    cin >> n >> m;
    fill_n(in, n, false);
    REP(i, n) {
      adj[i].clear();
      e[i] = 0;
    }
    REP(i, n-1) {
      cin >> u >> v >> w;
      u--, v--;
      adj[u].emplace(v, w);
      adj[v].emplace(u, w);
    }
    REP(i, m) {
      cin >> u >> v >> w;
      u--, v--;
      insert(v, u, 1, - w);
      in[u] = in[v] = true;
    }
    src = n;
    sink = n+1;
    get_size(0, -1, 0);
    prune(0, -1);
    nvs = 0;
    dfs(0, -1, 0);
    cout << - ssap() << '\n';
  }
}
