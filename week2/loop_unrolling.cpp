#include <array>
#include <iostream>
#include <type_traits>
using namespace std;

template <int N, typename F> 
static constexpr auto unrolledSum(F f) {
  if constexpr (N == 0) {
    return f(N);
  } else
    return f(N) + unrolledSum<N - 1>(f);
}

template <typename T, int N>
static constexpr T sumOfPositive(const array<T, N> &v) {
  static_assert(is_arithmetic_v<T>,
                "The type of the input array element must be arithmetic");
  return unrolledSum<N - 1>([&v](int i) { return v[i] > T{} ? v[i] : T{}; });
}
int main() {
  constexpr auto arr = array<double, 5>{2, 3.5, -2.7, -5, 1};
  auto sum = sumOfPositive<double, 5>(arr);
  cout << sum << endl;
}
