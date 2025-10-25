#include <algorithm>
#include <iostream>
#include <memory>
#include <ranges>
#include <vector>
using namespace std;

// Q2
class Shape {
public:
  // Pure virtual function
  virtual void whoAmI() const = 0;
  [[nodiscard]] virtual bool left_off(double x) const = 0;

  // destructor
  virtual ~Shape() = default;
};

class Circle : public Shape {
  double cx{}, cy{}, radius{};

public:
  Circle(double x, double y, double r) : cx(x), cy(y), radius(r) {};
  void whoAmI() const override { cout << "Circle" << endl; }
  [[nodiscard]] bool left_off(double x) const override {
    return (cx + radius) < x;
  }
};

class Rectangle : public Shape {
  double llx{}, lly{}, urx{}, ury{};

public:
  Rectangle(double x0, double y0, double x1, double y1)
      : llx(x0), lly(y0), urx(x1), ury(y1) {};
  void whoAmI() const override { cout << "Rectangle" << endl; }
  [[nodiscard]] bool left_off(double x) const override {
    return (llx < x) && (urx < x);
  }
};

// Q4
class Person {
public:
  // pure virtual function
  virtual void behavior() = 0;
  // destructor
  virtual ~Person() = default;
};

class Child : public Person {
public:
  static int count_children;
  void behavior() override { count_children += 1; }
};

class Adult : public Person {
public:
  static int count_adults;
  void behavior() override { count_adults += 1; }
};
int Child::count_children = 0;
int Adult::count_adults = 0;
int main() {
  // Q3
  auto shapes = vector<unique_ptr<Shape>>{};
  shapes.push_back(make_unique<Circle>(Circle{-3.5, 5, 10}));
  shapes.push_back(make_unique<Circle>(Circle{-5, 6, 7}));
  shapes.push_back(make_unique<Rectangle>(Rectangle{-3.5, 5, 4.5, 7.4}));
  auto shapeLeftOfX = shapes | views::filter([](unique_ptr<Shape> &p) {
                        return p->left_off(5.0);
                      });
  ranges::for_each(shapeLeftOfX, [](unique_ptr<Shape> &p) { p->whoAmI(); });
  // Q4
  auto people = vector<unique_ptr<Person>>{};
  people.push_back(make_unique<Adult>());
  people.push_back(make_unique<Child>());
  people.push_back(make_unique<Adult>());
  people.push_back(make_unique<Child>());
  people.push_back(make_unique<Child>());
  ranges::for_each(people, [](unique_ptr<Person> &p) { p->behavior(); });
  cout << "child_count:" << Child::count_children << endl;
  cout << "adult_count:" << Adult::count_adults << endl;
}
