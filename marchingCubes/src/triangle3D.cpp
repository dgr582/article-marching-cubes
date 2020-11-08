//DKE Green | 2020 | https://www.dgr582.com
//https://www.dgr582.com/articles/2020/marching-cubes


#include "triangle3D.h"

using dgr582::Triangle3D;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Triangle3D::Triangle3D() : _vertices{}
{

}


Triangle3D::Triangle3D(const dgr582::Point3D& p1, 
  const dgr582::Point3D& p2, const dgr582::Point3D& p3) : 
    _vertices{p1, p2, p3}
{

}

Triangle3D::Triangle3D(const std::array<Point3D, 3>& points) : 
    _vertices{points}
{

}


dgr582::Point3D& Triangle3D::operator[](size_t idx)
{
    return _vertices[idx]; 
}
 
const dgr582::Point3D& Triangle3D::operator[](size_t idx) const 
{ 
    return _vertices[idx]; 
}


std::array<float, 3> Triangle3D::computeNormal()
{
    //sneaking glm in here, nor super clean but is easier than writing my own cross product!

   //Dir = (B - A) x(C - A)
   //Norm = Dir / len(Dir)
    auto dir = glm::cross(
        (glm::vec3{ _vertices[1][0], _vertices[1][1], _vertices[1][2] } - glm::vec3{ _vertices[0][0], _vertices[0][1], _vertices[0][2] }),
        (glm::vec3{ _vertices[2][0], _vertices[2][1], _vertices[2][2] } - glm::vec3{ _vertices[0][0], _vertices[0][1], _vertices[0][2] })
    );
    auto retNormal = dir / glm::length(dir);
    return { retNormal.x, retNormal.y, retNormal.z };
}

