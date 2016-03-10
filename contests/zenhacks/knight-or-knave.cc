#include <algorithm>
#include <cstdio>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 100000;
int a[N], c[N], d[N];
char b[N+1];

int main()
{
  for (int cc = ri(); cc--; ) {
    int n = ri(), id = 0;
    fill_n(c, n, -1);
    fill_n(b, n, 0);
    fill_n(d, n, 0);
    REP(i, n) {
      a[i] = ri();
      if (a[i] > 0) a[i]--;
    }
    REP(i, n)
      if (! b[i]) {
        int x = i, t = 0;
        for (; ; ) {
          b[x] = 'C';
          x = a[x] < 0 ? t^=1, ~a[x] : a[x];
          if (b[x]) break;
        }
        int cc = b[x] == 'C' ? id++ : c[x];
        t = b[x] <= 'B' && b[x]-'A' != t;
        x = i;
        for(;;) {
          b[x] = 'A'+t;
          if (b[x] == 'A') d[cc]++;
          else d[cc]--;
          c[x] = cc;
          x = a[x] < 0 ? t^=1, ~a[x] : a[x];
          if (b[x] <= 'B') break;
        }
      }
    REP(i, n)
      if (d[c[i]] < 0)
        b[i] = 'A'+'B'-b[i];
    b[n] = 0;
    puts(b);
  }
}
