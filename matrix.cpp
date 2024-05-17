#include "matrix.h"
namespace WellsMatrixLib
{
    /*
    Constructor
    */
    template <typename T>
    Matrix<T>::Matrix() {}
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
    inline bool Matrix<T>::is_empty() const
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
        {
            fprintf(stderr, "File %s, Line %d, Function %s(): Column index out of range.\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }
        size_t length = (end_row - start_row + 1) * (end_col - start_col + 1);
        auto start_pos = data.get() + (start_row * cols) + start_col;
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
    T &Matrix<T>::operator[](size_t index)
    {
        if (this->is_empty())
        {
            fprintf(stderr, "File %s, Line %d, Function %s(): Null Pointer Detected.\n", __FILE__, __LINE__, __FUNCTION__);
            throw std::runtime_error("Null pointer detected");
        }
        size_t length = this->rows * this->cols;
        if (index >= length)
        {
            throw std::out_of_range("Index out of ROI range!");
        }
        // index = r * cols + c
        size_t c = index % this->cols;
        size_t r = index / this->cols;
        return (*this)(r, c);
    }

    template <typename T>
    T &Matrix<T>::operator[](size_t index) const
    {
        if (this->is_empty())
        {
            fprintf(stderr, "File %s, Line %d, Function %s(): Null Pointer Detected.\n", __FILE__, __LINE__, __FUNCTION__);
            throw std::runtime_error("Null pointer detected");
        }
        size_t length = this->rows * this->cols;
        if (index >= length)
        {
            throw std::out_of_range("Index out of ROI range!");
        }
        // index = r * cols + c
        size_t c = index % this->cols;
        size_t r = index / this->cols;
        return (*this)(r, c);
    }

    template <typename T>
    size_t Matrix<T>::Matrix::get_row() const
    {
        if (this->data == nullptr)
        {
            fprintf(stderr, "File %s, Line %d, Function %s(): Null Pointer Detected.\n", __FILE__, __LINE__, __FUNCTION__);
            std::abort();
        }
        return this->rows;
    }
    template <typename T>
    size_t Matrix<T>::Matrix::get_col() const
    {
        if (this->data == nullptr)
        {
            fprintf(stderr, "File %s, Line %d, Function %s(): Null Pointer Detected.\n", __FILE__, __LINE__, __FUNCTION__);
            std::abort();
        }
        return this->cols;
    }
    template <typename T>
    int Matrix<T>::Matrix::getData_count() const
    { // only count can be accessed, data is forbidden to be accessed directly since it's a shared pointer.
        if (this->data == nullptr)
        {
            fprintf(stderr, "File %s, Line %d, Function %s(): Null Pointer Detected.\n", __FILE__, __LINE__, __FUNCTION__);
            std::abort();
        }
        return this->data.use_count();
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
    Matrix<T> Matrix<T>::Matrix::operator+(T num) const
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
            result.data[i] = this->data[i] - other.data[i];
        }

        return result;
    }
    template <typename T>
    Matrix<T> Matrix<T>::Matrix::operator-(T num) const
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
            result.data[i] = this->data[i] - num;
        }

