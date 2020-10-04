#include "NaiveDotProduct.h"
#include <cmath>
#include <iostream>

bool baseCheck(DotProdSP method)
{
    SparseVector a = {{5, 1.0},  {7, -1.0}, {3, 2.0}, {2, 3.0}};
    SparseVector b = {{7, -1.0}, {5, 2.0},  {3, 7.0}, {1, 3.0}};

    // 1.0 * 2.0 + -1.0 * -1.0 + 2.0 * 7.0 = 17.0
    double res = method->compute(a, b);
    return std::fabs(res - 17.0) < 1e-10;
}

int main()
{
    DotProdSP n = DotProdSP(new NaiveDotProduct("Naive Approach"));

    if( baseCheck(n) )
    {
        std::cout << n->getMethodName() << ": Base test OK" << std::endl;
    }
    else
    {
        std::cout << n->getMethodName() << ": Base test FAILED" << std::endl;
    }

    return 0;
}


