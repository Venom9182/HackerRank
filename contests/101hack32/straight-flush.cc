#include <algorithm>
#include <cstdio>
using namespace std;

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) for (int i = 0; i < (n); i++)

int main()
{
  char a[9];
  int b[15] = {}, c[26] = {};
  REP(i, 5) {
    fgets(a, sizeof a, stdin);
    c[a[1]-'A']++;
    switch (a[0]) {
    case '2' ... '9': b[a[0]-'0']++; break;
    case 'T': b[10]++; break;
    case 'J': b[11]++; break;
    case 'Q': b[12]++; break;
    case 'K': b[13]++; break;
    case 'A': b[1]++; b[14]++; break;
    }
  }
  FOR(i, 1, 11)
    if (b[i] && b[i+1] && b[i+2] && b[i+3] && b[i+4] && *max_element(c, c+26) == 5)
      return puts("YES"), 0;
  puts("NO");
}
