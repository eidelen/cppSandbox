
#ifndef MY_MATRIX_H
#define MY_MATRIX_H

class Matrix
{
public:
    Matrix( unsigned int rows, unsigned int cols );
    virtual ~Matrix();

    unsigned int rows() const;
    unsigned int cols() const;

protected:
    const unsigned int m_rows;
    const unsigned int m_cols;
};

#endif //MY_MATRIX_H