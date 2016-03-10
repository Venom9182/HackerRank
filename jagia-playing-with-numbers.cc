#include <cstdio>
using namespace std;

typedef long long ll;
#define REP(i, n) for (int i = 0; i < (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 1000000;
ll a[N+1];

// 1000000  11110100001001000000
// >999936  11110100001000000000 -> 64
// >999424  11110100000000000000 -> 448
// >983040  11110000000000000000 -> 15808
// otherwise -> 48576
int add(int x, ll v)
{
  int c = 0;
  for (; x <= N; x += x & -x)
    a[x] += v * ++c;
  return x - N;
}

ll sum(int x)
{
  ll s = 0;
  for (; x; x &= x-1)
    s += a[x];
  return s;
}

int main()
{
  for (int q = ri(); q--; ) {
    char op;
    scanf(" %c", &op);
    int x = ri(), y = ri();
    if (op == 'R')
      printf("%lld\n", sum(y)-sum(x-1));
    else {
      int z = ri();
      REP(i, 50) {
        int t = add(x, y); // t <= 48576
        add(t, y); // return 48576
        add(48576, 998ll*y);
        x += z;
        if (x > N)
          x -= N;
      }
    }
  }
}
