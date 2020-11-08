//DKE Green | 2020 | https://www.dgr582.com 
//https://www.dgr582.com/articles/2020/marching-cubes


#ifndef CUBELATTICE3D_H
#define CUBELATTICE3D_H

#include "point3D.h"
#include "latticeData3D.h"
#include <array>

namespace dgr582
{
    template<size_t sizeX, size_t sizeY, size_t sizeZ>
    class CubeLattice3D : public LatticeData3D<dgr582::Point3D, sizeX, sizeY, sizeZ>
    {
    public:

        CubeLattice3D(float gridSpacing, const dgr582::Point3D& gridCentre);
        ~CubeLattice3D() = default;


    private:
        float _gridSpacing;
        const dgr582::Point3D _gridCentre;
        void computeLatticeVertices();
    };
}

#include "cubeLattice3D.hpp"

#endif //CUBELATTICE3D_H