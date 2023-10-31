#include <iostream>


int main()
{
    {
        // three-way comparison
        auto k = 3;
        auto q = 2;

        auto cmpRes = k <=> q;
        if( cmpRes > 0)
            std::cout << "k larger q" << std::endl;
        else if( cmpRes < 0 )
            std::cout << "k smaller q" << std::endl;
        else
            std::cout << "k and q are equal" << std::endl;
    }

    return 0;
}
