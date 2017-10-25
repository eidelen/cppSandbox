#include <gtest/gtest.h>
#include "matrix.h"

TEST(Matrix, InitializationCheckSize)
{
    unsigned int nRows = 5;
    unsigned int nCols = 10;

    Matrix* m = new Matrix(nRows,nCols);

    ASSERT_EQ(m->rows(), nRows);
    ASSERT_EQ(m->cols(), nCols);

    delete m;
}
