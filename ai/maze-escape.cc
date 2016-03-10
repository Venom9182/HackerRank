#include <iostream>
#include <string>
using namespace std;

int main()
{
  string a[3];
  cin >> a[0];
  cin >> a[0] >> a[1] >> a[2];
  if (a[2][2] == '#' && a[1][2] != '#') cout << "RIGHT";
  else if (a[0][2] == '#' && a[0][1] != '#') cout << "UP";
  else if (a[0][0] == '#' && a[1][0] != '#') cout << "LEFT";
  else if (a[2][0] == '#' && a[2][1] != '#') cout << "DOWN";
  else cout << "UP";
  cout << endl;
}
