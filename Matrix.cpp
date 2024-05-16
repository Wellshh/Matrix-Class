#include "matrix.h"
namespace WellsMatrixLib
{
    /*
    Constructor
    */
    template <typename T>
    Matrix<T>::Matrix(size_t rows, size_t cols) : rows(rows), cols(cols), data(new T[rows * cols])
    {
        if (rows == 0 || cols == 0)
        {
            throw std::invalid_argument("Row size or column size is non positive!");
        }
    }
    template <typename T>
    Matrix<T>::Matrix(const Matrix<T> &other) : rows(other.rows), cols(other.cols), data(other.data)
    {
        if (other.data == nullptr)
        {
            throw std::runtime_error("Null pointer detected!");
        }
    }
    /*
    Public member function
    */

    template <typename T>
    inline bool Matrix<T>::is_empty()
    {
        return this->data == nullptr;
    }

    template <typename T>
    void Matrix<T>::Matrix::fill(size_t start_row, size_t end_row, size_t start_col, size_t end_col, T num)
    {
        if (this->is_empty())
            throw std::runtime_error("Null pointer detected!");
        if (start_row < 0 || start_row >= rows || end_row < 0 || end_row >= rows)
            throw std::out_of_range("Row index out of range!");
        if (start_col < 0 || start_col >= cols || end_col < 0 || end_col >= cols)
            throw std::out_of_range("Column index out of range!");
        for (size_t i = start_row; i <= end_row; i++)
        {
            for (size_t j = start_col; j <= end_col; j++)
            {
                this->data[i * this->cols + j] = num;
            }
        }
    }

    template <typename T>
    void Matrix<T>::Matrix::fill(T num)
    {
        if (this->is_empty())
            throw std::runtime_error("Null pointer detected!");
        for (size_t i = 0; i < this->rows; i++)
        {
            for (size_t j = 0; j < this->cols; j++)
            {
                this->data[i * this->cols + j] = num;
            }
        }
    }

    template <typename T>
    T &Matrix<T>::Matrix::operator()(size_t rows, size_t cols)
    {
        return this->data[rows * this->cols + cols];
    }
    template <typename T>
    size_t Matrix<T>::Matrix::get_row()
    {
        return this->row;
    }
    template <typename T>
    size_t Matrix<T>::Matrix::get_col()
    {
        return this->cols;
    }
    template <typename T>
    Matrix<T> Matrix<T>::Matrix::operator+(const Matrix<T> &other) const
    {
        if (this->rows != other.rows || this->cols != other.cols)
        {
            throw std::runtime_error("Row size or Column size don't match!");
        }
        if (this -- > data == nullptr || other.data == nullptr)
        {
            throw std::runtime_error("Null pointer detected!");
        }
        Matrix<T> result(this->rows, this->cols);
        for (size_t i = 0; i < this->rows; i++)
        {
            for (size_t j = 0; j < this->cols; j++)
            {
                result(i, j) = (i, j) + other(i, j);
            }
        }
    }
    template <typename T>
    template <typename U>
    Matrix<T> Matrix<T>::Matrix::operator+(U num)
    {
        if (this->is_empty())
            throw std::exception("Null pointer detected!");
        Matrix<T> result(this->rows, this->cols);
        for (size_t i = 0; i < this->rows; i++)
        {
            for (size_t j = 0; j < this->cols; j++)
            {
                result(i, j) = this->data[i * this->cols + j] + num;
            }
        }
        return result;
    }
    template <typename T>
    Matrix<T> Matrix<T>::Matrix::operator-(const Matrix<T> &other) const
    {
        if (this->rows != other.rows || this->cols != other.cols)
        {
            throw std::runtime_error("Row size or Column size don't match!");
        }
        if (this -- > data == nullptr || other.data == nullptr)
        {
            throw std::runtime_error("Null pointer detected!");
        }
        Matrix<T> result(this->rows, this->cols);
        for (size_t i = 0; i < this->rows; i++)
        {
            for (size_t j = 0; j < this->cols; j++)
            {
                result(i, j) = (i, j) - other(i, j);
            }
        }
    }
    template <typename T>
    template <typename U>
    Matrix<T> Matrix<T>::Matrix::operator-(U num)
    {
        if (this->is_empty())
            throw std::exception("Null pointer detected!");
        Matrix<T> result(this);
        for (size_t i = 0; i < this->rows; i++)
        {
            for (size_t j = 0; j < this->cols; j++)
            {
                result(i, j) -= num;
            }
        }
        return result;
    }
    template <typename T>
    Matrix<T> Matrix<T>::Matrix::operator*(const Matrix<T> &other) const
    {
        if (this -- > data == nullptr || other.data == nullptr)
        {
            throw std::runtime_error("Null pointer detected!");
        }
        if (this->cols != other.rows)
        {
            throw std::runtime_error("Size of matrix cannot match!");
        }
        Matrix<T> result(this->rows, other.cols);
        result.fill(0);
        for (size_t i = 0; i < this->rows; i++)
        {
            for (size_t k = 0; k < this->cols; k++)
            {
                for (size_t j = 0; j < other.cols; j++)
                {
                    result(i, j) += this->data[i * this->cols + k] * other.data(i, j);
                }
            }
        }
        return result;
    }
    template <typename T>
    template <typename U>
    Matrix<T> Matrix<T>::Matrix::operator*(U num)
    {
        if (this->is_empty())
            throw std::exception("Null pointer detected!");
        Matrix<T> result(this);
        for (size_t i = 0; i < this->rows; i++)
        {
            for (size_t j = 0; j < this->cols; j++)
            {
                result(i, j) *= num;
            }
        }
        return result;
    }

