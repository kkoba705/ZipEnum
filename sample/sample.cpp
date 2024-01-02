#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <array>

#ifndef __cpp_structured_bindings
#error C++17 is required for the structured_bindings feature.
#endif

#include <ZipEnum.hpp>
using zip_enum::zip, zip_enum::enumerate;

auto iota(int n) {
    std::vector<int> r(n);
    for (int i=0; i < n; i++) {
        r[i] = i;
    }
    return r;
}

int main() {

    {auto&& I = iota(10); for (auto [n, k] : enumerate(I)) {
        std::cout << n << ", " << k << std::endl;
    }}
    
    std::vector<int> A = {1, -2, 4};
    std::set<std::string> B;
    B.insert("a");
    B.insert("z");
    B.insert("b");

    std::array<double, 3> C = {1.5, 2.2, 3.14};


    for (auto [n, s, d] : zip(A, B, C)) {
        std::cout << n << ", " << s << ", " << d << std::endl;
    }    

    for (auto [i, n, s] : enumerate(A, B)) {
        std::cout << "[" << i << "] " << s << std::endl;
    }

    return 0;
}
