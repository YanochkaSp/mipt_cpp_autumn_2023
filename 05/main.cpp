#include <iostream>
#include <cstdint>
#include <stdexcept>
#include <assert.h>

class Matrix
{
private:
    size_t rows_;
    size_t columns_;
    int32_t **data_;

public:
    class ProxyRow
    {
    private:
        int32_t *data_;
        size_t columns_;

    public:
        ProxyRow(int32_t *data, size_t columns)
            : data_(data), columns_(columns)
        {
        }

        int32_t &operator[](size_t j)
        {
            if (j >= columns_)
            {
                throw std::out_of_range("");
            }
            return data_[j];
        }
    };

    Matrix(size_t rows, size_t columns)
        : rows_(rows), columns_(columns)
    {
        data_ = new int32_t *[rows_];
        for (size_t i = 0; i < rows_; ++i)
        {
            data_[i] = new int32_t[columns_];
        }
    }

    ~Matrix()
    {
        for (size_t i = 0; i < rows_; ++i)
        {
            delete[] data_[i];
        }
        delete[] data_;
    }

    size_t getRows() const
    {
        return rows_;
    }

    size_t getColumns() const
    {
        return columns_;
    }

    ProxyRow operator[](size_t i)
    {
        if (i >= rows_)
        {
            throw std::out_of_range("");
        }
        return ProxyRow(data_[i], columns_);
    }

    Matrix &operator*=(int32_t scalar)
    {
        for (size_t i = 0; i < rows_; ++i)
        {
            for (size_t j = 0; j < columns_; ++j)
            {
                data_[i][j] *= scalar;
            }
        }
        return *this;
    }

    Matrix operator+(const Matrix &other) const
    {
        if (rows_ != other.rows_ || columns_ != other.columns_)
        {
            throw std::out_of_range("");
        }

        Matrix result(rows_, columns_);

        for (size_t i = 0; i < rows_; ++i)
        {
            for (size_t j = 0; j < columns_; ++j)
            {
                result.data_[i][j] = data_[i][j] + other.data_[i][j];
            }
        }

        return result;
    }

    bool operator==(const Matrix &other) const
    {
        if (rows_ != other.rows_ || columns_ != other.columns_)
        {
            return false;
        }

        for (size_t i = 0; i < rows_; ++i)
        {
            for (size_t j = 0; j < columns_; ++j)
            {
                if (data_[i][j] != other.data_[i][j])
                {
                    return false;
                }
            }
        }

        return true;
    }

    bool operator!=(const Matrix &other) const
    {
        return !(*this == other);
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix)
    {
        for (size_t i = 0; i < matrix.rows_; ++i)
        {
            for (size_t j = 0; j < matrix.columns_; ++j)
            {
                os << matrix.data_[i][j] << ' ';
            }
            os << '\n';
        }

        return os;
    }
};

int main()
{
    const size_t rows = 5;
    const size_t cols = 3;

    Matrix m(rows, cols);

    assert(m.getRows() == 5);
    assert(m.getColumns() == 3);

    m[1][2] = 5;
    double x = m[4][1];

    m *= 3;

    Matrix m1(rows, cols);

    if (m1 == m)
    {
        std::cout << "m1 and m are equal" << std::endl;
    }
    else
    {
        std::cout << "m1 and m are not equal" << std::endl;
    }

    try
    {
        Matrix m2 = m + m1;
        std::cout << m2 << std::endl;
    }
    catch (const std::out_of_range &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