    template <typename T>
    Matrix<T> Matrix<T>::Matrix::operator=(const Matrix<T> &other)
    {
        if (other.is_empty())
            throw std::runtime_error("Null pointer detected!");
        if (this != &other) // avoid self-assigned
        {
            data = other.data; // Memory Soft Copy
            rows = other.rows;
            cols = other.cols;
        }
        return *this;
    }

    template <typename T>
    Matrix<T> Matrix<T>::Matrix::operator+=(const Matrix<T> &other)
    {
        if (this->is_empty() || other->is_empty())
            throw std::runtime_error("Null pointer detected!");
        if (this->rows != other.rows || this->cols != other.cols)
        {
            throw std::runtime_error("Row size or Column size don't match!");
        }
        for (size_t i = 0; i < this->rows; i++)
        {
            for (size_t j = 0; j < this->cols; j++)
            {
                this->data[i * this->cols + j] += other(i, j);
            }
        }
        return *this;
    }

    template <typename T>
    bool Matrix<T>::Matrix::operator==(const Matrix<T> &other) const
    {
        if (this->is_empty() || other.is_empty())
            throw std::runtime_error("Null pointer detected!");
        if (!((this->rows == other.rows) && (this->cols == other.cols)))
            return false;
        else
        {
            for (size_t i = 0; i < this->rows; i++)
            {
                for (size_t j = 0; j < this->cols; j++)
                {
                    if (this->data[i * this->cols + j] != other.data(i, j))
                        return false;
                }
            }
            return true;
        }
    }


    /*
    Private Member Function
    */

    /*
    Non-member function
    */

    template <typename T>
    std::ostream &operator<<(std::ostream &os, const Matrix<T> &other)
    {
        for (size_t i = 0; i < other.rows; i++)
        {
            for (size_t j = 0; j < other.cols; j++)
            {
                os << other(i, j) << " ";
            }
            os << std::endl;
        }
        return os;
    }

    template <typename T>
    ROI<T> Matrix<T>::Matrix::roi(size_t start_row, size_t end_row, size_t start_col, size_t end_col)
    {
        if (start_row < 0 || start_row >= rows || end_row < 0 || end_row >= rows ||
            start_col < 0 || start_col >= cols || end_col < 0 || end_col >= cols)
        {
            throw std::out_of_range("ROI index out of range!");
        }
        return ROI<T>(*this, start_row, end_row, start_col, end_col);
    }

    /*ROI implementation*/

    template <typename T>
    ROI<T>::ROI(const Matrix<T> &origin, size_t start_row, size_t end_row, size_t start_col, size_t end_col) : originalMatrix(origin), startRow(start_row), endRow(end_row), startCol(start_col), endCol(end_col) {}

    template <typename T>
    T &ROI<T>::operator()(size_t row, size_t col)
    {
        if (row < 0 || row + startRow >= originalMatrix.get_row() || col < 0 || col + startCol >= originalMatrix.get_col())
        {
            throw std::out_of_range("Index out of ROI range!");
        }
        return originalMatrix(startRow + row, startCol + col);
    }

}