#include <vector>
using namespace std;

template <typename V>
concept Vector = std::same_as<V,std::vector<typename V::value_type>>;

auto smallestElement(const Vector auto& elements) {
    return minElement(elements.begin(), elements.end());
}

int countSmallerThan(const Vector auto& items, auto toCompare) {
    // Implementation
    return 1;
}

template<int I>
struct SpaceObject {
    array<float, I> position{};
    array<float, I> velocity{};
    array<float, I> acceleration{};
};

int maint(){
  std::vector<int> x;
  std::vector<int>::value_type i=4;
  countSmallerThan(x, 4.5);
  auto spaceO = SpaceObject<3>{}; 
}

