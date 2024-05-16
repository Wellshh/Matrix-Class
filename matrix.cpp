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
            fprintf(stderr, "File %s, Line %d, Function %s(): Row size of Column size is zero.\n", __FILE__, __LINE__, __FUNCTION__);
        }
        if (data == nullptr)
        {
            fprintf(stderr, "File %s, Line %d, Function %s(): Memory allocation failed.\n", __FILE__, __LINE__, __FUNCTION__);
        }
    }
    template <typename T>
    Matrix<T>::Matrix(const Matrix<T> &other) : rows(other.rows), cols(other.cols), data(other.data)
    {
        if (other.data == nullptr || data == nullptr)
        {
            fprintf(stderr, "File %s, Line %d, Function %s(): Memory allocation failed.\n", __FILE__, __LINE__, __FUNCTION__);
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
    bool Matrix<T>::Matrix::fill(size_t start_row, size_t end_row, size_t start_col, size_t end_col, T num)
    {
        if (this->is_empty())
        {
            fprintf(stderr, "File %s, Line %d, Function %s(): Null Pointer Detected.\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
        if (start_row >= rows || end_row >= rows)
        {
            fprintf(stderr, "File %s, Line %d, Function %s(): Row index out of range.\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
        else if (start_col >= cols || end_col >= cols)
            fprintf(stderr, "File %s, Line %d, Function %s(): Column index out of range.\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
        size_t length = (end_row - start_row + 1) * (end_col - start_col + 1);
        auto start_pos = data + (start_row * cols) + start_col;
        std::fill(start_pos, start_pos + length, num);
        return true;
    }

    template <typename T>
    bool Matrix<T>::Matrix::fill(T num)
    {
        if (this->is_empty())
        {
            fprintf(stderr, "File %s, Line %d, Function %s(): Null Pointer Detected.\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
        size_t length = (this->rows * this->cols);
        std::fill(data.get(), data.get() + length, num);
        return true;
    }

    template <typename T>
    T &Matrix<T>::Matrix::operator()(size_t rows, size_t cols)
    {
        if (rows >= this->rows || cols >= this->cols)
        {
            std::out_of_range("Matrix index out of range.\n");
        }
        else if (this->data == nullptr)
        {
            fprintf(stderr, "File %s, Line %d, Function %s(): Null Pointer Detected.\n", __FILE__, __LINE__, __FUNCTION__);
            std::abort();
        }
        return this->data[rows * this->cols + cols];
    }
    template <typename T>
    T &Matrix<T>::Matrix::operator()(size_t rows, size_t cols) const
    {
        if (rows >= this->rows || cols >= this->cols)
        {
            std::out_of_range("Matrix index out of range.\n");
        }
        else if (this->data == nullptr)
        {
            fprintf(stderr, "File %s, Line %d, Function %s(): Null Pointer Detected.\n", __FILE__, __LINE__, __FUNCTION__);
            std::abort();
        }

        return this->data[rows * this->cols + cols];
    }
    template <typename T>
    size_t Matrix<T>::Matrix::get_row()
    {
        if (this->data == nullptr)
        {
            fprintf(stderr, "File %s, Line %d, Function %s(): Null Pointer Detected.\n", __FILE__, __LINE__, __FUNCTION__);
            std::abort();
        }
        return this->rows;
    }
    template <typename T>
    size_t Matrix<T>::Matrix::get_col()
    {
        if (this->data == nullptr)
        {
            fprintf(stderr, "File %s, Line %d, Function %s(): Null Pointer Detected.\n", __FILE__, __LINE__, __FUNCTION__);
            std::abort();
        }
        return this->cols;
    }
    template <typename T>
    Matrix<T> Matrix<T>::operator+(const Matrix<T> &other) const
    {
        if (this->rows != other.rows || this->cols != other.cols)
        {
            fprintf(stderr, "File %s, Line %d, Function %s(): Matrix size can't match. (%zu,%zu) and (%zu,%zu).\n", __FILE__, __LINE__, __FUNCTION__, this->rows, this->cols, other.rows, other.cols);
            throw std::invalid_argument("Matrix size mismatch");
        }
        if (!this->data || !other.data)
        {
            fprintf(stderr, "File %s, Line %d, Function %s(): Null Pointer Detected.\n", __FILE__, __LINE__, __FUNCTION__);
            throw std::runtime_error("Null pointer detected");
        }
        Matrix<T> result(this->rows, this->cols);
        if (result.data == nullptr)
        {
            fprintf(stderr, "File %s, Line %d, Function %s(): Null Pointer Detected.\n", __FILE__, __LINE__, __FUNCTION__);
            throw std::runtime_error("Null pointer detected");
        }
        size_t length = this->cols * this->rows;

        for (size_t i = 0; i < length; ++i)
        {
            result.data[i] = this->data[i] + other.data[i];
        }

        return result;
    }
    template <typename T>
    Matrix<T> Matrix<T>::Matrix::operator+(T num)
    {
        if (this->is_empty())
        {
            fprintf(stderr, "File %s, Line %d, Function %s(): Null Pointer Detected.\n", __FILE__, __LINE__, __FUNCTION__);
            throw std::runtime_error("Null pointer detected");
        }
        Matrix<T> result(this->rows, this->cols);
        if (result.data == nullptr)
        {
            fprintf(stderr, "File %s, Line %d, Function %s(): Null Pointer Detected.\n", __FILE__, __LINE__, __FUNCTION__);
            throw std::runtime_error("Null pointer detected");
        }
        size_t length = this->cols * this->rows;

        for (size_t i = 0; i < length; ++i)
        {
            result.data[i] = this->data[i] + num;
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