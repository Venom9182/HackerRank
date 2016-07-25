#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <type_traits>
using namespace std;

#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

const long N = 50, M = 2000, V = 2*(N*M+1);
long allo, fork, suff, len[V], sl[V], size[V];
char a[N][M+1];
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
      while (it != to[fork].end() && suff > len[it->second] && to[it->second].size()) {
        fork = it->second;
        suff -= len[fork];
        cc = s[i+1-suff]; // may be NUL
        it = to[fork].find(cc);
      }
      if (it == to[fork].end()) {
        if (c)
          to[fork][cc] = new_node(&s[i+1-suff], size-(i+1-suff));
        sl[last] = fork;
        last = 0;
      } else {
        long u, t = pos[it->second][suff-1]; // may be NUL
        if (c == t) {
          sl[last] = fork;
          break;
        }
        if (! t) { // extend leaf of a preceding string
          u = it->second;
          to[u][c] = new_node(&s[i], size-i);
        } else {
          u = new_node(pos[it->second], suff-1);
          if (c)
            to[u][c] = new_node(&s[i], size-i);
          to[u][t] = it->second;
          pos[it->second] += suff-1;
          len[it->second] -= suff-1;
          it->second = u;
        }
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
  size[u] = len[u];
  for (auto& it: to[u]) {
    dfs(it.second);
    size[u] += size[it.second];
  }
}

void query(long u, long k)
{
  while (k > len[u]) {
    k -= len[u];
    if (u) {
      char t = pos[u][len[u]];
      pos[u][len[u]] = '\0';
      cout << pos[u];
      pos[u][len[u]] = t;
    }
    for (auto& it: to[u])
      if (k > size[it.second])
        k -= size[it.second];
      else {
        u = it.second;
        break;
      }
  }
  char t = pos[u][k];
  pos[u][k] = '\0';
  cout << pos[u];
  pos[u][k] = t;
}

int main()
{
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  long n, k;
  allo = fork = suff = 0;
  new_node(NULL, 0);
  cin >> n;
  while (n--) {
    cin >> a[n];
    add(a[n]);
  }
  dfs(0);
  cin >> n;
  while (n--) {
    cin >> k;
    if (k > size[0])
      cout << "INVALID\n";
    else {
      query(0, k);
      cout << '\n';
    }
  }
}
