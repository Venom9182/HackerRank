#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <utility>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); i++)
#define fi first
#define se second

int main()
{
  int n;
  string a;
  map<string, int> b, c;
  cin >> n;
  REP(i, n) {
    cin >> a;
    b[a]++;
  }
  REP(i, n) {
    cin >> a;
    c[a]++;
  }
  int ans = 0;
  for (auto &x: b)
    ans += min(x.se, c[x.fi]);
  cout << ans << endl;
}
