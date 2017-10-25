
#include "matrix.h"

Matrix::Matrix(unsigned int rows, unsigned int cols)
        : m_rows(rows), m_cols(cols)
{

}

Matrix::~Matrix()
{

}

unsigned int Matrix::rows() const
{
    return m_rows;
}

unsigned int Matrix::cols() const
{
    return m_cols;
}
