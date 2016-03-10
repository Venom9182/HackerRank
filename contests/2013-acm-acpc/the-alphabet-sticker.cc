#include <cstdio>
using namespace std;

typedef long long ll;

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 10000, MOD = 1000000007;
char a[N+1];

int main()
{
  int cc = ri();
  while (cc--) {
    ll ans = 1;
    scanf("%s", a);
    for (int j, i = 0; a[i]; )
      if (a[i] != '?')
        i++;
      else {
        for (j = i; a[j] && a[j] == '?'; j++);
        if (i && a[j] && a[i-1] != a[j])
          ans = ans*(j-i+1)%MOD;
        i = j;
      }
    printf("%lld\n", ans);
  }
}
