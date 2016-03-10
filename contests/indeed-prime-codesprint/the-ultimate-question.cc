#include <cstdio>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

int a[3], b[3];

int main()
{
  REP(i, 3)
    a[i] = ri();
  for (b[1] = 2; b[1]--; )
    for (b[2] = 2; b[2]--; ) {
      int s = 0;
      for (int j, i = 0; i < 3; i = j) {
        int t = a[i];
        for (j = i+1; j < 3 && b[j]; j++)
          t *= a[j];
        s += t;
      }
      if (s == 42) {
        const char op[] = "+*";
        printf("%d%c%d%c%d\n", a[0], op[b[1]], a[1], op[b[2]], a[2]);
        return 0;
      }
    }
  puts("This is not the ultimate question");
}
