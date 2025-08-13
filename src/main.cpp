#include <iostream>
#include "math/mat4.hpp"

int main()
{
    math::Mat4f test = math::Mat4f::Identity();
    std::cout << test.data().m[0] << test.data().m[5] << test.data().m[10] << test.data().m[15] << std::endl;
    return 0;
}