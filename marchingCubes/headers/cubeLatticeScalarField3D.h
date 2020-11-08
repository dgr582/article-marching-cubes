//DKE Green | 2020 | https://www.dgr582.com
//https://www.dgr582.com/articles/2020/marching-cubes

#ifndef CUBELATTICESCALARFIELD3D_H
#define CUBELATTICESCALARFIELD3D_H

#include "latticeData3D.h"
#include "cubeLattice3D.h"
#include "triangle3D.h"
#include <array>
#include <vector>

namespace dgr582
{

  template<size_t sizeX, size_t sizeY, size_t sizeZ>
  class CubeLatticeScalarField3D
  {
  public:

      CubeLatticeScalarField3D(float gridSpacing, const dgr582::Point3D& gridCentre);

      CubeLatticeScalarField3D(
          float gridSpacing, const dgr582::Point3D& gridCentre,
          const LatticeData3D<float, sizeX, sizeY, sizeZ>& scalarField);

      ~CubeLatticeScalarField3D() = default;

      /**
      * \brief Compute a list of vertices and normals for the marching cube mesh
      *
      * \return A list of vertices, the format is [[vert1.x,vert1.y,vert1.z,normal1.x,normal1.y,normal1.z], ... ,[vertN.x,vertN.y,vertN.z,normalN.x,normalN.y,normalN.z]]
      */
      std::vector<float> computeVertexDrawData(double isoLevel);

      dgr582::CubeLatticeScalarField3D<sizeX, sizeY, sizeZ>& getCubeLattice();
      const dgr582::CubeLatticeScalarField3D<sizeX, sizeY, sizeZ>& getCubeLattice() const;

      dgr582::LatticeData3D<float, sizeX, sizeY, sizeZ>& getScalarField();
      const dgr582::LatticeData3D<float, sizeX, sizeY, sizeZ>& getScalarField() const;

  private:
      dgr582::CubeLattice3D<sizeX, sizeY, sizeZ> _cubeLattice;
      dgr582::LatticeData3D<float, sizeX, sizeY, sizeZ> _scalarField;

      unsigned int polygoniseCell(size_t i, size_t j, size_t k, double isoLevel, std::array<dgr582::Triangle3D, 5>& triangleResult);

      std::array<size_t, 3> cellCornerIndexToIJKIndex(size_t vertexIndex, size_t i, size_t j, size_t k);
      dgr582::Point3D interpolateVertex(double isoLevel, const std::array<size_t,3>& vertIJK1, const std::array<size_t, 3>& vertIJK2);


  };
}

#include "cubeLatticeScalarField3D.hpp"

#endif //CUBELATTICESCALARFIELD3D_H