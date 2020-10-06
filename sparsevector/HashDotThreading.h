
#ifndef SPARSEVECTOR_HASHDOTTHREADING_H
#define SPARSEVECTOR_HASHDOTTHREADING_H

#include "DotProd.h"
#include <unordered_map>
#include <thread>
#include <numeric>
#include <iostream>
#include <functional>
#include <future>


class HashDotThreading: public DotProd
{
public:
    explicit HashDotThreading(const std::string &methodName) : DotProd(methodName)
    {}

    static double computeSection(const SparseVector &a, size_t startIdx, size_t endIdx, const std::unordered_map<size_t, double>& bHash)
    {
        double partialDot = 0.0;
        for (size_t q = startIdx; q < endIdx; q++)
        {
            auto[pos, val] = a[q];
            auto corresponding = bHash.find(pos);
            if (corresponding != bHash.end())
            {
                partialDot += val * corresponding->second;
            }
        }
        return partialDot;
    }

    double compute(const SparseVector &a, const SparseVector &b) override
    {
        // generate hash table from b
        std::unordered_map<size_t, double> bHash;
        for( auto [pos, val]: b)
        {
            bHash[pos] = val;
        }

        size_t nThreads = 2;
        size_t batchSize = a.size() / nThreads;

        std::vector<double> partialResults(nThreads, 0.0);
        std::vector<std::future<double>> workers;
        const SparseVector& a_const = a;

        for(size_t tidx = 0; tidx < nThreads; tidx++)
        {
            size_t startIdx = tidx * batchSize;
            size_t endIdx = (tidx + 1 < nThreads) ? startIdx + batchSize: a.size();

            workers.push_back(std::async(std::launch::async, &HashDotThreading::computeSection, std::cref(a_const), startIdx, endIdx, std::cref(bHash) ));
        }

        return std::accumulate(workers.begin(), workers.end(), 0.0, [](double result, std::future<double>& f ){
            return result + f.get();
        });
    }
};

#endif //SPARSEVECTOR_HASHDOTTHREADING_H
