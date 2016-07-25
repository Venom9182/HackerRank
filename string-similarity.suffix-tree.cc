#include <cstring>
#include <iostream>
#include <map>
#include <type_traits>
using namespace std;

#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

const long N = 100000, V = 2*(N+1);
long allo, fork, suff, len[V], sl[V], cnt[V];
char a[N+1];
char* pos[V];
map<long, long> to[V];

long new_node(char* p, long l)
{
  pos[allo] = p;
  len[allo] = l;
  sl[allo] = 0;
  to[allo].clear();
  return allo++;
}

void add(char* s)
{
  long size = strlen(s);
  REP(i, size+1) {
    long last = 0, c = s[i]; // may be NUL
    suff++;
    while (suff > 0) {
      long cc = s[i+1-suff]; // may be NUL
      auto it = to[fork].find(cc);
      while (it != to[fork].end() && suff > len[it->second]) {
        fork = it->second;
        suff -= len[fork];
        cc = s[i+1-suff]; // may be NUL
        it = to[fork].find(cc);
      }
      if (it == to[fork].end()) {
        //if (c) a suffix is indicated by NULL
          to[fork][cc] = new_node(&s[i+1-suff], size-(i+1-suff));
        sl[last] = fork;
        last = 0;
      } else {
        long u, t = pos[it->second][suff-1]; // may be NUL
        if (c == t) {
          sl[last] = fork;
          break;
        }
        u = new_node(pos[it->second], suff-1);
        //if (c) a suffix is indicated by NULL
          to[u][c] = new_node(&s[i], size-i);
        to[u][t] = it->second;
        pos[it->second] += suff-1;
        len[it->second] -= suff-1;
        it->second = u;
        sl[last] = u;
        last = u;
      }
      if (fork)
        fork = sl[fork];
      else
        suff--;
    }
  }
}

void dfs(long u)
{
  cnt[u] = to[u].empty();
  for (auto& it: to[u]) {
    dfs(it.second);
    cnt[u] += cnt[it.second];
  }
}

int main()
{
  cin >> a;
  while (cin >> a) {
    allo = fork = suff = 0;
    new_node(NULL, 0);
    add(a);
    dfs(0);
    long ans = 0, l = 0, u = 0, v;
    while (a[l]) {
      v = to[u][a[l]];
      ans += (cnt[u]-cnt[v])*l;
      l += len[v];
      u = v;
    }
    cout << ans+l << '\n';
  }
}
