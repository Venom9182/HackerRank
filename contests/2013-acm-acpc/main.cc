#include <cstdio>

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

int main()
{
  int cc = ri();
  while (cc--) {
    int n = ri(), m = ri(), x = ri();
    puts((n-1)%m == x-1 ? "YES" : "NO");
  }
}