        return result;
    }
    template <typename T>
    Matrix<T> Matrix<T>::Matrix::operator*(const Matrix<T> &other) const
    {
        if (this->is_empty() || other.data == nullptr)
        {
            throw std::runtime_error("Null pointer detected!");
        }
        if (this->cols != other.rows)
        {
            throw std::runtime_error("Multiplication Size of matrix cannot match!");
        }
        Matrix<T> result(this->rows, other.cols);
        if (result.data == nullptr)
        {
            fprintf(stderr, "File %s, Line %d, Function %s(): Null Pointer Detected.\n", __FILE__, __LINE__, __FUNCTION__);
            throw std::runtime_error("Null pointer detected");
        }
        result.fill(0);
        for (size_t i = 0; i < this->rows; i++)
        {
            for (size_t k = 0; k < this->cols; k++)
            {
                for (size_t j = 0; j < other.cols; j++)
                {
                    result(i, j) += this->data[i * this->cols + k] * other(k, j);
                }
            }
        }
        return result;
    }
    template <typename T>
    Matrix<T> Matrix<T>::Matrix::operator*(T num)
    {
        if (this->is_empty())
        {
            fprintf(stderr, "File %s, Line %d, Function %s(): Null Pointer Detected.\n", __FILE__, __LINE__, __FUNCTION__);
            throw std::runtime_error("Null pointer detected");
        }
        Matrix<T> result(this->rows, this->cols);
        size_t length = this->cols * this->rows;

        for (size_t i = 0; i < length; ++i)
        {
            result.data[i] = this->data[i] * num;
        }
        return result;
    }

    template <typename T>
    Matrix<T> Matrix<T>::Matrix::operator=(const Matrix<T> &other)
    {
        if (!this->data || !other.data)
        {
            fprintf(stderr, "File %s, Line %d, Function %s(): Null Pointer Detected.\n", __FILE__, __LINE__, __FUNCTION__);
            throw std::runtime_error("Null pointer detected");
        }
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
        size_t length = this->cols * this->rows;

        for (size_t i = 0; i < length; ++i)
        {
            this->data[i] += other.data[i];
        }
        return *this;
    }

    template <typename T>
    bool Matrix<T>::Matrix::operator==(const Matrix<T> &other) const
    {
        if (!this->data || !other.data)
        {
            fprintf(stderr, "File %s, Line %d, Function %s(): Null Pointer Detected.\n", __FILE__, __LINE__, __FUNCTION__);
            throw std::runtime_error("Null pointer detected");
        }
        if (!((this->rows == other.rows) && (this->cols == other.cols)))
            return false;
        else
        {
            size_t length = this->cols * this->rows;

            for (size_t i = 0; i < length; ++i)
            {
                if (this->data[i] != other.data[i])
                {
                    return false;
                }
            }
            return true;
        }
    }

    /*
    Private Member Function
    */

    template <typename T>
    T &ROI<T>::operator[](size_t index)
    {
        if (this->originalMatrix.is_empty())
        {
            fprintf(stderr, "File %s, Line %d, Function %s(): Null Pointer Detected.\n", __FILE__, __LINE__, __FUNCTION__);
            throw std::runtime_error("Null pointer detected");
        }
        size_t length = this->rows * this->cols;
        if (index >= length)
        {
            throw std::out_of_range("Index out of ROI range!");
        }
        // index = r * cols + c
        size_t c = index % this->cols;
        size_t r = index / this->cols;
        return (*this)(r, c);
    }
    template <typename T>
    T &ROI<T>::operator[](size_t index) const
    {
        if (this->originalMatrix.is_empty())
        {
            fprintf(stderr, "File %s, Line %d, Function %s(): Null Pointer Detected.\n", __FILE__, __LINE__, __FUNCTION__);
            throw std::runtime_error("Null pointer detected");
        }
        size_t length = this->rows * this->cols;
        if (index >= length)
        {
            throw std::out_of_range("Index out of ROI range!");
        }
        // index = r * cols + c
        size_t c = index % this->cols;
        size_t r = index / this->cols;
        return (*this)(r, c);
    }
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
    Matrix<T> operator+(T num, const Matrix<T> &other)
    {
        return other + num;
    }

    template <typename T>
    ROI<T> Matrix<T>::Matrix::roi(size_t start_row, size_t end_row, size_t start_col, size_t end_col)
    {
        if (start_row >= rows || end_row >= rows ||
            start_col >= cols || end_col >= cols)
        {
            throw std::out_of_range("ROI index out of range!");
        }
        return ROI<T>(*this, start_row, end_row, start_col, end_col);
    }

    /*ROI implementation*/

    template <typename T>
    ROI<T>::ROI(Matrix<T> &origin, size_t start_row, size_t end_row, size_t start_col, size_t end_col) : originalMatrix(origin), startRow(start_row), endRow(end_row), startCol(start_col), endCol(end_col)
    {
        this->rows = end_row - start_row + 1;
        this->cols = end_col - start_col + 1;
    }

    template <typename T>
    T &ROI<T>::operator()(size_t row, size_t col)
    {
        if (row < 0 || row + startRow >= originalMatrix.get_row() || col < 0 || col + startCol >= originalMatrix.get_col())
        {
            throw std::out_of_range("Index out of ROI range!");
        }
        return originalMatrix(startRow + row, startCol + col);
    }
    template <typename T>
    T &ROI<T>::operator()(size_t row, size_t col) const
    {
        if (row < 0 || row + startRow >= originalMatrix.get_row() || col < 0 || col + startCol >= originalMatrix.get_col())
        {
            throw std::out_of_range("Index out of ROI range!");
        }
        return originalMatrix(startRow + row, startCol + col);
    }
    template <typename T>
    std::ostream &operator<<(std::ostream &os, const ROI<T> &other)
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
    size_t ROI<T>::ROI::get_row() const
    {
        if (this->originalMatrix.is_empty())
        {
            fprintf(stderr, "File %s, Line %d, Function %s(): Null Pointer Detected.\n", __FILE__, __LINE__, __FUNCTION__);
            std::abort();
        }
        return this->rows;
    }
    template <typename T>
    size_t ROI<T>::ROI::get_col() const
    {
        if (this->originalMatrix.is_empty())
        {
            fprintf(stderr, "File %s, Line %d, Function %s(): Null Pointer Detected.\n", __FILE__, __LINE__, __FUNCTION__);
            std::abort();
        }
        return this->cols;
    }
    template <typename T>
    int ROI<T>::ROI::getData_count() const
    { // only count can be accessed, data is forbidden to be accessed directly since it's a shared pointer.
        if (this->originalMatrix.is_empty())
        {
            fprintf(stderr, "File %s, Line %d, Function %s(): Null Pointer Detected.\n", __FILE__, __LINE__, __FUNCTION__);
            std::abort();
        }
        return this->originalMatrix.getData_count();
    }
    template <typename T>
    Matrix<T> ROI<T>::ROI::operator+(const Matrix<T> &other) const
    {
        if (this->rows != other.get_row() || this->cols != other.get_col())
        {
            fprintf(stderr, "File %s, Line %d, Function %s(): Matrix size can't match. (%zu,%zu) and (%zu,%zu).\n", __FILE__, __LINE__, __FUNCTION__, this->rows, this->cols, other.get_row(), other.get_col());
            throw std::invalid_argument("Matrix size mismatch");
        }
        if (this->originalMatrix.is_empty() || other.is_empty())
        {
            fprintf(stderr, "File %s, Line %d, Function %s(): Null Pointer Detected.\n", __FILE__, __LINE__, __FUNCTION__);
            throw std::runtime_error("Null pointer detected");
        }
        Matrix<T> result(this->rows, this->cols);
        if (result.is_empty())
        {
            fprintf(stderr, "File %s, Line %d, Function %s(): Null Pointer Detected.\n", __FILE__, __LINE__, __FUNCTION__);
            throw std::runtime_error("Null pointer detected");
        }
        size_t length = this->cols * this->rows;

        for (size_t i = 0; i < length; ++i)
        {

            result[i] = (*this)[i] + other[i];
        }

        return result;
    }

    template <typename T>
    Matrix<T> ROI<T>::ROI::operator-(const Matrix<T> &other) const
    {
        if (this->rows != other.get_row() || this->cols != other.get_col())
        {
            fprintf(stderr, "File %s, Line %d, Function %s(): Matrix size can't match. (%zu,%zu) and (%zu,%zu).\n", __FILE__, __LINE__, __FUNCTION__, this->rows, this->cols, other.get_row(), other.get_col());
            throw std::invalid_argument("Matrix size mismatch");
        }
        if (this->originalMatrix.is_empty() || other.is_empty())
        {
            fprintf(stderr, "File %s, Line %d, Function %s(): Null Pointer Detected.\n", __FILE__, __LINE__, __FUNCTION__);
            throw std::runtime_error("Null pointer detected");
        }
        Matrix<T> result(this->rows, this->cols);
        if (result.is_empty())
        {
            fprintf(stderr, "File %s, Line %d, Function %s(): Null Pointer Detected.\n", __FILE__, __LINE__, __FUNCTION__);
            throw std::runtime_error("Null pointer detected");
        }
        size_t length = this->cols * this->rows;

        for (size_t i = 0; i < length; ++i)
        {

            result[i] = (*this)[i] - other[i];
        }

        return result;
    }

    template <typename T>
    Matrix<T> ROI<T>::ROI::operator*(const Matrix<T> &other) const
    {
        if (this->cols != other.get_row())
        {
            fprintf(stderr, "File %s, Line %d, Function %s(): Matrix size can't match. (%zu,%zu) and (%zu,%zu).\n", __FILE__, __LINE__, __FUNCTION__, this->rows, this->cols, other.get_row(), other.get_col());
            throw std::invalid_argument("Matrix size mismatch");
        }
        if (this->originalMatrix.is_empty() || other.is_empty())
        {
            fprintf(stderr, "File %s, Line %d, Function %s(): Null Pointer Detected.\n", __FILE__, __LINE__, __FUNCTION__);
            throw std::runtime_error("Null pointer detected");
        }
        Matrix<T> result(this->rows, this->cols);
        if (result.is_empty())
        {
            fprintf(stderr, "File %s, Line %d, Function %s(): Null Pointer Detected.\n", __FILE__, __LINE__, __FUNCTION__);
            throw std::runtime_error("Null pointer detected");
        }
        result.fill(0);
        for (size_t i = 0; i < this->rows; i++)
        {
            for (size_t k = 0; k < this->cols; k++)
            {
                for (size_t j = 0; j < other.get_col(); j++)
                {
                    result(i, j) += (*this)(i, k) * other(k, j);
                }
            }
        }
        return result;
    }
}