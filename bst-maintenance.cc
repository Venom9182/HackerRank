#include <algorithm>
#include <cstdio>
#include <stack>
#include <utility>
using namespace std;

typedef long long ll;
#define REP(i, n) for (int i = 0; i < (n); i++)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )
#define fi first
#define se second

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 250000;
int tick, a[N], b[N], l[N], r[N], p[N], dep[N], size[N], heavy[N], pre[N], post[N];
ll fw_size[N], // pre[i] exists <=> array[i] == 1
  fw_s[N], // size[i]-size[i's heavy child]
  fw_ds[N]; // fw_s[i] * dep[i]

int dfs(int v)
{
  return v >= 0 ? size[v] = dfs(l[v]) + 1 + dfs(r[v]) : 0;
}

void add(ll fenwick[], int i, ll v)
{
  for (; i < N; i |= i+1)
    fenwick[i] += v;
}

ll getSum(ll fenwick[], int i)
{
  ll s = 0;
  for (; i; i &= i-1)
    s += fenwick[i-1];
  return s;
}

void heavyLight(int d, int v, int chain)
{
  int c[2], nc = 0;
  pre[v] = tick++;
  heavy[v] = chain;
  dep[v] = d;
  if (~ l[v]) {
    p[l[v]] = v;
    c[nc++] = l[v];
  }
  if (~ r[v]) {
    p[r[v]] = v;
    c[nc++] = r[v];
  }
  if (nc == 2 && size[c[0]] < size[c[1]])
    swap(c[0], c[1]);
  if (nc) {
    heavyLight(d+1, c[0], chain);
    if (nc == 2)
      heavyLight(d+1, c[1], c[1]);
  }
  post[v] = tick;
}

ll getSize(int i)
{
  return getSum(fw_size, post[i]) - getSum(fw_size, pre[i]);
}

void realMain()
{
  int n = ri();
  REP(i, n)
    a[i] = ri();
  iota(b, b+n, 0);
  sort(b, b+n, [](int i, int j) { return a[i] < a[j]; });

  // Cartesian tree construction
  stack<int> st;
  REP(i, n+1) {
    int j = i == n ? -1 : b[i], x = -1;
    for (; ! st.empty() && st.top() > j; st.pop()) {
      int y = st.top();
      r[y] = x;
      x = y;
    }
    if (i < n) {
      st.push(j);
      l[j] = x;
    }
  }

  dfs(0);
  heavyLight(0, 0, 0);
  ll ans = 0, sum = 0;
  REP(i, n) {
    ans += sum;
    for (int v = i; v; ) {
      int u = p[v];
      ans += (dep[i]-2*dep[u]) * (getSize(u)-getSize(v)); // contribution of `u`
      ll s = getSum(fw_s, pre[u]) - getSum(fw_s, pre[heavy[u]]),
        ds = getSum(fw_ds, pre[u]) - getSum(fw_ds, pre[heavy[u]]);
      ans += dep[i]*s - 2*ds; // contribution of ancestors of `u`
      if (heavy[v] != heavy[u]) {
        add(fw_s, pre[u], 1);
        add(fw_ds, pre[u], dep[u]);
      }
      v = heavy[u];
    }
    add(fw_size, pre[i], 1);
    add(fw_s, pre[i], 1);
    add(fw_ds, pre[i], dep[i]);
    sum += dep[i];
    printf("%lld\n", ans);
  }
}

int main()
{
  const size_t STACK_SIZE = 64*N+0xb612; // one call of heavyLight uses 64 bytes in my case
  static char st[STACK_SIZE];
  static long sp;
  asm volatile("movq %%rsp, %0\n\tmovq %1, %%rsp\n\t" : "=g"(sp) : "g"(st+STACK_SIZE) : "memory");
  realMain();
  asm volatile("movq %0, %%rsp\n\t" : "=g"(sp) :: "memory");
}
