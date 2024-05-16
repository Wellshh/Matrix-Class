#ifndef MATRIX_H
#define MATRIX_H
#include <stdio.h>
#include <memory>
#include <stdexcept>
#include <iostream>
// #include </home/wells/OpenBLAS/OpenBLAS/cblas.h>
namespace WellsMatrixLib
{
    template <typename T>
    class ROI;
    template <typename T>
    class Matrix
    {
    private:
        size_t rows;
        size_t cols;
        std::shared_ptr<T> data;

    public:
        Matrix(size_t, size_t);        // Constructor
        Matrix(const Matrix<T> &);     // Copy Constructor
        T &operator()(size_t, size_t); // Acquire element of matrix
        size_t get_row();
        size_t get_col();
        // Matrix-Matrix Arithmetic
        Matrix<T> operator+(const Matrix<T> &) const;
        Matrix<T> operator-(const Matrix<T> &) const;
        Matrix<T> operator*(const Matrix<T> &) const;
        Matrix<T> operator=(const Matrix<T> &); // Shallow copy
        Matrix<T> operator+=(const Matrix<T> &);
        // Matrix-Scalar Arithmetic
        template <typename U>
        Matrix<T> operator+(U);
        template <typename U>
        Matrix<T> operator-(U);
        template <typename U>
        Matrix<T> operator*(U);

        bool operator==(const Matrix<T> &) const;

        template <typename U>
        friend std::ostream &operator<<(std::ostream &, const Matrix<U> &);

        void fill(size_t, size_t, size_t, size_t, T); // Fill the designated region of the matrix with designated number
        void fill(T);                                 // Fill the whole matrix with designated number

        inline bool is_empty(); // check if the current matrix is empty

        /*
            ROI class, which holds a "view" of submatrix of the original matrix.
        */
        ROI<T> roi(size_t, size_t, size_t, size_t);
    };
    template <typename T>
    Matrix<T> operator+(double, const Matrix<T> &);
    template <typename T>
    Matrix<T> operator-(double, const Matrix<T> &);
    template <typename T>
    Matrix<T> operator*(double, const Matrix<T> &);

    template <typename T>
    class ROI
    {
    private:
        Matrix<T> &originalMatrix;
        size_t startRow;
        size_t endRow;
        size_t startCol;
        size_t endCol;

    public:
        ROI(const Matrix<T> &, size_t, size_t, size_t, size_t); // Constructor
        T &operator()(size_t, size_t);
    };
}

#endif