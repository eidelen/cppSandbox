
#ifndef SPARSEVECTOR_DOTPROD_H
#define SPARSEVECTOR_DOTPROD_H

#include <string>
#include <utility>
#include <vector>
#include <memory>

using SparseVector = std::vector<std::pair<size_t,double>>;

/**
 * Algorithm interface to compute dot product of sparse vectors.
 */
class DotProd
{
public:

    explicit DotProd(std::string methodName): m_methodName(std::move(methodName))
    {
    }

    [[nodiscard]] const std::string& getMethodName() const
    {
        return m_methodName;
    }

    /**
     * Computes the dot product of two sparse vectors. Note: The entries of
     * the sparse vectors are not necessarily ordered!
     * @param a Sparse vector A
     * @param b Sparse vector B
     * @return Dot product
     */
    virtual double compute(const SparseVector& a, const SparseVector& b) = 0;

private:
    std::string m_methodName;
};

using DotProdSP = std::shared_ptr<DotProd>;

#endif //SPARSEVECTOR_DOTPROD_H
