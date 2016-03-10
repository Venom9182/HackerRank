#include <cstdio>
#include <map>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 1000;
int d[N], p[N];

int main()
{
  int n = ri();
  multimap<int, int> a;
  REP(i, n)
    a.emplace(d[i] = ri(), i);
  while (a.size() > 1) {
    auto it = a.begin();
    int v = it->second;
    a.erase(it);
    it = a.end();
    --it;
    int u = it->second;
    a.erase(it);
    p[v] = u+1;
    a.emplace(--d[u], u);
  }
  REP(i, n)
    printf("%d\n", p[i]);
}
