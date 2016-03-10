Complex operator+(const Complex &x, const Complex &y)
{
  return Complex{x.a + y.a, x.b + y.b};
}

ostream &operator<<(ostream &out, const Complex &x)
{
  out << x.a << "+i" << x.b;
  return out;
}
