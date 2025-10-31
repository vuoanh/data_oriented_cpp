#include <iostream>
#include <variant>

using namespace std;

struct PrintType{
  void operator()(const int& n) const {
    cout << "Variable holds an int" << endl;
  }

  void operator()(const double &n) const {
    cout << "Variable holds a double" << endl;
  }
};

static constexpr void useVariant(const variant<int, double> &var){
 visit(PrintType{}, var);
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
using Animal = variant<Horse, Cat, Dog>; 

static constexpr void makeSound(const Animal& animal) {
    visit([](auto& a){cout << a.communicate() << endl;}, animal);
}

int main(){
	constexpr auto n1 = variant<int, double>{4};
	constexpr auto n2 = variant<int, double>{10.5};
	useVariant(n1);
	useVariant(n2);
	constexpr auto a1 = Horse{};
	constexpr auto a2 = Cat{};
	constexpr auto a3 = Dog{};
	makeSound(a1); 
	makeSound(a2); 
	makeSound(a3); 
}
