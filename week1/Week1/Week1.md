# Week1  

## Array, Vectors, and initialization  
### Array  
- Initialization  
```cpp
#include <array>
auto my_array=array<int, 4>{1,2,3,4};
for{ auto i:my_array};


auto a=array<double, 6>{1,2,3}; // all other 3 elements are 0
auto a=array{1,2,3}; // compiler set to int array of 3



```
- Brace initilization  
  
```cpp
auto i=int{2};
auto x=float{3.14f};

```
## Transfer of data from and into a function  
- dataset from and to a C++ function is  key performance issue, memory access is slow, much slower than computation. So, as much as possible, one should avoid copying data from one data structure to another unless the amount of data is small.  
### Value sematics vs reference semantics:  
* Value semantics in C++ means that objects behave like independent values - when you copy them, you get a completely separate object, and modifications to one don't affect the other.  
Key Characteristics  
* Copying creates an independent copy  
* Assignment replaces the entire value  
* Objects have automatic lifetime management  
* No shared ownership or aliasing concerns  
- Reference semantics means objects act like names/aliases for shared data:  
### Use the references to access the data of vectors  
```cpp
void printData(const vector<int>& w){
    for(auto i:w) cout << i << " ";
    count << endl;
} 

```
### Transfer data from a function  
- Problem with this function, data associated with w will be deleted due to out of scope => **copy elision **to avoid losing data  
```cpp
vector<int> multiplyByTwo(const vector<int>& v)
{
    auto w = vector<int>(v.size());
    for (int i=0; i<w.size(); i++) w[i] = 2*v[i];
    return w;
}
auto v1=vector<int>{1,2,3,4};
auto v2=multiplyByTwo(v1); //copy elision to copy address from w to v2 and avoid data deletion


```
- However, if there are several return statement in the function, then the compiler will not know which vector/data to be returned=> using Move semantics  
```cpp
auto v2 = vector<int>(5);

    v2=multiplyByTwo(v1); // the data of w were copied to v2, but V2 retained its adrress, which is different from w

```
- Tuple: a new data structure that contains data with different types  
```cpp
#include <tuple>
tuple<int,bool> t1;
auto t2=tuple<int, bool>{6,false};
t1 = make_tuple(10, true);
auto i=get,0.(t1);

```
Use tuples to get returned data  
```cpp
auto returnMultiple(unsigned value)
{
    return make_tuple(2*value, sqrt((float)value), value>10);
}

auto [intVal, floatVal, boolVal] = returnMultiple(77);

```

## Container - Iterators  
vectors’ iterators  
```cpp
// initialization
auto v = vector<int>{1,2,3,4}
auto iter = v.begin();

cout << *iter << endl; // we get 1

++iter;
cout << *iter << endl; // we get 2

// for loop
for (auto iter = v.begin(); iter!=v.end(); ++iter){
    cout << *iter << " "; // we get 1 2 3 4
}

```
lists’ iterators  
```cpp
#include <list>
auto myList = list<int>{1,2};
myList.push_back(3);
myList.push_front(0);
// myList[i] is not an acceptable syntax

// for loop
for (auto iter=myList.begin(); iter != myList.end(); ++iter){
    cout << *iter << " ";
}

```
## Algorithm and lambda functions  
transform function applies the predefined function f on each element of a container  
```cpp
#include <cmath>

// define the function
double f(double x) {return (2*sqrt(x)+1);}

auto v = vector{1.,2.,3.,4.};
auto w=vector<double>(4);

// using the transform lambda function
std::transform(v.begin(), v.end(), w.begin(), f);

for(auto i in v) {
    cout << i<< " "; // 3, 3.82843 4.4641 5
}

```
lamda function f, can be anywhere in the code, like a variable.  
```cpp
// general syntax: f = [capture] (arguments) {body};
auto f= [](double x) {return 2*sqrt(x) + 1);

auto a=2;
auto b=1;
auto f1 = [a, b](double x){return a*sqrt(x) +b};

// combine the lamda function f1 with transform function
transform(v.begin(), v.end(), w.begin(), [a,b](double x]{return a*sqrt(x) + b;});

```
the transform_reduce functions takes two lambda functions  
```cpp
auto a = 2, b=1;
auto linear = [a, b](int val){return a*x + b;};
auto add = [](int val1, int val2){return val1+val2;};

transform_reduce(v.begin(), v.end(), w.begin(), int{}, add, linear);
transform_reduce(v.begin(), v.end(), w.begin(), int{}, std::plus{}, linear);

```
## Ranges  
```cpp
#include <ranges>
#include <algorithm>
#include <random>
auto v=vector<float>(5);
iota(v.begin(), v.end(),0.f);

auto w=vector<float>(5);
ranges::transform(v, w.begin(), sqrtf);

ranges::fill(v, 1.f);

auto index=vector<int>(10);
iota(v.begin(), v.end(),0); // index is 0,1,2,3,4,5,6,7,8,9

// shuffle with a fixed random seed: 999
ranges::shuffle(index, mt19937{999});
// with a Mersenne -Twister sandom-number generator
ranges::shuffle(index, mt19937{random_device{}()});

//innitialize the random number generator
auto engine = mt199937{random_device{}()};

// select the uniform distribution, between 0 and 99
uniform_int_distribution<int> uniform{0, 99};

// define the random function
auto randint = [&uniform, &engine](){return uniform(engine);};

auto v = vector<int>(10);
range::generate(v, randint);
z

```
range::find()  
```cpp
auto w = vector{3,1,5,6,2,7};

// search for the element of value 2
auto it = ranges::find(w, 2);

// find its position in w; index will be 4
auto index = distance(w.begin(), it);

```
Other functions:  
- Ranges::equal(v, w): returns bool- whether or not two input containers are equal.  
- Range::all_of(): tests if all elements of input container meets a condition  
- for_each(range, lambda): apply a lambda function on each of the element of a input container  
  
  
## View  
Characteristics:  
- An object that describe a range but does not own the elements in the range  
- lazy-evaluation data specified in a view are generated only when needed  
- cheap to create, copy and move  
- allow the compiler to produce an optimal code  
  

