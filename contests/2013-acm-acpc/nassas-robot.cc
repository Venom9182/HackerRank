#include <cstdio>
using namespace std;

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

char a[100001];

int main()
{
  int cc = ri();
  while (cc--) {
    int x = 0, y = 0, z = 0;
    scanf("%s", a);
    for (char *p = a; *p; p++)
      switch (*p) {
      case 'L': x--; break;
      case 'R': x++; break;
      case 'U': y++; break;
      case 'D': y--; break;
      case '?': z++; break;
      }
    printf("%d %d %d %d\n", x-z, y-z, x+z, y+z);
  }
}
