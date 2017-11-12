#include <gtest/gtest.h>
#include "matrix.hpp"

TEST(MatMul, Scalar)
{
    size_t s = 5;
    auto mat = Matrix<int>(s,s);
    mat.setValue(3);

    auto res1 = mat * 2; // res should be 2*3 = 6

    auto soll1 = Matrix<int>(s,s);
    soll1.setValue(6);

    ASSERT_TRUE(res1.compare(soll1));

    auto res2 = 2 * mat; // res should be 2*3 = 6
    ASSERT_TRUE(res2.compare(soll1));
}




