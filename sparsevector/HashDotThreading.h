
#ifndef SPARSEVECTOR_HASHDOTTHREADING_H
#define SPARSEVECTOR_HASHDOTTHREADING_H

#include "DotProd.h"
#include <unordered_map>
#include <thread>
#include <numeric>
#include <iostream>
#include <functional>

class HashDotThreading: public DotProd
{
public:
    explicit HashDotThreading(const std::string &methodName) : DotProd(methodName)
    {}

    double compute(const SparseVector &a, const SparseVector &b) override
    {
        // generate hash table from b
        std::unordered_map<size_t, double> bHash;
        for( auto [pos, val]: b)
        {
            bHash[pos] = val;
        }

        size_t nThreads = 20;
        size_t batchSize = a.size() / nThreads;

        std::vector<double> partialResults(nThreads, 0.0);
        std::vector<std::thread> workers;
        const SparseVector& a_const = a;
        for(size_t tidx = 0; tidx < nThreads; tidx++)
        {
            size_t startIdx = tidx * batchSize;
            size_t endIdx = (tidx + 1 < nThreads) ? startIdx + batchSize: a.size();
            workers.push_back(std::thread([startIdx, endIdx, &a_const, &bHash, &partialResults, tidx]() mutable{
                double partialDot = 0.0;
                for (size_t q = startIdx; q < endIdx; q++)
                {
                    auto[pos, val] = a_const[q];
                    auto corresponding = bHash.find(pos);
                    if (corresponding != bHash.end())
                    {
                        partialDot += val * corresponding->second;
                    }
                }
                partialResults[tidx] = partialDot;
              }));
        }

        std::for_each(workers.begin(), workers.end(), [](std::thread &t)
        {
            t.join();
        });

        return std::accumulate(partialResults.begin(), partialResults.end(), 0.0);
    }
};

#endif //SPARSEVECTOR_HASHDOTTHREADING_H
