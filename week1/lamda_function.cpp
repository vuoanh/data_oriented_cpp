#include <numeric>
#include <vector>
#include <iostream>

using namespace std;

int main(){
  static constexpr auto v=array<int,5>{1,2,3,4,5};
  auto s = reduce(v.begin(), v.end()-1);
  cout << "sun :" << s <<endl;

  auto f = [](int x){ return x%2 == 0 ? 1 : -1; };
  auto w = array<int,5>();
  transform(v.begin(), v.end(), w.begin(), f); 
  cout << "new w: " ;
  for (auto i: w) {cout << i << " " ;}
  cout << endl;
}
