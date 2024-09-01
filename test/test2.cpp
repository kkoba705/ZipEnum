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
    std::vector<int> const &B = A;
    int C[] = {3, 4, 5, 6};

    int s = 0;
    for (auto [a, b, c] : zip(A, B, C)) {
        s += a + b + c;
    }

    if (s != 2*(A[0]+A[1]+A[2]+A[3]) + C[0]+C[1]+C[2]+C[3]) return 1;
    

    int k=0;

    for (auto [i, a, c] : enumerate(A, C)) {
        if (k++ != i || a != A[i] || c != C[i]) return 1;
    }

    if (k != 4) return 1;

    std::cout << "ok" << std::endl;
    return 0;
}
