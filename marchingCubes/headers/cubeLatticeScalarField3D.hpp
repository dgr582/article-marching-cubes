//DKE Green | 2020 | https://www.dgr582.com
//https://www.dgr582.com/articles/2020/marching-cubes

#ifndef CUBELATTICESCALARFIELD3D_HPP
#define CUBELATTICESCALARFIELD3D_HPP

#ifndef CUBELATTICESCALARFIELD3D_H
#error __FILE__ should only be included from cubeLatticeScalarField3D.h.
#endif

using dgr582::CubeLatticeScalarField3D;

#include "mcubes.h"

template<size_t sizeX, size_t sizeY, size_t sizeZ>
CubeLatticeScalarField3D<sizeX, sizeY, sizeZ>::CubeLatticeScalarField3D(float gridSpacing, const dgr582::Point3D& gridCentre) :
    _cubeLattice{ gridSpacing, gridCentre }, _scalarField{ }
{

}


template<size_t sizeX, size_t sizeY, size_t sizeZ>
CubeLatticeScalarField3D<sizeX, sizeY, sizeZ>::CubeLatticeScalarField3D(
  float gridSpacing, const dgr582::Point3D& gridCentre,
  const LatticeData3D<float, sizeX, sizeY, sizeZ>& scalarField) :
  _cubeLattice{ gridSpacing, gridCentre }, _scalarField{ scalarField }
{

}


template<size_t sizeX, size_t sizeY, size_t sizeZ>
dgr582::CubeLatticeScalarField3D<sizeX, sizeY, sizeZ>& 
CubeLatticeScalarField3D<sizeX, sizeY, sizeZ>::getCubeLattice()
{
    return _cubeLattice;
}

template<size_t sizeX, size_t sizeY, size_t sizeZ>
const dgr582::CubeLatticeScalarField3D<sizeX, sizeY, sizeZ>& 
CubeLatticeScalarField3D<sizeX, sizeY, sizeZ>::getCubeLattice() const
{
    return _cubeLattice;
}


template<size_t sizeX, size_t sizeY, size_t sizeZ>
dgr582::LatticeData3D<float, sizeX, sizeY, sizeZ>& 
CubeLatticeScalarField3D<sizeX, sizeY, sizeZ>::getScalarField()
{
    return _scalarField;
}


template<size_t sizeX, size_t sizeY, size_t sizeZ>
const dgr582::LatticeData3D<float, sizeX, sizeY, sizeZ>&
CubeLatticeScalarField3D<sizeX, sizeY, sizeZ>::getScalarField() const
{
    return _scalarField;
}



template<size_t sizeX, size_t sizeY, size_t sizeZ>
std::vector<float> CubeLatticeScalarField3D<sizeX, sizeY, sizeZ>::computeVertexDrawData(double isoLevel)
{

    std::vector<float> retVec;


    std::array<dgr582::Triangle3D, 5> trianglesAfterPolygonisation;

    //first, polygonise the field
    //iterate over cells, not over points
    for (auto i = 0; i < sizeX - 1; ++i)
    {
        for (auto j = 0; j < sizeY - 1; ++j)
        {
            for (auto k = 0; k < sizeZ - 1; ++k)
            {
                auto numTris = polygoniseCell(i, j, k, isoLevel, trianglesAfterPolygonisation);
                for (decltype(numTris) c = 0; c < numTris; ++c)
                {
                    auto normal = trianglesAfterPolygonisation[c].computeNormal(); //dodgy version here: using the triangle normal instead of a smoothed normal at the vertices

                    
                    //this is a little inefficient, but ok enough for this
                    retVec.push_back(trianglesAfterPolygonisation[c][0][0]);
                    retVec.push_back(trianglesAfterPolygonisation[c][0][1]);
                    retVec.push_back(trianglesAfterPolygonisation[c][0][2]);
                    retVec.push_back(normal[0]);
                    retVec.push_back(normal[1]);
                    retVec.push_back(normal[2]);


                    retVec.push_back(trianglesAfterPolygonisation[c][1][0]);
                    retVec.push_back(trianglesAfterPolygonisation[c][1][1]);
                    retVec.push_back(trianglesAfterPolygonisation[c][1][2]);
                    retVec.push_back(normal[0]);
                    retVec.push_back(normal[1]);
                    retVec.push_back(normal[2]);

                    retVec.push_back(trianglesAfterPolygonisation[c][2][0]);
                    retVec.push_back(trianglesAfterPolygonisation[c][2][1]);
                    retVec.push_back(trianglesAfterPolygonisation[c][2][2]);
                    retVec.push_back(normal[0]);
                    retVec.push_back(normal[1]);
                    retVec.push_back(normal[2]);
                }
            }
        }
    }




    return retVec;
}

