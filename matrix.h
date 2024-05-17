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
    protected:
        size_t rows;
        size_t cols;
        std::shared_ptr<T[]> data;

    public:
        Matrix(size_t, size_t); // Constructor
        Matrix();
        Matrix(const Matrix<T> &); // Copy Constructor
        T &operator()(size_t, size_t);
        T &operator()(size_t, size_t) const; // Acquire element of matrix
        T &operator[](size_t);
        T &operator[](size_t) const;
        size_t get_row() const;
        size_t get_col() const;
        int getData_count() const;
        // Matrix-Matrix Arithmetic
        Matrix<T> operator+(const Matrix<T> &) const;
        Matrix<T> operator-(const Matrix<T> &) const;
        Matrix<T> operator*(const Matrix<T> &) const;
        Matrix<T> operator=(const Matrix<T> &); // Shallow copy
        Matrix<T> operator+=(const Matrix<T> &);
        // Matrix-Scalar Arithmetic
        Matrix<T> operator+(T) const;
        Matrix<T> operator-(T) const;
        Matrix<T> operator*(T);

        bool operator==(const Matrix<T> &) const;

        template <typename U>
        friend std::ostream &operator<<(std::ostream &, const Matrix<U> &);
        template <typename U>
        friend Matrix<U> operator+(T, const Matrix<T> &);
        bool fill(size_t, size_t, size_t, size_t, T); // Fill the designated region of the matrix with designated number
        bool fill(T);                                 // Fill the whole matrix with designated number

        inline bool is_empty(); // check if the current matrix is empty
        inline bool is_empty() const;

        /*
            ROI class, which holds a "view" of submatrix of the original matrix.
        */
        ROI<T> roi(size_t, size_t, size_t, size_t);
    };
    template <typename T>
    Matrix<T> operator-(double, const Matrix<T> &);
    template <typename T>
    Matrix<T> operator*(double, const Matrix<T> &);

    template <typename T>
    class ROI : public Matrix<T>
    {
    private:
        Matrix<T> &originalMatrix;
        size_t startRow;
        size_t endRow;
        size_t startCol;
        size_t endCol;

    public:
        ROI(Matrix<T> &, size_t, size_t, size_t, size_t); // Constructor
        T &operator()(size_t, size_t);
        T &operator()(size_t, size_t) const;
        template <typename U>
        friend std::ostream &operator<<(std::ostream &, const ROI<U> &);
        size_t get_row() const;
        size_t get_col() const;
        int getData_count() const;
        Matrix<T> operator+(const Matrix<T> &) const;
        Matrix<T> operator-(const Matrix<T> &) const;
        Matrix<T> operator*(const Matrix<T> &) const;

    private:
        T &operator[](size_t);
        T &operator[](size_t) const;
    };
}

#endif