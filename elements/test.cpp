#include <iostream>
#include "vector.h"

int main()
{
    linal::vector<double> a = {1.0, 2.0, 3.0};
    //int scalar = 2;
    //a /= scalar;
    for(double coord : a)
        printf("%1f ", coord);
    return 0;
}