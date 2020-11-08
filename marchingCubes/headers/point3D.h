//DKE Green | 2020 | https://www.dgr582.com 
//https://www.dgr582.com/articles/2020/marching-cubes

#ifndef POINT3D_H
#define POINT3D_H

#include <array>

namespace dgr582
{
    class Point3D
    {
    public:
        Point3D();
        Point3D(float x, float y, float z);
        Point3D(const std::array<float, 3>& xyz);
        ~Point3D() = default;

        float& operator[](size_t idx);
        const float& operator[](size_t idx) const;

    private:
        std::array<float, 3> _points;


    };
}

#endif //POINT3D_H