template<size_t sizeX, size_t sizeY, size_t sizeZ>
std::array<size_t, 3> CubeLatticeScalarField3D<sizeX, sizeY, sizeZ>::cellCornerIndexToIJKIndex(size_t vertexIndex, size_t i, size_t j, size_t k)
{
    //Given a grid cell IJK, work out the index of the cell corners given an index from 0 to 7
    //
    // 0 - bottom left , near face  (x            , y            , z            )
    // 1 - bottom right, near face  (x+gridSpacing, y            , z            )
    // 2 - top right   , near face  (x+gridSpacing, y            , z+gridSpacing)
    // 3 - top left    , near face  (x            , y            , z+gridSpacing)
    // 4 - bottom left , far face   (x            , y+gridSpacing, z            )
    // 5 - bottom right, far face   (x+gridSpacing, y+gridSpacing, z            )
    // 6 - top right   , far face   (x+gridSpacing, y+gridSpacing, z+gridSpacing)
    // 7 - top left    , far face   (x            , y+gridSpacing, z+gridSpacing)

    
    switch (vertexIndex)
    {
    case 0:
        return { i  ,j  ,k+1 };
    case 1:
        return { i+1,j  ,k + 1 };
    case 2:
        return { i+1  ,j, k };
    case 3:
        return { i,j, k };
    case 4:
        return { i  ,j+1  ,k+1 };
    case 5:
        return { i+1,j+1  ,k+1 };
    case 6:
        return { i+1  ,j+1,k };
    case 7:
        return { i,j+1,k };
    default:
        return {};//shouldn't ever get here, polygonise shouldn't call for vertexIndex outside 0 to 7 - safer to put an assert here...
    }
}

