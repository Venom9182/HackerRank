#include <cstdio>
#include <cstdint>
using namespace std;

int ri()
{
  int x;
  scanf("%d", &x);
  return x;
}

union {
  uint8_t a[1<<28];
  uint64_t b[1<<25];
} a;

int main() {
  int n = ri();
  unsigned s = ri(), p = ri(), q = ri();
  for (; n; n--) {
    a.a[(s & ~(1u<<31))>>3] |= 1 << (s&7);
    s = s*p+q;
  }
  s = 0;
  for (n = 1<<25; n; )
    s += __builtin_popcountll(a.b[--n]);
  printf("%u\n", s);
  return 0;
}
