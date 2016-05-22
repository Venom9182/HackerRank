#include <cstdio>
#include <type_traits>
using namespace std;

#define ROF(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (b); --i >= (a); )

long rl()
{
  long x;
  scanf("%ld", &x);
  return x;
}

const long N = 1000000;
char a[N+1];

int main()
{
  ROF(_, 0, rl()) {
    scanf("%s", a);
    long m = rl();
    char *q = a;
    for (char *p = a; *p; p++) {
      while (m && a < q && q[-1] < *p)
        q--, m--;
      *q++ = *p;
    }
    q[-m] = '\0';
    puts(a);
  }
}
