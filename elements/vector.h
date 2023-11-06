#pragma once
#include <initializer_list>
#include <stdexcept>
#include <cmath>
#include <vector>

namespace linal
{
    class vector
    {
        public:
            vector(size_t d): 
                dim(d) {}
            vector(std::initializer_list<double> values): 
                dim(values.size())
                {
                    int i = 0;
                    for(double value : values)
                    {    
                        coord[i] = value;
                        i++;
                    }
                }
            ~vector()
            {
                delete[] coord;
            }

            double norm2() const
            {
                double res = 0;
                for(int i = 0; i < dim; i++)
                    res += coord[i] * coord[i];
                return res;
            }
            double norm() const
            {
                return std::sqrt(this->norm2());
            }
            size_t size() const
            {
                return dim;
            }
            double* begin()
            {
                return coord;
            }
            double* end()
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
            inline vector operator=(const std::initializer_list<double> other)
            {
                if (other.size() != dim)
                    throw std::invalid_argument("Array length does not match vector dimension");
                for(int i = 0; i < dim; i++)
                    coord[i] = other.begin()[i];
                return *this;
            }
            inline vector operator=(std::vector<double> other)
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
            inline vector operator*(const double& scalar)
            {
                for(int i = 0; i < dim; i++)
                    coord[i] *= scalar;
                return *this;
            }
            inline vector operator/(const double& scalar)
            {
                for(int i = 0; i < dim; i++)
                    coord[i] /= scalar;
                return *this;
            }
            inline vector operator/=(const double& scalar)
            {
                for(int i = 0; i < dim; i++)
                    coord[i] /= scalar;
                return *this;
            }
            inline vector operator*=(const auto& other)
            {
                return *this * other;
            }
            inline vector operator+=(const vector& other)
            {
                return *this + other;
            }
            inline vector operator-=(const vector& other)
            {
                return *this - other;
            }
            inline double operator^(const vector& other) const
            {
                if(dim != other.size())
                    throw std::invalid_argument("Dimensions do not match");
                double res = 0;
                for(int i = 0; i < dim; i++)
                    res += coord[i] * other[i];
                return res;
            }
            inline double& operator[](size_t index)
            {
                if(index >= dim || index < 0)
                    throw std::out_of_range("Index out of range");
                return coord[index];
            }
            inline const double operator[](size_t index) const
            {
                if(index >= dim || index < 0)
                    throw std::out_of_range("Index out of range");
                return coord[index];
            }
            
        private:
            size_t dim;
            double* coord = new double[dim];
};
}