#include <iostream>
#include <memory>
#include <vector>
#include <array>

using namespace std;

void func(array<unique_ptr<int>, 10> &ar_ptr){
	ranges::for_each(ar_ptr, [](unique_ptr<int> &i_p){*i_p += 1;}); 
}
int main() {
  // Q3
  auto x = int{42};
  auto p = make_shared<int>(x);
  x = 43;
  cout << *p << endl;

  //Q4
  auto u_p = make_unique<vector<int>>(vector<int>{3,4,5,6});
  cout << "size of the vector: " << u_p->size() << endl;
  u_p->push_back(5);
  ranges::for_each(*u_p, [](int i){cout << i<< " ";});
  cout << endl;

  //Q5
  auto arr_p = array<unique_ptr<int>, 10>();
  ranges::for_each(arr_p, [](unique_ptr<int> &i_p){ i_p = make_unique<int>(int{1});});
  func(arr_p);
  ranges::for_each(arr_p, [](unique_ptr<int> &i_p){cout << *i_p << " ";});
  cout << endl;

  // Q6
  auto vec_p = vector<unique_ptr<array<int, 2>>>(5);
  ranges::for_each(vec_p, [](auto &ptr_arr){ ptr_arr = make_unique<array<int,2>>(array{1,2});});
  auto q = vector<unique_ptr<array<int, 2>>>(5);
  ranges::transform(vec_p.begin(), vec_p.end(), q.begin(), [](auto &ptr_arr){ return make_unique<array<int,2>>(*ptr_arr);});
  ranges::for_each(q, [](auto &i_p){cout << "[" << (*i_p)[0] << "," << (*i_p)[1] << "] ";});
  cout << endl;
  
}

