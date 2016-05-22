#include <algorithm>
#include <cstdio>
#include <functional>
#include <map>
#include <string>
#include <vector>
using namespace std;

#define REP(i, n) for (decltype(n) i = 0; i < (n); i++)

const int N = 2000;
char a[N+1];

int main()
{
  int n;
  map<vector<int>, vector<string>> m;
  map<string, vector<string>*> mm;
  scanf("%d", &n);
  REP(i, n) {
    scanf("%s", a);
    vector<int> h(10, 0);
    for (int j = 0; a[j]; j++)
      h[a[j]-'0']++;
    m[h].push_back(a);
  }
  int opt = 0;
  for (auto &x: m) {
    sort(x.second.begin(), x.second.end(), greater<string>());
    x.second.erase(unique(x.second.begin(), x.second.end()), x.second.end());
    if (x.second.size() > opt)
      opt = x.second.size();
  }
  for (auto &x: m)
    if (x.second.size() == opt)
      mm[x.second[0]] = &x.second;
  printf("%zd\n", m.size());
  for (auto &xx: mm) {
    for (auto &x: *xx.second)
      printf("%s ", x.c_str());
    puts("");
  }
}
