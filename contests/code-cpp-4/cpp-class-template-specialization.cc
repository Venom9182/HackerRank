#include <iostream>
using namespace std;
enum class Fruit { apple, orange, pear };
enum class Color { red, green, orange };

template <typename T> struct Traits;

template<>
struct Traits<Fruit> {
  static string name(int x) {
    return x == 0 ? "apple" : x == 1 ? "orange" : x == 2 ? "pear" : "unknown";
  }
};

template<>
struct Traits<Color> {
  static string name(int x) {
    return x == 0 ? "red" : x == 1 ? "green" : x == 2 ? "orange" : "unknown";
  }
};

int main()
{
  int t = 0; std::cin >> t;

  for (int i=0; i!=t; ++i) {
    int index1; std::cin >> index1;
    int index2; std::cin >> index2;
    cout << Traits<Color>::name(index1) << " ";
    cout << Traits<Fruit>::name(index2) << "\n";
  }
}
