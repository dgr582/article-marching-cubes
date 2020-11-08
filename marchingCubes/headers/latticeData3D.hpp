//DKE Green | 2020 | https://www.dgr582.com
//https://www.dgr582.com/articles/2020/marching-cubes

#ifndef LATTICEDATA3D_HPP
#define LATTICEDATA3D_HPP

#ifndef LATTICEDATA3D_H
#error __FILE__ should only be included from latticeData3D.h.
#endif

using dgr582::LatticeData3D;

template<typename T, size_t sizeX, size_t sizeY, size_t sizeZ>
LatticeData3D<T, sizeX, sizeY, sizeZ>::LatticeData3D() : _data{}
{

}

template<typename T, size_t sizeX, size_t sizeY, size_t sizeZ>
LatticeData3D<T, sizeX, sizeY, sizeZ>::LatticeData3D(
  const std::array<T, sizeX*sizeY*sizeZ>& data) : _data{ data }
{

}


template<typename T, size_t sizeX, size_t sizeY, size_t sizeZ>
T& LatticeData3D<T, sizeX, sizeY, sizeZ>::operator[](size_t idx) 
{ 
    return _data[idx]; 
}


template<typename T, size_t sizeX, size_t sizeY, size_t sizeZ>
const T& LatticeData3D<T, sizeX, sizeY, sizeZ>::operator[](size_t idx) const 
{ 
    return _data[idx]; 
}


template<typename T, size_t sizeX, size_t sizeY, size_t sizeZ>
T& LatticeData3D<T, sizeX, sizeY, sizeZ>::value(size_t i, size_t j, size_t k)
{
    return _data[ijkToLinearIndex(i, j, k)];
}


template<typename T, size_t sizeX, size_t sizeY, size_t sizeZ>
const T& LatticeData3D<T, sizeX, sizeY, sizeZ>::value(size_t i, size_t j, size_t k) const
{
    return _data[ijkToLinearIndex(i,j,k)];
}


template<typename T, size_t sizeX, size_t sizeY, size_t sizeZ>
T& LatticeData3D<T, sizeX, sizeY, sizeZ>::operator[](const std::array<size_t, 3>& ijk)
{
    return _data[ijkToLinearIndex(ijk[0], ijk[1], ijk[2])];
}

template<typename T, size_t sizeX, size_t sizeY, size_t sizeZ>
const T& LatticeData3D<T, sizeX, sizeY, sizeZ>::operator[](const std::array<size_t, 3>& ijk) const
{
    return _data[ijkToLinearIndex(ijk[0], ijk[1], ijk[2])];
}



template<typename T, size_t sizeX, size_t sizeY, size_t sizeZ>
size_t LatticeData3D<T, sizeX, sizeY, sizeZ>::ijkToLinearIndex(
    size_t i, size_t j, size_t k)
{
    //Z first, then Y, then X
    return i*sizeY*sizeZ + j*sizeZ + k;
}


#endif //LATTICEDATA3D_HPP
