#include <iostream>
#include <iomanip> 
using namespace std;

int main() {
  int T; cin >> T;
  cout << setiosflags(ios::uppercase);
  cout << setw(0xf) << internal;
  while(T--) {
    double A; cin >> A;
    double B; cin >> B;
    double C; cin >> C;

    cout << setw(0) << nouppercase << setiosflags(ios::showbase) << hex << long(A) << resetiosflags(ios::showbase) << endl;
    cout << showpos << right << setw(15) << setfill('_') << fixed << setprecision(2) << B << noshowpos << endl;
    cout << scientific << uppercase << setprecision(9) << C << endl;
  }
}
