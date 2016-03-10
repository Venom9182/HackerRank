struct Available_Workshops { vector<pair<int, int>> a; };

Available_Workshops *initialize(int *a, int *b, int n)
{
  auto x = new Available_Workshops;
  x->a.resize(n);
  for (int i = 0; i < n; i++)
    x->a[i] = {a[i]+b[i], b[i]};
  return x;
}

int CalculateMaxWorkshops(Available_Workshops *x)
{
  vector<pair<int, int>> &a = x->a;
  sort(a.begin(), a.end());
  int last = 0, s = 0;
  for (auto x: a) {
    if (last <= x.first-x.second) {
      last = x.first;
      s++;
    }
  }
  delete x;
  return s;
}
