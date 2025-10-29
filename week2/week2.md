# week2: compile_time code execution

## Templates

### Why do we need tempates:

- easier to maitain codes if you need function overload
- c-macros :  awkward syntax, difficult to generalize, no compiler diagnostics (type checking) provided in the original, non-expanded code

```cpp
// function template
template <typename T>
auto iPow(T x, int n){
	auto result = T{1};
	for (int i=0, i<n, ++i){
		result *= x;	
	}
	return result;
}

// class template 
template <typename T>
struct Insect {
  array<T, 2> position{};
  array<T,2> velosity{};
  T timeSinceChange{};
};

auto insect = Insect<double> { // instatiate with double datatype
  .velosity = {1.0, 0.0}
};

auto insect = Insect{
  {.velocity = array<double,2>{1., 0.}}
};
```

### C++ metaprogramming

- Common C++ code + Generic code sequences => machine code
- generic code : instantiates templates and expands constant expressions

## Abbreviated function templates

- Examples

```cpp
// standard syntax
template<typename T>
auto ipow(T x, int n){
	auto result = T{1};
  for (int i=0, i<n, ++i){
    result *=x;
  }
  return result;
}

// abbreviated syntax (not very elegant)
auto ipow(auto x, int n){
  auto result = decltype(x){1}; //needs to access type of x
  // only works if x is not constant or a reference
  for (int i=0, i<n, ++i){
    result *=x;
  }
  return result;
}
```

- Lamda functions (from C++20)

```cpp
//---------1 template parameter-----------
// abbreviated syntax
auto iPow = [](auto x, int n){
	auto result = decltype(x){1};
	for (int i=0; i<n; ++i) result *= x;
	return result;
};

// explicit type
auto iPow = []<template T>(T x, int n){
	auto result = x{1};
	for (int i=0; i<n; ++i) result *= x;
	return result;
  
  
//---------multiple template parameters-----------
// explicit type
template<typename T1, typename T2>
array<T1,2> integrate(
  array<T1, 2> pos,
  array<T2, 2> vel
) {
  return { pos[0] + vel[0],
           pos[1] + vel[1]
         };
}
// abbreviated syntax
auto integrate(
  array<auto, 2> pos,
  array<auto, 2> vel
) {
  return decltype(pos) // needs to 
  { pos[0] + vel[0], pos[1] + vel[1]};
}

auto pos = array<double, 2>{1., 1.};
auto vel = array<float, 2>{0.f, 1.f};
pos = intergate(pos, vel);
```



### Attention: the meaning of the auto keyword

- auto for type deduction

```cpp
// type is known at the momment of writing (double)
auto x = 1.0; 
```

- Auto to declare templates

```cpp
// declare the a template with abbreviated syntax. Type is generic
auto iPow(auto x, int n){
	...
}
```

- compare to dynamic language like python, auto in declaring template in cpp is still faster than python code as python codes perform type checking at run time and add overhead cost.

## Template specialization and integer arguments

- template specialization of a function to specifies how the function should be overloaded with specific datatypes (cant include generic datatypes)

```cpp
// explicit type
template<typename T1, typename T2>
array<T1,2> integrate(
  array<T1, 2> pos,
  array<T2, 2> vel
) {
  return { pos[0] + vel[0],
           pos[1] + vel[1]
         };
}
// template specification for string
template<>
auto iPow<string>(T x, int n){
	return x + "^" + to_string(n);
}
```

- this can also be possible to class templates. And we can use a mix of specified and generic variables (unlike for template specialization for functions)

```cpp
//---------1 template parameter-----------
template <typename T>
struct struct_iPow{
	T operator()(T x, int n) const{
		...
		return results;
	}
};

template <>
struct struct_iPow<string> {
	T operator()(T x, int n) const{
		return x + "^" + to_string(n);
	}
};
```

### integer arguments in template specialization

- Template parameters can be data types or integers

```cpp
// The value I is known at compile time
template <typename T, int n>
struct struct_iPow{
	T operator()(T x) const {
    auto result = T{1};
    for (int i=0; i < n; ++i) result *= x;
    return result;
	}
};

// Compiler create different versions of iPow
// for a different version of n
auto a = iPow<int, 3>(10);
auto b = iPow<int, 4>(10);
```

- interger arguments can also be specilized

```cpp
template <>
auto iPow<double, 0>(double x){
  return 0;
}
```



## Constant expression

- constexpr variable is guaranteed to be initialized at compile time
- constexpr function can be evaluated at compile time if all of its arguments are constant expressions and the context requires a constant expression
- consteval function (only) is guaranteed to be evaluated at compile time. Any call to a constevel function must result in a compile-time constant expression.

## Compile-time polymorphism using templates

```cpp
struct SocialInsect{
	array<float, 2> vel{};
  auto k = 1.e-3;
  void adapt(array<float,2> nbvel){
    vel[0] += k*(nbVel[0] - vel[0]);
    vel[1] += k*(nbVel[1] - vel[1]);
  }
};

struct AntoSocialInsect{
  array<float, 2> vel{};
  void flee(array<float, 2> nbVel){
    vel[0] = -nbVel[0];
    vel[1] = -nbVel[1];
  }
}
```

without template specialization, use the `std::is_same_v` and `if constexpr` 

