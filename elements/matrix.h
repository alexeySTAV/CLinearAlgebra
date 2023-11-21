#pragma once
#include <initializer_list>
#include <stdexcept>

namespace linal
{
    template<typename T>
    class matrix
    {
        public:
        matrix(size_t rows, size_t columns): 
        rows_(rows), columns_(columns), data_(new T[rows * columns]()){}
        matrix(std::initializer_list<std::initializer_list<T>> init): 
        rows_(init.size()), columns_(init.begin()->size()), data_(new T[init.size() * init.begin()->size()])
        {
            for(size_t i = 0; i < init.size(); i++)
                for(size_t j = 0; j < init.begin()[i].size(); j++)
                    data_[i * columns_ + j] = init.begin()[i].begin()[j];
        }
        matrix(const matrix& other):
        rows_(other.rows()), columns_(other.columns()), data_(new T[other.rows() * other.columns()])
        {
           if(other.columns() != columns_ || other.rows() != rows_)
                throw std::invalid_argument("Matrices's dimensions do not match!");
            for(int i = 0; i < rows_; i++)
                for(int j = 0; j < columns_; j++)
                    (*this)[i][j] = other[i][j]; 
        }
        ~matrix()
        {
            if(data_)
                delete[] data_;
        }

        size_t columns() const
        {
            return columns_;
        }
        size_t rows() const
        {
            return rows_;
        }
        
        
        private:
        class Row 
        {
        public:
        Row(T* row, size_t col) : row(row), colum_(col) {}
        ~Row(){}
        inline T& operator[](size_t colIndex) const 
        {
            if (colIndex >= colum_) 
            {
                throw std::out_of_range("Columns out of range!");
            }
            return row[colIndex];
        }
        inline T& operator[](size_t colIndex)
        {
            if (colIndex >= colum_) 
            {
                throw std::out_of_range("Columns out of range!");
            }
            return row[colIndex];
        }
        private:
        T* row;
        size_t colum_;
        };
        
        
        public:
        inline Row operator[](size_t rowIndex) const 
        {
    
            if (rowIndex >= rows_) 
                throw std::out_of_range("Rows out of range!");
            return Row(&data_[rowIndex * columns_], columns_);
        }
        inline Row operator[](size_t rowIndex) 
        {
    
            if (rowIndex >= rows_) 
                throw std::out_of_range("Rows out of range!");
            return Row(&data_[rowIndex * columns_], columns_);
        }
        inline matrix& operator=(const matrix& other)
        {
            if(other.columns() != columns_ || other.rows() != rows_)
                throw std::invalid_argument("Matrices's dimensions do not match!");
            for(int i = 0; i < rows_; i++)
                for(int j = 0; j < columns_; j++)
                    (*this)[i][j] = other[i][j];
            return *this;
        }
        inline matrix operator+(const matrix& other) const
        {
            if(other.columns() != columns_ || other.rows() != rows_)
                throw std::invalid_argument("Matrices's dimensions do not match!");
            matrix<T> res(rows_, columns_);
            for(int i = 0; i < rows_; i++)
                for(int j = 0; j < columns_; j++)
                    res[i][j] = (*this)[i][j] + other[i][j];
            return res;
        }
        inline matrix operator-(const matrix& other) const
        {
            if(other.columns() != columns_ || other.rows() != rows_)
                throw std::invalid_argument("Matrices's dimensions do not match!");
            matrix<T> res(rows_, columns_);
            for(int i = 0; i < rows_; i++)
                for(int j = 0; j < columns_; j++)
                    res[i][j] = (*this)[i][j] - other[i][j];
            return res;
        }
        inline matrix operator*(const T scalar) const
        {
            matrix<T> res(rows_, columns_);
            for(int i = 0; i < rows_; i++)
                for(int j = 0; j < columns_; j++)
                    res[i][j] = (*this)[i][j] * scalar;
            return res;
        }
        inline matrix operator/(const T scalar) const
        {
            matrix<T> res(rows_, columns_);
            for(int i = 0; i < rows_; i++)
                for(int j = 0; j < columns_; j++)
                    res[i][j] = (*this)[i][j] / scalar;
            return res;
        }
        inline matrix operator*(const matrix& other) const 
        {
            if(columns_ != other.rows())
                throw std::invalid_argument("Matrices's dimensions do not match!");
            matrix<T> res(rows_, other.columns());
            for(int i = 0; i < rows_; i++)
                for(int j = 0; j < other.columns(); j++)
                    for(int k = 0; k < columns_; k++)
                        res[i][j] += (*this)[i][k] * other[k][j];
            return res;
        }

        inline matrix& operator+=(const matrix& other)
        {
            if(other.columns() != columns_ || other.rows() != rows_)
                throw std::invalid_argument("Matrices's dimensions do not match!");
            for(int i = 0; i < rows_; i++)
                for(int j = 0; j < columns_; j++)
                    (*this)[i][j] += other[i][j];
            return *this;
        }
        inline matrix& operator-=(const matrix& other)
        {
            if(other.columns() != columns_ || other.rows() != rows_)
                throw std::invalid_argument("Matrices's dimensions do not match!");
            for(int i = 0; i < rows_; i++)
                for(int j = 0; j < columns_; j++)
                    (*this)[i][j] -= other[i][j];
            return *this;
        }
        inline matrix& operator*=(const T scalar)
        {
            for(int i = 0; i < rows_; i++)
                for(int j = 0; j < columns_; j++)
                    (*this)[i][j] *= scalar;
            return *this;
        }
        inline matrix& operator/=(const T scalar)
        {
            for(int i = 0; i < rows_; i++)
                for(int j = 0; j < columns_; j++)
                    (*this)[i][j] /= scalar;
            return *this;
        }
        
        private:
        size_t rows_, columns_;
        T* data_ = new T[rows_ * columns_];

    };
}