/* Problem
   Number of ways to build a square with 6 sticks
*/
   
// O(n^2) * hashmap
// O(n^2+len) solution is intricate: https://www.hackerrank.com/contests/hourrank-4/challenges/newyear-present/editorial
#include <algorithm>
#include <cstdio>
#include <unordered_map>
#include <utility>
using namespace std;

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) for (int i = 0; i < (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const int N = 3000;
int a[N];

int main()
{
  int n = ri();
  long ans = 0;
  REP(i, n)
    a[i] = ri();
  sort(a, a+n);
  unordered_map<int, int> cnt;
  for (int ii, i = 0; i < n; i = ii) {
    for (ii = i+1; ii < n && a[i] == a[ii]; ii++);
    // a+b = c+d = e = f
    // e, f in [i,ii)
    if (ii-i > 1) {
      int j = 0, k = i-1;
      long s = 0, h = (ii-i)*(ii-i-1)/2;
      while (j < k)
        if (a[j]+a[k] < a[i])
          j++;
        else if (a[j]+a[k] > a[i])
          k--;
        else if (a[j] == a[k]) {
          int t = k-j+1;
          ans += h*(t-1)*t/2*s;
          ans += h*t*(t-1)*(t-2)*(t-3)/24;
          break;
        } else {
          int jj = j, kk = k;
          for (; a[j] == a[jj]; jj++);
          for (; a[k] == a[kk]; kk--);
          int f = jj-j, g = k-kk;
          ans += h*f*g*s;
          ans += h*f*(f-1)*g*(g-1)/4;
          s += f*g;
          j = jj;
          k = kk;
        }
    }
    // a+b+c = d = e = f
    // d, e, f in [j,jj)
    // c in [i,ii)
    for (int jj, j = ii; j < n; j = jj) {
      for (jj = j+1; jj < n && a[j] == a[jj]; jj++);
      if (jj-j > 2) {
        long h = long(jj-j)*(jj-j-1)*(jj-j-2)/6;
        if (3*a[i] == a[j])
          ans += long(ii-i)*(ii-i-1)*(ii-i-2)/6*h;
        else {
          int t = a[j]-2*a[i];
          auto eq = equal_range(a, a+i, t);
          if (eq.first != eq.second)
            ans += long(eq.second-eq.first)*(ii-i)*(ii-i-1)/2*h;
          auto it = cnt.find(a[j]-a[i]);
          if (it != cnt.end())
            ans += long(it->second)*(ii-i)*h;
        }
      }
    }
    for (int jj, j = 0; j < i; j = jj) {
      for (jj = j+1; jj < i && a[j] == a[jj]; jj++);
      cnt[a[j]+a[i]] += (ii-i)*(jj-j);
    }
    cnt[2*a[i]] += (ii-i)*(ii-i-1)/2;
  }
  printf("%ld\n", ans);
}
