//DKE Green | 2020 | https://www.dgr582.com
//https://www.dgr582.com/articles/2020/marching-cubes

#ifndef LATTICEDATA3D_H
#define LATTICEDATA3D_H

#include "point3D.h"
#include <array>

namespace dgr582
{
    template<typename T, size_t sizeX, size_t sizeY, size_t sizeZ>
    class LatticeData3D
    {
    public:

        LatticeData3D();
        LatticeData3D(const std::array<T, sizeX* sizeY* sizeZ>& data);
        ~LatticeData3D() = default;

        T& operator[](size_t idx);
        const T& operator[](size_t idx) const;

        T& operator[](const std::array<size_t,3>& ijk);
        const T& operator[](const std::array<size_t, 3>& ijk) const;

        T& value(size_t i, size_t j, size_t k);
        const T& value(size_t i, size_t j, size_t k) const;

    protected:
        std::array<T, sizeX* sizeY* sizeZ> _data;

        size_t ijkToLinearIndex(size_t i, size_t j, size_t k);
    };  
}

#include "latticeData3D.hpp"

#endif //LATTICEDATA3D_H