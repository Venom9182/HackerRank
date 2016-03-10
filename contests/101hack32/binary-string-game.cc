#include <algorithm>
#include <cstdio>
#include <functional>
using namespace std;

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) for (int i = 0; i < (n); i++)
#define ROF(i, a, b) for (int i = (b); --i >= (a); )

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 1001, M = 1000000;
char a[M+1];
int nim[N], mex[N];

int main()
{
  int tick = 0;
  ROF(_, 0, ri()) {
    int k = ri();
    scanf("%s", a);

    fill_n(nim, k, 0);
    FOR(i, k, N) {
      tick++;
      REP(j, i-k+1)
        mex[nim[j]^nim[i-k-j]] = tick;
      nim[i] = find_if_not(mex, mex+N, bind(equal_to<int>(), placeholders::_1, tick)) - mex;
    }
    int sum = 0;
    for (int j, i = 0; a[i]; )
      if (a[i] == '0')
        i++;
      else {
        for (j = i+1; a[j] == '1'; j++);
        sum ^= nim[k != 2 || j-i < 36 ? j-i : (j-i-36)%34+36];
        i = j;
      }
    puts(sum ? "Alice" : "Bob");
  }
}
