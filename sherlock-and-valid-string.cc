#include <algorithm>
#include <cstdio>
using namespace std;

const int N = 100000;
char a[N+1];
int c[26];

int main()
{
  scanf("%s", a);
  for (int i = 0; a[i]; i++)
    c[a[i]-'a']++;
  sort(c, c+26);
  int i = upper_bound(c, c+26, 0) - c, t;
  puts(c[i] == c[26-1] || c[i]+1 == c[26-1] && c[26-2] < c[26-1] || 1 == c[i] && c[i] < c[i+1] && c[i+1] == c[26-1] ? "YES" : "NO");
}
