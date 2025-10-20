#include <algorithm>
#include <functional>
#include <iostream>
#include <random>
#include <ranges>
#include <vector>

using namespace std;

int main() {
  auto vec = vector<int>{3, 4, 1, 6, 3, 5, 9, 2};
  constexpr int vec_size = 8;
  // Q1:
  auto index = views::iota(0, vec_size);
  // use ranges::for_each and view::iota to reverse the order of the elements in
  // a vector v.
  auto new_vec = vector<int>(vec_size);
  ranges::for_each(index, [&vec, &new_vec](int idx) {
    new_vec[idx] = vec[vec_size - 1 - idx];
  });
  // ranges::for_each(new_vec, [](int& i){ cout << i << " ";});
  vec = new_vec;
  for (int i : vec) {
    cout << i << " ";
  }
  cout << endl;

  // Q2 : Write a composition of views which takes a view on the multiples of
  // 18, filter those that are multiple of 27, and select the first 2 elements
  // that verify this property.
  auto time18 = [](int i) { return i * 18; };
  auto mulOf27 = [](int i) { return i % 27 == 0; };
  auto myPrint = [](auto i) { cout << i << " "; };
  // composing a filter view and the transform view
  auto dataTransform =
      vec | views::transform(time18) | views::filter(mulOf27) | views::take(2);
  ranges::for_each(dataTransform, myPrint);
  cout << endl;

  // Q3: Question 3 Write a composition of views that describe the coordinates x
  // of n grid points covering the interval [0,1].
  static constexpr int n = 20;
  auto divideNGrid = [](int i) {
    return static_cast<double>(static_cast<double>(i) /
                               static_cast<double>(n - 1));
  };
  auto grid = views::iota(0, n) | views::transform(divideNGrid);
  ranges::for_each(grid, myPrint);
  cout << endl;
}
