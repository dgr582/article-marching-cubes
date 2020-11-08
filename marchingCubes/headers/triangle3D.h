//DKE Green | 2020 | https://www.dgr582.com
//https://www.dgr582.com/articles/2020/marching-cubes


#ifndef TRIANGLE3D_H
#define TRIANGLE3D_H

#include "point3D.h"
#include <array>

namespace dgr582
{
  class Triangle3D
  {
  public:
      Triangle3D();

      Triangle3D(const dgr582::Point3D& p1, 
      const dgr582::Point3D& p2, const dgr582::Point3D& p3);

      Triangle3D(const std::array<Point3D, 3>& points);
      ~Triangle3D() = default;

      dgr582::Point3D& operator[](size_t idx);
      const dgr582::Point3D& operator[](size_t idx) const;

      std::array<float, 3> computeNormal();

  private:
      std::array<Point3D, 3> _vertices;
  };
}



#endif //TRIANGLE3D_H
