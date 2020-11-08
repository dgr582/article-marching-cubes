//DKE Green | 2020 | https://www.dgr582.com 
//https://www.dgr582.com/articles/2020/marching-cubes

#include "point3D.h"

using dgr582::Point3D;


Point3D::Point3D() : _points{ 0.0f, 0.0f, 0.0f }
{

}

Point3D::Point3D(float x, float y, float z) : _points{x, y, z}
{

}

Point3D::Point3D(const std::array<float, 3>& xyz) : _points{xyz}
{

}


float& Point3D::operator[](size_t idx) 
{ 
    return _points[idx]; 
}

const float& Point3D::operator[](size_t idx) const 
{ 
    return _points[idx]; 
}

