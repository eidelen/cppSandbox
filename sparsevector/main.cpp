#include "NaiveDotProduct.h"
#include "HashDot.h"
#include "HashDotThreading.h"
#include <cmath>
#include <iostream>
#include <random>
#include <chrono>

/**
 * Basic check if method computes the correct dot product result.
 * @param method Dot product method
 * @return Dot product
 */
bool baseCheck(DotProdSP method)
{
    // simple
    SparseVector a = {{5, 1.0},  {7, -1.0}, {3, 2.0}, {2, 3.0}};
    SparseVector b = {{7, -1.0}, {5, 2.0},  {3, 7.0}, {1, 3.0}};

    // 1.0 * 2.0 + -1.0 * -1.0 + 2.0 * 7.0 = 17.0
    double res = method->compute(a, b);
    bool ok = std::fabs(res - 17.0) < 1e-10;

    // long
    SparseVector c;
    SparseVector d;
    for(size_t i = 0; i < 1000; i++)
    {
        c.push_back({i, 1.0});
        d.push_back({i, 2.0});
    }
    double res2 = method->compute(c, d);
    return ok && std::fabs(res2 - 2000.0) < 1e-10;
}

/**
 * Generates a random sparse vector.
 * @param maxLength The maximum length of the vector.
 * @param nbrOfNonZeros The number of non zero entries.
 * @return Random sparse vector.
 */
SparseVector getRandomVector(size_t maxLength, size_t nbrOfNonZeros)
{
    std::default_random_engine rndEngine;
    std::uniform_int_distribution<size_t> posDistribution(0, maxLength-1);
    std::uniform_real_distribution<double> valDistribution(-1000.0, 1000.0);
    SparseVector rndVect;

    for(size_t e = 0; e < maxLength; e++)
    {
        size_t rndPos = posDistribution(rndEngine);
        double rndVal = valDistribution(rndEngine);
        rndVect.push_back({rndPos, rndVal});
    }

    return rndVect;
}

int main()
{
    std::vector<DotProdSP> methods = {DotProdSP(new HashDotProduct("Crazy Hash Tables")),
                                      DotProdSP(new HashDotThreading("Multi Threading Hash Tables"))}; //DotProdSP(new NaiveDotProduct("Simu's Naive Approach"))};
    for( auto algo: methods )
    {
        std::cout << "####### " << algo->getMethodName() << " #######" << std::endl;

        if (baseCheck(algo))
        {
            std::cout << "Base test OK" << std::endl;
        }
        else
        {
            std::cout << "Base test FAILED" << std::endl;
        }

        // performance check
        std::vector<std::tuple<size_t, size_t, size_t>> performanceTests = {{250, 1000,  100},
                                                                            {250, 1000,  700},
                                                                            {5,   20000, 1000},
                                                                            {5,   20000, 10000},
                                                                            {5,   40000, 4000},
                                                                            {5,   40000, 10000},
                                                                            {5,   80000, 20000},
                                                                            {5,  250000, 100000}};

        for (auto[iterations, length, nonZeros]: performanceTests)
        {
            std::cout << "Random length = " << length << ", nonZeros = "
                      << nonZeros << ", iterations = " << iterations;

            long durationAccum = 0;
            for (size_t i = 0; i < iterations; i++)
            {
                auto[a, b] = std::pair(getRandomVector(length, nonZeros), getRandomVector(length, nonZeros));

                std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
                algo->compute(a, b);
                std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                durationAccum += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            }
            std::cout << " -> " << durationAccum << "[ms]" << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}


