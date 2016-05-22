#include <iostream>
using namespace std;

const long N = 100000;
char a[N+1];

int main()
{
  long n, k, s = 0;
  cin >> n >> k >> a;
  for (long i = 0, j = n-1; i < j; i++, j--)
    if (a[i] != a[j])
      s++;
  if (k < s)
    return (cout << "-1\n"), 0;
  for (long i = 0, j = n-1; i < j; i++, j--)
    if (a[i] == '9') {
      if (a[j] != '9')
        k--, s--, a[j] = '9';
    } else if (a[j] == '9')
      k--, s--, a[i] = '9';
    else if (a[i] == a[j]) {
      if (k-2 >= s)
        k -= 2, a[i] = a[j] = '9';
    } else {
      if (k > s)
        k -= 2, s--, a[i] = a[j] = '9';
      else if (a[i] < a[j])
        k--, s--, a[i] = a[j];
      else
        k--, s--, a[j] = a[i];
    }
  if (n%2 && k && a[n/2] < '9')
    a[n/2] = '9';
  cout << a << endl;
}
