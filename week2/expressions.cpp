#include <cmath>
#include <iostream>
#include <numbers>
using namespace std;

// better sin function
template <typename T> static constexpr T improvedSin(const T &x) {
  if (x == numbers::pi_v<T>) {
    return 0;
  }
  return sin(x);
}

struct Horse {
  string communicate() const { return "neigh"; }
};

struct Cat {
  string communicate() const { return "meow"; }
};

struct Dog {
  string communicate() const { return "bark"; }
};

template <typename A> static constexpr void printSound2(const A &animal) {
  if constexpr (is_same_v<A, Cat>) {
    cout << "purr\n";
  } else if constexpr (is_same_v<A, Dog> || is_same_v<A, Horse>) {
    cout << animal.communicate() << endl;
  }
}

int main() {
  constexpr auto pi_double = numbers::pi_v<double>;
  constexpr auto pi_float = numbers::pi_v<float>;
  cout << "sin(pi <double>) is " << improvedSin(pi_double) << endl;
  cout << "sin(pi <float>) is " << improvedSin(pi_float) << endl;
  cout << "sin (0.f) is " << improvedSin(0.f) << endl;
  constexpr auto cat = Cat{};
  printSound2(cat);
  printSound2(10);
}
