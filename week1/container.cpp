#include <array>
#include <iostream>
#include <vector>
#include <list>

int main() {
  auto v1 = std::vector<int>(10);
  auto v2 = std::vector<int>(10);
  auto last_element = *(--v1.end());
  auto last_element1 = *(v1.end()--);
  auto a1 = std::array<int, 5>();
  auto a2 = a1;
  std::cout << "last element: " << last_element << std::endl;
  std::cout << "last element 1: " << last_element1 << std::endl;

  // auto v3 = v1 + v2;
  // auto a3=std::array<int,5>;
  // a3 = a1;
  auto myList = std::list<int>{1, 2};
  auto iter = myList.begin();

  myList.push_back(3);
  myList.push_front(0);

  std::cout << *iter << " ";
  ++iter;
  std::cout << *iter << " ";

  for (auto iter = myList.begin(); iter != myList.end(); ++iter)
    std::cout << *iter << " ";
  std::cout << std::endl;
}