Code examples:  
- iota  
```cpp
// returns a range but no data
auto index = views::iota(0,n);

myPrint = [](int i){cout << i <<" ";};
// compute and prints the values described by the view
ranges::for_each(index, myPrint);

```
- transform  
```cpp
auto v = vector{3,4,1,6,3,5,9,2};
// vTimes7 will only be computed if this variable is used
// in an other computation
auto vTimes7 = view::transform(v, [](int i){return 7*i;});

```
- Composition of view  
```cpp
auto vTimes7 = v|views::transform(multiplyBy7);

auto square = [](int i){return i*i;};
auto even = [](int i){return i%2==0;};

//composing a filter view and the transform view
auto dataTransform = data|views::filter(even)|views::transform(square);
ranges::for_each(dataTranform, myPrint);

```
- other views functions  
```cpp
views::take(N)
views::drop(N) // skip the first N elements
views::reverse(N)
views::zip()

```
## Smart Pointer  
### Shared pointers  
The object linked to the shared pointers are deallocated when all the pointers are out of scope  
```cpp
#include <memory>
shared_ptr<type> p;
auto p = make_shared<type>(new_object);

// p is not a pointer to x, but a ptr to a copy of x
auto p = make_shared<type>(new_object) ;

// p2 is a copy of p1, and points to the same vector
auto p2=p1;

```
### Unique pointer  
can only points to its first associated object, cant be copied, cant point to the same objects  
```cpp
unique_ptr<int> p0;
unique_ptr<int> pi = make_unique<int>(100);

```
### Vector of unique pointers  
```cpp
auto n = 10;
auto p = vector<unique_ptr<int>>(n);

for (int i=0; i<n;i++){
    p[i] = make_unique<int>(i);
}rar

for (auto i:p) count << *i << " ";

```
### Vector of pointers to an array  
```cpp
auto n =4;
// a vector of n pointers on two float arrays
auto p = vector<unique_ptr<array<float,2>>>(n);

auto x = vector<float>(2.f, 4.f, 1.f, 7.f};
auto y = vector<float>(0.f, 8.f, 3.f, 2.f};

for(int i =0; i<n; i++){
    p[i] = make_unique<array<float,2>>(array<float,2>{x[i], y[i]});
}

```
### Smart pointers and for_each  
```cpp
// lambda function
auto rotate = [](auto& ptr_array){
auto tmp =(*ptr_array)[0];
(*ptr_array)[0] = -(*ptr_array)[1];
(*ptr_array)[1] = tmp;};

```
## Structure and classes  
### Structures  
everything is public by default  
```cpp
struct Person
{
    //attributes
    int age;
    float height;
    string name;
};

int main(){
    auto myNeighbor = Person{21, 1.76, "Peter"};

}

```
Initialization of attributes with default values  
```cpp
struct Person
{
    int age{};
    float height{};
    string name{"noBody"};
}

auto John=Person{.height=0.52, .name="John”};
// all the attributes are copied, including the string which is a heap variable

```
### Class  
everything is private by default  

## Polymorphic classes

### Abstract class and virtual methods

```cpp
struct Shape{
	virtural ~Shape() = default; // destructor
  virtual double get_distance(double, double,
                              double, double) = 0; // pure virtual method
}
```

### Derived class

```cpp
struct Circle : public Shape {
	double cx{}, cy{}, radius{};
  Circle(double x, double y, double r):cx(x), cy(y), radius(r){}; 
  // explicit contructor is needed
  vitual double get_distance(double ax, double ay,
                             double bx, double by)
  {
    //compute distance from circle to line a, b
    return d;
  }
}

```

### Vector of pointers to shapes

```cpp
auto myShape = vector<unique_ptr<Shape>>{};
myShapes.push_back (make_unique<Circle>(Circle{1, 3, 4}));
myShape.push_back(make_unique<Circle>(Circle{3,5,1}));

ranges::transform(myShape, distance.begin(), 
                  [ax, ay, bx, by](auto& shape){
                  	return shape-> get_distance(ax, ay, bx, by);
                  }
                 )
```



