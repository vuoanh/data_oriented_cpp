#include <vector>

using namespace std;

struct Circle {
    vector<double> intersect(const double a, const double b) const;
    double x{};
    double y{};
    double r{};
};
template<typename Shape> 
static constexpr void ReturnInterface(const Shape& shape, vector<double> vec){
  visit([vec](auto& x){vec = x.intersect();}, shape);
}

template<typename ObjectVariant>
vector<double> intersect(const vector<ObjectVariant>& objects, double a, double b) {
    auto intersections = vector<double>{};
    for(auto object: objects) {
        visit([&intersections, a, b](auto obj) {
            auto newInters = obj.intersect(a, b);
            intersections.insert(intersections.end(), newInters.begin(), newInters.end());
        });
    }
    return intersections;
}
