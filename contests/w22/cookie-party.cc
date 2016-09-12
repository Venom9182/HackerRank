#include <iostream>
using namespace std;

int main()
{
  long n, m;
  cin >> n >> m;
  cout << (n-m%n)%n << endl;
}
