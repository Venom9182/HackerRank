#include <algorithm>
#include <cstring>
#include <iostream>
#include <type_traits>
using namespace std;

#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define ROF(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (b); --i >= (a); )

const long N = 50001;
char a[N], b[N], c[N];

int main()
{
  char h[256], hh[16];
  REP(i, 10) h['0'+i] = i, hh[i] = '0'+i;
  REP(i, 6) h['a'+i] = h['A'+i] = 10+i, hh[10+i] = 'A'+i;
#define F(a, i) (a[i/4] >> i%4 & 1)
#define S(a, i) (a[i/4] |= 1 << i%4)
#define U(a, i) (a[i/4] &= ~ (1 << i%4))
  long cases, k;
  for (cin >> cases; cases--; ) {
    cin >> k >> a >> b >> c;
    long na = strlen(a), nb = strlen(b), nc = strlen(c);
    reverse(a, a+na);
    reverse(b, b+nb);
    reverse(c, c+nc);
    REP(i, na) a[i] = h[a[i]];
    REP(i, nb) b[i] = h[b[i]];
    REP(i, nc) c[i] = h[c[i]];
    long n = max(max(na, nb), nc), m = 0;
    fill_n(a+na, n-na, 0);
    fill_n(b+nb, n-nb, 0);
    fill_n(c+nc, n-nc, 0);
    REP(i, n*4)
      switch (F(a,i)*4 + F(b,i)*2 + F(c,i)) {
      case 0b001: S(b, i); k--; break;
      case 0b010: U(b, i); k--; break;
      case 0b100: U(a, i); k--; break;
      case 0b110: U(a, i); U(b, i); k -= 2; break;
      }
    ROF(i, 0, n*4) {
      if (k <= 0) break;
      switch (F(a,i)*4 + F(b,i)*2 + F(c,i)) {
      case 0b101: if (k >= 2) { U(a, i); S(b, i); k -= 2; } break;
      case 0b111: U(a, i); k--; break;
      }
    }
    if (k < 0)
      cout << "-1\n";
    else {
      REP(i, n) a[i] = hh[a[i]];
      REP(i, n) b[i] = hh[b[i]];
      reverse(a, a+n);
      reverse(b, b+n);
      a[n] = b[n] = '\0';
      char *pa = a, *pb = b;
      while (pa < a+n-1 && *pa == '0') pa++;
      while (pb < b+n-1 && *pb == '0') pb++;
      cout << pa << '\n' << pb << '\n';
    }
  }
}
