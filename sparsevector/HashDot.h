
#ifndef SPARSEVECTOR_HASHDOT_H
#define SPARSEVECTOR_HASHDOT_H

#include "DotProd.h"
#include <unordered_map>

class HashDotProduct: public DotProd
{
public:
    explicit HashDotProduct(const std::string &methodName) : DotProd(methodName)
    {}

    double compute(const SparseVector &a, const SparseVector &b) override
    {
        // generate hash table from b
        std::unordered_map<size_t, double> bHash;
        for( auto [pos, val]: b)
        {
            bHash[pos] = val;
        }

        double dotProd = 0.0;
        for( auto [pos, val]: a )
        {
            auto corresponding =  bHash.find(pos);
            if( corresponding != bHash.end() )
            {
                dotProd += val * corresponding->second;
            }
        }
        return dotProd;
    }
};

#endif //SPARSEVECTOR_HASHDOT_H
