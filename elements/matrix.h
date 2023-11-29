#pragma once
#include <initializer_list>
#include <stdexcept>
#include <cmath>

namespace linal
{
    template<typename T = double>
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
        
        matrix transpose()
        {
            matrix<T> res(columns_, rows_);
            for(int i = 0; i < rows_; i++)
                for(int j = 0; j < columns_; j++)
                    res[j][i] = (*this)[i][j];
            return res;
        }

        T det()
        {
            T res = T();
            if(columns_ != rows_)
                throw std::invalid_argument("On this quiz, I asked you to find the determinant of a 2x3 matrix.\nSome of you, to my great amusement, actually tried to do this.\n(Via mathprofessorquotes.com, no name listed)");
            if(columns_ == 2 && rows_ == 2)
                return (*this)[0][0] * (*this)[1][1] - (*this)[1][0] * (*this)[0][1];
            for(int i = 0; i < columns_; i++)
                res += (*this)[0][i] * pow(-1, i) * cutMatrix(*this, 0, i).det();
            return res;
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
        friend std::ostream& operator<<(std::ostream& os, const matrix<T>& mat) {
            os << std::string("{\n");
            for (size_t i = 0; i < mat.rows(); ++i) {
                os << std::string("  {");
                for (size_t j = 0; j < mat.columns(); ++j) {
                    os << mat[i][j];
                    if (j < mat.columns() - 1) os << std::string(", ");
                }
                os << std::string("}");
                if (i < mat.rows() - 1) os << std::string(",");
                os << std::string("\n");
            }
            os << std::string("}");
            return os;
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
        
        matrix cutMatrix(matrix& toCut, size_t Index, size_t Jndex)
        {
            matrix<T> res(toCut.rows() - 1, toCut.columns() - 1);
            int itr = 0, jtr = 0;
            for(int i = 0; i < toCut.rows(); i++)
            {
                jtr = 0;
                if(i == Index)
                    continue;
                for(int j = 0; j < toCut.columns(); j++)
                {
                    if(j == Jndex)
                        continue;
                    res[itr][jtr] = toCut[i][j];
                    jtr++;
                }
                itr++;
            }
            return res;
        }

    };
}