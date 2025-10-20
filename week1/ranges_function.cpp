#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

using namespace std;
int main() {
  auto v = vector<int>(20);
  iota(v.begin(), v.end(), 1);
  ranges::transform(v, v.begin(), [](int n) { return n * 7; });
  for (auto i : v) {
    cout << i << " ";
  }
  cout << endl;
  bool checked = ranges::any_of(v, [](int i) { return i % 28 == 0; });
  if (checked) {
    cout << "there is at least one multiple of 28 in v" << endl;
  }

  // Q4
  // innitialize the random number generator
  auto engine = mt19937{random_device{}()};

  // select the uniform distribution, between 0 and 99
  uniform_int_distribution<int> uniform{1, 99};

  // define the random function
  auto randint = [&uniform, &engine]() { return uniform(engine); };

  static constexpr int arr_size = 100000;

  auto a = array<int, arr_size>();
  ranges::generate(a, randint);

  // compute the mean of the array
  auto mean = static_cast<double>(reduce(a.begin(), a.end(), 0, plus<>()));
  mean /= static_cast<double>(arr_size);
  cout << "mean is " << mean << endl;

  double std_dev = transform_reduce(
    a.begin(), 
    a.end(), 
    0.0, 
    plus<>(), 
    [mean](int x) {return pow(static_cast<double>(x) - mean, 2);}
  );

  std_dev = sqrt(std_dev / static_cast<double>(arr_size));
  cout << "std dev is: " << std_dev << endl;

  // Q6A w[i]=0.5*(v[i-1] + v[i+1]), for i=1 to n-2
  auto vec = vector<double>(10);
  iota(vec.begin(), vec.end(), 1.0);
  ranges::transform(vec, vec.begin(),[](double x){return x*x;});
  auto w = vec;
  auto w_first = w.data();
  auto f = [&vec, w_first](double& it){
		auto index = distance(w_first, &it);
		it = 0.5 * (vec[index-1] + vec[index +1]);
  };
  ranges::for_each(w.begin() +1, w.end() - 1, f);
  for (auto ele: vec) {
    cout << ele << " ";
  }
  cout << endl;
  for (auto ele: w) {
    cout << ele << " ";
  }
  cout << endl;
  
}
