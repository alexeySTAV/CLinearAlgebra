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
        rows_(rows), columns_(columns), data_(new T[rows * columns])
        {
            for(int i = 0; i < rows * columns; i++)
                data_ = T();
        }
        matrix(std::initializer_list<std::initializer_list<T>> init): 
        rows_(init.size()), columns_(init.begin()->size()), data_(new T[init.size() * init.begin()->size()])
        {
            for(int i = 0; i < init.size(); i++)
                for(int j = 0; j < init.begin()->size(); j++)
                    data_[i * init.size() + j] = init.begin()[i].begin()[j];
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
        class RowProxy 
        {
        public:
        RowProxy(T* row, size_t col) : row(row), colum_(col) {}

        T& operator[](size_t colIndex) const 
        {
            if (colIndex >= colum_) 
            {
                throw std::out_of_range("Columns out of range!");
            }
            return row[colIndex];
        }
        T& operator[](size_t colIndex)
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
        inline RowProxy operator[](size_t rowIndex) const 
        {
    
            if (rowIndex >= rows_) 
                throw std::out_of_range("Rows out of range!");
            return RowProxy(&data_[rowIndex * columns_], columns_);
        }
        inline RowProxy operator[](size_t rowIndex) 
        {
    
            if (rowIndex >= rows_) 
                throw std::out_of_range("Rows out of range!");
            return RowProxy(&data_[rowIndex * columns_], columns_);
        }
        
        private:
        size_t rows_, columns_;
        T* data_ = new T[rows_ * columns_];

    };
}