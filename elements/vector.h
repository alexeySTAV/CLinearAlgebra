#pragma once
#include <initializer_list>
#include <stdexcept>
#include <cmath>
#include <vector>

namespace linal
{
    template<typename T>
    class vector
    {
        public:
            vector(size_t d): 
                dim(d), data_(new T[d]) 
                {
                    for(int i = 0; i < d; i++)
                        data_[i] = T();
                }
            vector(std::initializer_list<T> values): 
                dim(values.size())
                {
                    std::copy(values.begin(), values.end(), data_);
                }
            ~vector()
            {
                if(data_)
                    delete[] data_;
            }

            T norm2() const
            {
                T res = 0;
                for(int i = 0; i < dim; i++)
                    res += data_[i] * data_[i];
                return res;
            }
            T norm() const
            {
                return std::sqrt(this->norm2());
            }
            size_t size() const
            {
                return dim;
            }
            T* begin() const
            {
                return data_;
            }
            T* end() const
            {
                return data_ + dim;
            }
            
            inline vector operator+(const vector& other) const
            {
                if(dim != other.size())
                    throw std::invalid_argument("Dimensions do not match");
                vector b(dim);
                for(int i = 0; i < dim; i++)
                    b[i] = data_[i] + other[i];
                return b;
            }
            inline vector operator-(const vector& other) const
            {
                if(dim != other.size())
                    throw std::invalid_argument("Dimensions do not match");
                vector b(dim);
                for(int i = 0; i < dim; i++)
                    b[i] = data_[i] - other[i];
                return b;
            }
            inline vector operator=(const std::initializer_list<T> other)
            {
                if (other.size() != dim)
                    throw std::invalid_argument("Array length does not match vector dimension");
                for(int i = 0; i < dim; i++)
                    data_[i] = other.begin()[i];
                return *this;
            }
            inline vector operator=(std::vector<T> other)
            {
                if (other.size() != dim)
                    throw std::invalid_argument("Array length does not match vector dimension");
                for(int i = 0; i < dim; i++)
                    data_[i] = other[i];
                return *this;
            } 
            inline vector operator=(const vector& other)
            {
                if(dim != other.size())
                    throw std::invalid_argument("Dimensions do not match");
                for(int i = 0; i < dim; i++)
                    data_[i] = other[i];
                return *this;
                
            }
            inline bool operator==(const vector& other) const
            {
                if(dim != other.size())
                    return false;
                for(int i = 0; i < dim; i++)
                    if(data_[i] != other[i])
                        return false;
                return true;
            }
            inline vector operator*(const vector& other) const
            {
                if(dim != other.size() || dim != 3)
                    throw std::invalid_argument("One or both vectors aren't 3-dimensional");
                vector b(dim);
                b[0] = data_[1] * other[2] - data_[2] * other[1];
                b[1] = data_[2] * other[0] - data_[0] * other[2];
                b[2] = data_[0] * other[1] - data_[1] * other[0];
                return b;
            }
            inline vector operator*(const double& scalar) const
            {
                vector res(dim);
                for(int i = 0; i < dim; i++)
                    res[i] = data_[i] * scalar;
                return res;
            }
            inline vector operator/(const double& scalar) const
            {
                vector res(dim);
                for(int i = 0; i < dim; i++)
                    res[i] = data_[i] / scalar;
                return res;
            }
            inline vector operator/=(const double& scalar)
            {
                for(int i = 0; i < dim; i++)
                    data_[i] /= scalar;
                return *this / scalar;
            }
            inline vector operator*=(const vector& other)
            {
                return *this * other;
            }
            inline vector operator*=(const T& scalar)
            {
                return *this * scalar;
            }
            inline vector operator+=(const vector& other)
            {
                return *this + other;
            }
            inline vector operator-=(const vector& other)
            {
                return *this - other;
            }
            inline T operator^(const vector& other) const
            {
                if(dim != other.size())
                    throw std::invalid_argument("Dimensions do not match");
                T res = 0;
                for(int i = 0; i < dim; i++)
                    res += data_[i] * other[i];
                return res;
            }
            inline T& operator[](size_t index)
            {
                if(index >= dim || index < 0)
                    throw std::out_of_range("Index out of range");
                return data_[index];
            }
            inline const T operator[](size_t index) const
            {
                if(index >= dim || index < 0)
                    throw std::out_of_range("Index out of range");
                return data_[index];
            }
            
        private:
            size_t dim;
            T* data_ = new T[dim];
};
}