#include <algorithm>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>
using namespace std;
struct Person {
  string name;
  int age;
  constexpr void compare_name(const Person &other) const {
    if (name == other.name) {
      cout << "they have the same name.\n";
    } else {
      cout << "they doenst have the same name.\n";
    }
  }
};
// Q4
static constexpr int f(int &i, int &j) {
  static int nx = 10;
  return nx * i + j;
}

static constexpr int ageOfOldest(const vector<Person> &vec) {
  return ranges::max(
      vec | views::transform([](const Person &per) { return per.age; }));
}
int main() {
  auto person1 = Person("Tom", 2);
  auto person2 = Person("Thom", 20);
  auto person3 = Person("Tim", 15);
  person1.compare_name(person2);
  person1.compare_name(person3);
  person3.compare_name(person2);
  auto people = vector<Person>{person1, person2, person3};
  cout << "age of oldest is " << ageOfOldest(people) << endl;
  // Create a view of people that are younger than 20
  ranges::for_each (
    people|views::filter([](Person& p){return p.age < 20;}),
 [](Person& p){ cout << p.name << " ";});
  cout << endl;
}
