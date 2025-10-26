
template<typename T>
struct SkyObject {
    int id{}; // i.e. id_antares
    float magnitude{}; // i.e. 0.96
    T distance{}; // i.e. 550 (light years)
};
int main(){
  auto s1 = SkyObject<int>{}; 
  auto s2 = SkyObject<float>{}; 
}
