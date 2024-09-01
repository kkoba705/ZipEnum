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

int main() {

    std::vector<int> A = {1, 2, 3, 4, 5};
    std::vector<int> B = {2, 4, 6};

    int s = 0;
    for (auto [a, b] : zip(A, B)) {
        s += a + b;
    }

    if (s != A[0]+A[1]+A[2]+B[0]+B[1]+B[2]) return 1;
    

    int k=0;
    for (auto [i, a] : enumerate(A)) {
        if (k++ != i || a != A[i]) return 1;
        a = 1;
    }

    for (auto a : A) {
        if (a != 1) return 1;
    }

    std::cout << "ok" << std::endl;
    return 0;
}
