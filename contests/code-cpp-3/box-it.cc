#include <tuple>

class Box
{
  int l, b, h;
public:
  Box() : l(0), b(0), h(0) { BoxesCreated++; }
  Box(int l, int b, int h) : l(l), b(b), h(h) { BoxesCreated++; }
  Box(const Box &o) : l(o.l), b(o.b), h(o.h) { BoxesCreated++; }
  ~Box() { BoxesDestroyed++; }
  int getLength() const { return l; }
  int getBreadth() const { return b; }
  int getHeight() const { return h; }
  long long CalculateVolume() const { return (long long)l * b * h; }
  bool operator<(const Box &o) { return make_tuple(l, b, h) < make_tuple(o.l, o.b, o.h); }
  friend ostream& operator<<(ostream &out, Box B) {
    out << B.l << ' ' << B.b << ' ' << B.h;
    return out;
  }
};
