#include <cstdio>
using namespace std;

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

int main()
{
  for (int n = ri(); n--; ) {
    unsigned a = ri(), b = ri();
    printf("%u\n", a == b ? a : a & -1u << 31-__builtin_clz(a^b));
  }
}
