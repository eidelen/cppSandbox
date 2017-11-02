#include <gtest/gtest.h>
#include "matrix.hpp"

TEST(Matrix, InitializationCheckSizes)
{
    size_t nRows = 5;
    size_t nCols = 10;
    size_t nElements = nRows * nCols;

    MatrixISP m( new Matrix<int>(nRows,nCols) );

    ASSERT_EQ(m->rows(), nRows);
    ASSERT_EQ(m->cols(), nCols);
    ASSERT_EQ(m->getNbrOfElements(), nElements);
}

TEST(Matrix, SetGetSingleValue)
{
    size_t nRows = 5; size_t nCols = 10; int currentVal = 2;
    Matrix<int> mat(nRows, nCols);

    for( size_t m = 0; m < nRows; m++ )
    {
        for (size_t n = 0; n < nCols; n++)
        {
            currentVal++;
            mat.setValue(m,n,currentVal);
            ASSERT_EQ(mat.getValue(m, n), currentVal);

            currentVal++;  //operators
            mat(m,n) = currentVal;
            ASSERT_EQ(mat(m, n), currentVal);
        }
    }
}


TEST(Matrix, SetElementsToSameValue)
{
    size_t nRows = 5; size_t nCols = 10; int val = 99;

    MatrixISP mat( new Matrix<int>(nRows,nCols) );
    mat->setValue(val);

    for( size_t m = 0; m < nRows; m++ )
        for( size_t n = 0; n < nCols; n++ )
            ASSERT_EQ(mat->getValue(m, n), val);
}
