#include <algorithm>
#include <cstdio>
#include <type_traits>
#include <utility>
#include <vector>
using namespace std;

typedef pair<long, long> pll;
#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define ROF(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (b); --i >= (a); )

long rl()
{
  long x;
  scanf("%ld", &x);
  return x;
}

const int N = 500000;
long tick, order[N];
vector<long> es[N], ch[N];
pll dfn[N], b[N];

void dfs(long u, long p)
{
  order[tick] = u;
  dfn[u].first = tick++;
  ch[u].push_back(tick);
  for (long v: es[u])
    if (v != p) {
      dfs(v, u);
      ch[u].push_back(tick);
    }
  dfn[u].second = tick;
}

void rmain()
{
  long n = rl(), m, k;
  REP(i, n-1) {
    long u = rl()-1, v = rl()-1;
    es[u].push_back(v);
    es[v].push_back(u);
  }
  dfs(0, -1);
  ROF(_, 0, rl()) {
    long k = rl(), v;
    REP(i, k)
      b[i] = dfn[rl()-1];
    sort(b, b+k, [&](const pll& x, const pll& y) {
      if (x.second != y.second)
        return x.second < y.second;
      return x.first > y.first;
    });

    long rt = order[b[k-1].first], branch = -1;
    v = 1;
    REP(i, k-1) {
      int t = upper_bound(ch[rt].begin(), ch[rt].end(), b[i].first) - ch[rt].begin();
      if (branch >= 0 && branch != t) { v = 0; break; }
      branch = t;
    }
    // v == 1 if the topmost node has more than one branch

    long s = 1;
    FOR(i, 1, k-1)
      if (b[s-1].second <= b[i].first)
        b[s++] = b[i];
    // s == number of leaves
    printf("%ld\n", k == 1 ? 0 : (s+v+1)/2);
  }
}

int main()
{
  const size_t STACK_SIZE = 96*N+0xb612;
  static char st[STACK_SIZE];
  static long sp;
  asm volatile("movq %%rsp, %0\n\tmovq %1, %%rsp\n\t" : "=g"(sp) : "g"(st+STACK_SIZE) : "memory");
  rmain();
  asm volatile("movq %0, %%rsp\n\t" : "=g"(sp) :: "memory");
}
