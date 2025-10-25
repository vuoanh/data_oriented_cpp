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



