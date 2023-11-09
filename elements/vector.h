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
                dim(d), coord(new T[d]) 
                {
                    for(int i = 0; i < d; i++)
                        coord[i] = T();
                }
            vector(std::initializer_list<T> values): 
                dim(values.size())
                {
                    std::copy(values.begin(), values.end(), coord);
                }
            ~vector()
            {
                if(coord)
                    delete[] coord;
            }

            T norm2() const
            {
                T res = 0;
                for(int i = 0; i < dim; i++)
                    res += coord[i] * coord[i];
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
            T* begin()
            {
                return coord;
            }
            T* end()
            {
                return coord + dim;
            }
            
            inline vector operator+(const vector& other) const
            {
                if(dim != other.size())
                    throw std::invalid_argument("Dimensions do not match");
                vector b(dim);
                for(int i = 0; i < dim; i++)
                    b[i] = coord[i] + other[i];
                return b;
            }
            inline vector operator-(const vector& other) const
            {
                if(dim != other.size())
                    throw std::invalid_argument("Dimensions do not match");
                vector b(dim);
                for(int i = 0; i < dim; i++)
                    b[i] = coord[i] - other[i];
                return b;
            }
            inline vector operator=(const std::initializer_list<T> other)
            {
                if (other.size() != dim)
                    throw std::invalid_argument("Array length does not match vector dimension");
                for(int i = 0; i < dim; i++)
                    coord[i] = other.begin()[i];
                return *this;
            }
            inline vector operator=(std::vector<T> other)
            {
                if (other.size() != dim)
                    throw std::invalid_argument("Array length does not match vector dimension");
                for(int i = 0; i < dim; i++)
                    coord[i] = other[i];
                return *this;
            } 
            inline vector operator=(const vector& other)
            {
                if(dim != other.size())
                    throw std::invalid_argument("Dimensions do not match");
                for(int i = 0; i < dim; i++)
                    coord[i] = other[i];
                return *this;
                
            }
            inline bool operator==(const vector& other) const
            {
                if(dim != other.size())
                    return false;
                for(int i = 0; i < dim; i++)
                    if(coord[i] != other[i])
                        return false;
                return true;
            }
            inline vector operator*(const vector& other) const
            {
                if(dim != other.size() || dim != 3)
                    throw std::invalid_argument("One or both vectors aren't 3-dimensional");
                vector b(dim);
                b[0] = coord[1] * other[2] - coord[2] * other[1];
                b[1] = coord[2] * other[0] - coord[0] * other[2];
                b[2] = coord[0] * other[1] - coord[1] * other[0];
                return b;
            }
            inline vector operator*(const double& scalar) const
            {
                vector res(dim);
                for(int i = 0; i < dim; i++)
                    res[i] = coord[i] * scalar;
                return res;
            }
            inline vector operator/(const double& scalar) const
            {
                vector res(dim);
                for(int i = 0; i < dim; i++)
                    res[i] = coord[i] / scalar;
                return res;
            }
            inline vector operator/=(const double& scalar)
            {
                for(int i = 0; i < dim; i++)
                    coord[i] /= scalar;
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
                    res += coord[i] * other[i];
                return res;
            }
            inline T& operator[](size_t index)
            {
                if(index >= dim || index < 0)
                    throw std::out_of_range("Index out of range");
                return coord[index];
            }
            inline const T operator[](size_t index) const
            {
                if(index >= dim || index < 0)
                    throw std::out_of_range("Index out of range");
                return coord[index];
            }
            
        private:
            size_t dim;
            T* coord = new T[dim];
};
}