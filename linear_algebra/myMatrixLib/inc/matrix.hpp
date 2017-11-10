
#ifndef MY_MATRIX_H
#define MY_MATRIX_H

#include <memory>
#include <iostream>

template <class T>
class Matrix
{
public:
    Matrix( size_t rows, size_t cols );
    virtual ~Matrix();

    size_t rows() const;
    size_t cols() const;
    size_t getNbrOfElements() const;

    /**
     * Sets each element to the value val.
     * @param val Value
     */
    void setValue( T val );

    /**
     * Set the value at position m, n.
     * @param m Row
     * @param n Column
     * @param val Value
     */
    void setValue( size_t m, size_t n, T val);

    /**
     * Gets the value at position m, n.
     * @param m Row
     * @param n Column
     * @return Value
     */
    T getValue( size_t m, size_t n ) const;

    /**
     * Gets the value at position m, n.
     * @param m
     * @param n
     * @return
     */
    const T operator() (size_t m, size_t n) const;
    T& operator() (size_t m, size_t n);

    /**
     * Creates a m x m identity matrix
     * @param m Matrix size.
     * @return Identity matrix.
     */
    static Matrix<T> eye(size_t m);

protected:
    const size_t m_rows;
    const size_t m_cols;

    T* m_data;
    const size_t m_nbrOfElements;
};


template <class T>
Matrix<T>::Matrix(size_t rows, size_t cols)
        : m_rows(rows), m_cols(cols), m_nbrOfElements(rows*cols)
{
    m_data = new T[ m_nbrOfElements ];
}

template <class T>
Matrix<T>::~Matrix()
{
    delete[] m_data;
}

template <class T>
size_t Matrix<T>::rows() const
{
    return m_rows;
}

template <class T>
size_t Matrix<T>::cols() const
{
    return m_cols;
}

template <class T>
size_t Matrix<T>::getNbrOfElements() const
{
    return m_nbrOfElements;
}

template <class T>
void Matrix<T>::setValue( T val )
{
    for( size_t i = 0; i < m_nbrOfElements; i++ )
        m_data[i] = val;
}

template <class T>
void Matrix<T>::setValue( size_t m, size_t n, T val)
{
    m_data[m*cols() + n] = val;
}

template <class T>
T Matrix<T>::getValue( size_t m, size_t n ) const
{
    return m_data[m*cols() + n];
}

template <class T>
const T Matrix<T>::operator() (size_t m, size_t n) const
{
    return m_data[m*cols() + n];
}

template <class T>
T& Matrix<T>::operator() (size_t m, size_t n)
{
    return m_data[m*cols() + n];
}

template <class T>
Matrix<T> Matrix<T>::eye(size_t m)
{
    Matrix<T> ident = Matrix<T>(m,m);
    ident.setValue(0);
    for(size_t i = 0; i < m; i++)
    {
        ident(i,i) = 1;
    }

    return ident;
}




template <class T>
std::ostream& operator<<(std::ostream& os, Matrix<T> const& mat)
{
    for( size_t m = 0; m < mat.rows(); m++ )
    {
        for( size_t n = 0; n < mat.cols(); n++ )
        {
            os << mat(m,n);
            if( n+1 < mat.cols() )
                os << ", ";
        }

        os << std::endl;
    }
}

// Predefined Matrix Types
typedef std::shared_ptr<Matrix<int>> MatrixISP;
typedef std::shared_ptr<Matrix<double>> MatrixDSP;

#endif //MY_MATRIX_H