#include "inheritance.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <algorithm>

void doInheritanceTest()
{
    unsigned int n = 200000000;

    std::vector<Person*> pV;
    std::vector<Child*> cV;

    for( unsigned int i = 0; i < n; i++ )
    {
        Child* nC = new Child();

        pV.push_back(nC);
        cV.push_back(nC);
    }

    clock_t start, finish;


    start = clock();
    for( int i = 0; i < pV.size(); i++ )
        pV.at(i)->isAllowedToDrive();
    finish = clock();

    std::cout << "Time for calling inherited function (seconds): " << ((double)(finish - start))/CLOCKS_PER_SEC << std::endl;

    start = clock();
    for( int i = 0; i < cV.size(); i++ )
        cV.at(i)->isAllowedToDrive();
    finish = clock();

    std::cout << "Time for calling direct function (seconds): " << ((double)(finish - start))/CLOCKS_PER_SEC << std::endl;

    return;
}