```cpp
template<typename Insect>
void react(Insect& insect, array<float, 2> nvVel) {
  // 'if constexpr' statement can exclude some code 
  // from the the compilation process
  if constexpr (is_same_v<Insect, SocialInsect>){
    insect.adapt(nbVel);
  }
  else if constexpr (is_same_v<Insect, AntiSocialInsect>){
    insect.flee(nbVel);
  }
}
```

## Loop unrolling

original version

```cpp
template<int N> double stecial(
	vector<double> & u, int i, counst auto& ind, const auto& weight){
  auto sum = u[i + ind[0]] * weight[0];
  for(int i = 1; i < N; ++i) {
    sum += u[i+ind[i]] * weight[i];
  }
  return sum;
}

```

the unrolled version: instantiate a function template recursively for every loop element

```cpp
template<int N, typename F> 
double unrolledSum(F f){
	if constexpr(N == 0){
    return f(N);
  }
  else{
    return f(N) + unrolledSum<N -1>(f);
  }
}

template<int N> double stecial(
	vector<double> & u, int i, counst auto& ind, const auto& weight){
	return unrolledSum<N-1>(
  	[&u, &ind, &eight, i](auto irel){
      return weight[irel] * u[i + ind[irel]];
    }
  ); 
}
```



## Variant

- Is a type of object that can hold a number of different datatypes of a value

```cpp
#include <variant>
// num can be int or double
auto num = variant<int, double>{4};

// int
cout << "num = " << get<int>(num) << endl; // print 4

// assign a double, no additional memory needed
num = 3.14159;
count << "num = " << get<doubel>(num) << endl; // print 3,14159


```

- the int and the double value share memory in `num`  => total number of memory needed for both int and double value is 8 bytes (and 4 bytes for type information).
- For the `variant<int, double, string>` type, the 3 datatypes share the same memory again, since the string pointer takes 32 bytes, and the type info takes 8 bytes, the total size is 40 bytes. => a lot of memory is unused if only `int` is used.
- When the datatype can only be idetified at run-time, we can use `hold_alternative<type>` to check the datatype.

```cpp
if(hold_alternative<double>(num)) {
	cout << "num = " << get<double>(num) << endl;
}
```

### Variant and visitor

- Define a class or struct of `visitor` that overloads the function-call `operator()` to each typr held by the variant

```cpp
struct DivideByTwo{
	void operator()(int& number){
		number >>=1;
	}
  void operator()(double& number) {
    number /=2;
  }
  void operator()(string& number) {
  	auto val = stod(number);
    number = to_string(val/2.);
  }
};

// the visit function calls the appropriate overload based on the variant's type
void divideByTwo(variant<int, double, string>& n){
  std::visit(DividedByTwo{}, n);
}
```

- no need the visitor class/struct if the same function can be applied to muliple types

```cpp
void didvidedByTwo(variant<int, double> &n){
	visit([](auto& x){x/=2;}, n);
}
```

## Run time polymorphism

- Problem: different nodes require different number of stenciels (3,5 or 1) => different `apply()` functions. 
- the original polumorphism solution with the base `Node` class and the virtual function `apply()` : need a vector of pointers to the `Node` objects ( the data is saved in heap memory and not consecutive) => not efficient and not supported in GPUs.
- The solution: `Varient` : elegant and efficient

```cpp
template<int N, typename F> 
double unrolledSum(F f){
	if constexpr(N == 0){
    return f(N);
  }
  else{
    return f(N) + unrolledSum<N -1>(f);
  }
}

template<int N> 
double stencil(
	vector<double> & u, int i, counst auto& ind, const auto& weight){
	return unrolledSum<N-1>(
  	[&u, &ind, &eight, i](auto irel){
      return weight[irel] * u[i + ind[irel]];
    }
  ); 
}

// struct of nodes
struct DirichletNode{
	double uconst{0.};
	double apply(vector<double>& u, 
  						int i, double dt){
    return uconst;
  }
};

struct O2Node{
  double a{1.};
  double apply(vector<double>& u, int i, double dt)const{
    constexpr auto ind2 = array{-1, 0, 1};
    constexpr auto weight2 = array {1.,-2, 1.};
    auto delta = stencil<3>(u, i, ind2, weight2);
    return a * delta * dt;
  }
};

struct O4Node{
  double a{1.};
  double apply(vector<double>& u, int i, double dt)const{
    constexpr auto ind4 = array{-2, -1, 0, +1, +2};
    constexpr auto weight4 = array{
      -1./12., 4./3., -5./2., 4./3., -1./12.};
    auto delta = stencil<5>(u, i, ind2, weight2);
    return a * delta * dt;
  }
};

// data initialization
using Node = variant<O2Node, O4Node, DirichletNode>;
// Vectors of values instead of pointers
auto u = vector<double>(M);
auto nodes = vector<Node>(M, O2Node{});
node[0] = node[M-1] = DirichletNode{};

auto ids = views::iota(0, M);
ranges::for_each(ids, [dx = 1./(M+1), &u](int i){
  u[i] = i * dx *2.0 * numbers::pi_v<float>;
});

// run one update cycle of the numerical scheme
ranges::for_each(ids, [dt, &u, &nodes](int i) {
  visit([i, dt, &u](auto& node){
    u[i] = node.apply(u, i, dt);
  }, nodes[i]);
});

```



