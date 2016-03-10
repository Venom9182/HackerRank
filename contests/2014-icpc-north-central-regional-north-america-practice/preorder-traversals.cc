#include <cstdio>
#include <vector>
using namespace std;

int main()
{
  char c;
  int cases = 0, x, p = 0;
  vector<int> s;
  bool tak = true;
  while (scanf("%d", &x) == 1) {
    if (x < 0) {
      printf("Case %d: %s\n", ++cases, tak ? "yes" : "no");
      p = 0;
      tak = true;
      s.clear();
    } else if (tak) {
      if (x <= p)
        tak = false;
      else {
        while (s.size() && s.back() <= x) {
          if (s.back() == x)
            tak = false;
          else
            p = s.back();
          s.pop_back();
        }
        s.push_back(x);
      }
    }
  }
}
