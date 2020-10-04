
#ifndef SPARSEVECTOR_NAIVEDOTPRODUCT_H
#define SPARSEVECTOR_NAIVEDOTPRODUCT_H

#include "DotProd.h"

class NaiveDotProduct: public DotProd
{
public:
    explicit NaiveDotProduct(const std::string &methodName) : DotProd(methodName)
    {}

    double compute(const SparseVector &a, const SparseVector &b) override
    {
        double dotProd = 0.0;
        for( auto [pos, val]: a )
        {
            auto corresponding = std::find_if(b.begin(), b.end(), [pos=pos](auto candidate){
                return candidate.first == pos;
            });

            if( corresponding != b.end() )
            {
                dotProd += val * corresponding->second;
            }
        }
        return dotProd;
    }
};


#endif //SPARSEVECTOR_NAIVEDOTPRODUCT_H
