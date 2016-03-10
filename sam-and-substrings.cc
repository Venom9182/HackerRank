#include <algorithm>
#include <iostream>
using namespace std;
typedef long long ll;
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int MOD = 1000000007;

int main()
{
  string s;
  cin >> s;
  int l = s.size();
  ll t = 0, ans = 0;
  REP(i, l) {
    t = (t*10+(i+1)*(s[i]-'0'))%MOD;
    ans = (ans+t)%MOD;
  }
  cout << ans << endl;
}
