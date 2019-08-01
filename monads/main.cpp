#include "nullable.hpp"
#include <iostream>

int main()
{
    Nullable<int> i = 3;
    i
        .then([](int n) { std::cout << n << std::endl; return n; })
        .then([](int n) { n -= 1; std::cout << n << std::endl; return n; });
}
