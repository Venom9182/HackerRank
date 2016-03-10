#include <iostream>
using namespace std;

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) for (int i = 0; i < (n); i++)
#define REP1(i, n) for (int i = 1; i <= (n); i++)

int main()
{
  int a, b, x;
  cin >> a >> b >> x;
  if (a == 1 && b == x) {
    cout << "-1 -1" << endl;
    return 0;
  }
  REP1(i, x+1) {
    int j = x+2-i;
    if (a <= i*j && i*j <= b) {
      a = i;
      b = j;
      break;
    }
  }
  cout << a*b << ' ' << a*b*x/2 << endl;
  REP(i, a)
    REP(j, b) {
      FOR(k, i+1, a)
        cout << i*b+j+1 << ' ' << k*b+j+1 << endl;
      FOR(k, j+1, b)
        cout << i*b+j+1 << ' ' << i*b+k+1 << endl;
    }
}
