#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

#define FOR(i, a, b) for (decltype(b) i = (a); i < (b); i++)
#define REP(i, n) for (decltype(n) i = 0; i < (n); i++)

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

const long P = 5000000;
long order[P], pw[P];

long blankinship(long a, long b, long &x, long &y)
{
  for (long u = y = 1, v = x = 0; a; ) {
    long q = b/a;
    swap(x -= q*u, u);
    swap(y -= q*v, v);
    swap(b -= q*a, a);
  }
  return b;
}

long pow_mod(long a, long b, long mod)
{
  long r = 1;
  for (; b; b >>= 1) {
    if (b & 1)
      r = r * a % mod;
    a = a * a % mod;
  }
  return r;
}

long prim_root(long p)
{
  vector<long> f;
  long pp = p-1;
  for (long i = 2; i*i <= pp; i++)
    if (pp%i == 0) {
      f.push_back(i);
      while ((pp /= i) % i == 0);
    }
  if (pp > 1)
    f.push_back(pp);
  FOR(r, 2, p) {
    for (long q: f)
      if (pow_mod(r, (p-1)/q, p) == 1)
        goto next;
    return r;
next:
    ;
  }
  return 0;
}

int main()
{
  long p = ri(), cc = ri(), r = prim_root(p);
  order[1] = 0; pw[0] = 1;
  for (long o = 1, i = r; i > 1; i = i*r%p, o++)
    order[i] = o, pw[o] = i;
  while (cc--) {
    long k = ri(), n = (ri()%p+p)%p;
    if (! n)
      puts("0");
    else {
      long x, y, d = blankinship(k, p-1, x, y);
      if (order[n] % d)
        puts("NONE");
      else {
        vector<long> f;
        REP(i, d)
          f.push_back(pw[(order[n]/d*x%(p-1)+(p-1)+(p-1)/d*i)%(p-1)]);
        sort(f.begin(), f.end());
        for (long x: f)
          printf("%ld ", x);
        puts("");
      }
    }
  }
}
