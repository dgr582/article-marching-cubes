//DKE Green | 2020 | https://www.dgr582.com
//https://www.dgr582.com/articles/2020/marching-cubes

#ifndef CUBELATTICE3D_HPP
#define CUBELATTICE3D_HPP

#ifndef CUBELATTICE3D_H
#error __FILE__ should only be included from cubeLattice3D.h.
#endif

using dgr582::CubeLattice3D;

template<size_t sizeX, size_t sizeY, size_t sizeZ>
CubeLattice3D<sizeX, sizeY, sizeZ>::CubeLattice3D(float gridSpacing, const dgr582::Point3D& gridCentre) :
  _gridSpacing{ gridSpacing }, _gridCentre{ gridCentre },
   LatticeData3D<dgr582::Point3D, sizeX, sizeY, sizeZ>{}
{
    computeLatticeVertices();
}


template<size_t sizeX, size_t sizeY, size_t sizeZ>
void CubeLattice3D<sizeX, sizeY, sizeZ>::computeLatticeVertices()
{

    //subtract default centre and shift to new centre
    float centreAdjustX = -_gridSpacing * float(sizeX - 1) / 2.0f + _gridCentre[0];
    float centreAdjustY = -_gridSpacing * float(sizeY - 1) / 2.0f + _gridCentre[1];
    float centreAdjustZ = -_gridSpacing * float(sizeZ - 1) / 2.0f + _gridCentre[2];

    for (auto i = 0; i < sizeX; ++i)
    {
        for (auto j = 0; j < sizeY; ++j)
        {
            for (auto k = 0; k < sizeZ; ++k)
            {
                value(i, j, k) =
                {
                    i * _gridSpacing + centreAdjustX,
                    j * _gridSpacing + centreAdjustY,
                    k * _gridSpacing + centreAdjustZ
                };
            }
        }
    }
}


#endif //CUBELATTICE3D_HPP
