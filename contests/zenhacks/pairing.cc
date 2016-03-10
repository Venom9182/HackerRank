#include <iostream>
#include <set>
#include <string>
#include <tuple>
using namespace std;

const int N = 1000;
char a[N+1], b[N+1];

int main()
{
  int n, ans = 0;
  typedef tuple<string, int, string, char> typ;
  multiset<typ> S;
  cin >> n;
  while (n--) {
    string c, cc, t;
    int s;
    cin >> c >> s >> cc >> t;
    typ g{c, s, cc, 'L'+'R'-t[0]};
    if (S.count(g)) {
      S.erase(S.find(g));
      ans++;
    } else
      S.insert(typ{c, s, cc, t[0]});
  }
  printf("%d\n", ans);
}