/*
   Given a grid cell and an isolevel, calculate the triangular
   facets required to represent the isosurface through the cell.
   Return the number of triangular facets, the array "triangles"
   will be loaded up with the vertices at most 5 triangular facets.
    0 will be returned if the grid cell is either totally above
   of totally below the isolevel.
*/
template<size_t sizeX, size_t sizeY, size_t sizeZ>
unsigned int CubeLatticeScalarField3D<sizeX, sizeY, sizeZ>::polygoniseCell(
    size_t i, size_t j, size_t k, double isoLevel, std::array<dgr582::Triangle3D, 5>& triangleResult)
{
    int cubeindex = 0;
    std::array<dgr582::Point3D, 12> vertlist{};

    if (_scalarField[cellCornerIndexToIJKIndex(0, i, j, k)] < isoLevel) cubeindex |= 1;
    if (_scalarField[cellCornerIndexToIJKIndex(1, i, j, k)] < isoLevel) cubeindex |= 2;
    if (_scalarField[cellCornerIndexToIJKIndex(2, i, j, k)] < isoLevel) cubeindex |= 4;
    if (_scalarField[cellCornerIndexToIJKIndex(3, i, j, k)] < isoLevel) cubeindex |= 8;
    if (_scalarField[cellCornerIndexToIJKIndex(4, i, j, k)] < isoLevel) cubeindex |= 16;
    if (_scalarField[cellCornerIndexToIJKIndex(5, i, j, k)] < isoLevel) cubeindex |= 32;
    if (_scalarField[cellCornerIndexToIJKIndex(6, i, j, k)] < isoLevel) cubeindex |= 64;
    if (_scalarField[cellCornerIndexToIJKIndex(7, i, j, k)] < isoLevel) cubeindex |= 128;

    /* Cube is entirely in/out of the surface */
    if (edgeTable[cubeindex] == 0)
        return(0);

    /* Find the vertices where the surface intersects the cube */
    if (edgeTable[cubeindex] & 1)
        vertlist[0] = interpolateVertex(isoLevel, cellCornerIndexToIJKIndex(0, i, j, k), cellCornerIndexToIJKIndex(1, i, j, k));
    if (edgeTable[cubeindex] & 2)
        vertlist[1] = interpolateVertex(isoLevel, cellCornerIndexToIJKIndex(1, i, j, k), cellCornerIndexToIJKIndex(2, i, j, k));
    if (edgeTable[cubeindex] & 4)
        vertlist[2] = interpolateVertex(isoLevel, cellCornerIndexToIJKIndex(2, i, j, k), cellCornerIndexToIJKIndex(3, i, j, k));
    if (edgeTable[cubeindex] & 8)
        vertlist[3] = interpolateVertex(isoLevel, cellCornerIndexToIJKIndex(3, i, j, k), cellCornerIndexToIJKIndex(0, i, j, k));
    if (edgeTable[cubeindex] & 16)
        vertlist[4] = interpolateVertex(isoLevel, cellCornerIndexToIJKIndex(4, i, j, k), cellCornerIndexToIJKIndex(5, i, j, k));
    if (edgeTable[cubeindex] & 32)
        vertlist[5] = interpolateVertex(isoLevel, cellCornerIndexToIJKIndex(5, i, j, k), cellCornerIndexToIJKIndex(6, i, j, k));
    if (edgeTable[cubeindex] & 64)
        vertlist[6] = interpolateVertex(isoLevel, cellCornerIndexToIJKIndex(6, i, j, k), cellCornerIndexToIJKIndex(7, i, j, k));
    if (edgeTable[cubeindex] & 128)
        vertlist[7] = interpolateVertex(isoLevel, cellCornerIndexToIJKIndex(7, i, j, k), cellCornerIndexToIJKIndex(4, i, j, k));
    if (edgeTable[cubeindex] & 256)
        vertlist[8] = interpolateVertex(isoLevel, cellCornerIndexToIJKIndex(0, i, j, k), cellCornerIndexToIJKIndex(4, i, j, k));
    if (edgeTable[cubeindex] & 512)
        vertlist[9] = interpolateVertex(isoLevel, cellCornerIndexToIJKIndex(1, i, j, k), cellCornerIndexToIJKIndex(5, i, j, k));
    if (edgeTable[cubeindex] & 1024)
        vertlist[10] = interpolateVertex(isoLevel, cellCornerIndexToIJKIndex(2, i, j, k), cellCornerIndexToIJKIndex(6, i, j, k));
    if (edgeTable[cubeindex] & 2048)
        vertlist[11] = interpolateVertex(isoLevel, cellCornerIndexToIJKIndex(3, i, j, k), cellCornerIndexToIJKIndex(7, i, j, k));

    /* Create the triangle */
    int ntriang = 0;
    for (auto t = 0; triTable[cubeindex][t] != -1; t += 3) {
        triangleResult[ntriang][0] = vertlist[triTable[cubeindex][t    ]];
        triangleResult[ntriang][1] = vertlist[triTable[cubeindex][t + 1]];
        triangleResult[ntriang][2] = vertlist[triTable[cubeindex][t + 2]];
        ntriang++;
    }

    return(ntriang);
}


/*
   Linearly interpolate the position where an isosurface cuts
   an edge between two vertices, each with their own scalar value
*/
template<size_t sizeX, size_t sizeY, size_t sizeZ>
dgr582::Point3D CubeLatticeScalarField3D<sizeX, sizeY, sizeZ>::interpolateVertex(
    double isoLevel, const std::array<size_t, 3>& vertIJK1, const std::array<size_t, 3>& vertIJK2)
{
    auto& p1 = _cubeLattice[vertIJK1];
    auto& p2 = _cubeLattice[vertIJK2];

    auto valp1 = _scalarField[vertIJK1];
    auto valp2 = _scalarField[vertIJK2];

    double mu;
    dgr582::Point3D p;

    if (abs(isoLevel - valp1) < 0.00001)
        return(p1);
    if (abs(isoLevel - valp2) < 0.00001)
        return(p2);
    if (abs(valp1 - valp2) < 0.00001)
        return(p1);
    mu = (isoLevel - valp1) / (valp2 - valp1);
    p[0] = float(p1[0] + mu * (p2[0] - p1[0]));
    p[1] = float(p1[1] + mu * (p2[1] - p1[1]));
    p[2] = float(p1[2] + mu * (p2[2] - p1[2]));

    return(p);
}



#endif //CUBELATTICESCALARFIELD3D_HPP
