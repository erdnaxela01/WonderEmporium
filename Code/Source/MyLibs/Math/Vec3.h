#ifndef __VEC3_H
#define __VEC3_H


template<typename type>
struct vec3
{
    type x;
    type y;
    type z;

    //structor
    vec3();
    vec3(type tx, type ty, type tz);

    //Math operatrions
    vec3 operator+(vec3 rhs);
    vec3 operator-(vec3 rhs);
    vec3 operator*(vec3 rhs);
    vec3 operator/(type rhs) const;
	vec3 operator*(type rhs)const;
    vec3 operator+=(vec3 rhs);
    vec3 operator-=(vec3 rhs);
    vec3 operator*=(vec3 rhs);
    vec3 operator/=(type rhs);
    vec3 operator*=(type rhs);
    //returns the normalized vector
    vec3 Normalized();
    //returns the dot product between it an two vectors
    type Dot(vec3 rhs);

    //returns the length of the vector
    type Length();

    //returns the distance between this vector and another
    type Distance(vec3 rhs);

    //return the vec3 perpendicular to both vectors
    vec3 Cross(vec3 rhs);

};

//structor
template<typename type>
vec3<type>::vec3() :x(0.0f), y(0.0f), z(0.0f)
{
}

template<typename type>
vec3<type>::vec3(type tx, type ty, type tz) : x(tx), y(ty), z(tz)
{

}

//Math operatrions
template<typename type>
vec3<type> vec3<type>::operator+(vec3 rhs)
{
    return vec3(x + rhs.x, y + rhs.y, z + rhs.z);
}

template<typename type>
vec3<type> vec3<type>::operator-(vec3 rhs)
{
    return vec3(x - rhs.x, y - rhs.y, z - rhs.z);
}

template<typename type>
vec3<type> vec3<type>::operator*(vec3 rhs)
{
    return vec3(x * rhs.x, y * rhs.y, z * rhs.z);
}

template<typename type>
vec3<type> vec3<type>::operator/(type rhs) const
{
    return vec3(x / rhs, y / rhs, z / rhs);
}

template<typename type>
vec3<type> vec3<type>::operator*(type rhs)const
{
    return vec3(x * rhs, y * rhs, z*rhs);
}

template<typename type>
vec3<type> vec3<type>::Normalized()
{
    float length = Length();
    return vec3(x / length, y / length, z / length);
}

template<typename type>
type vec3<type>::Dot(vec3 rhs)
{
    return (x * rhs.x + y * rhs.y + z * rhs.z);
}

template<typename type>
type vec3<type>::Length()
{
    return sqrt(x * x + y*y + z*z);
}

template<typename type>
type vec3<type>::Distance(vec3 rhs)
{
    return vec3(x - rhs.x, y - rhs.y, z - rhs.z).Length();
}


template<typename type>
vec3<type> vec3<type>::operator+=(vec3 rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

template<typename type>
vec3<type> vec3<type>::operator-=(vec3 rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

template<typename type>
vec3<type> vec3<type>::operator*=(vec3 rhs)
{
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    return *this;
}

template<typename type>
vec3<type> vec3<type>::operator/=(type rhs)
{
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return *this;
}

template<typename type>
vec3<type> vec3<type>::operator*=(type rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
}

template<typename type>
vec3<type> vec3<type>::Cross(vec3 rhs)
{
    return vec3(y * rhs.z - z * rhs.y,
        z * rhs.x - x *rhs.z,
        x * rhs.y - y * rhs.x);
}

using vec3f = vec3 < float >;
using vec3i = vec3 < int >;
using vec3s = vec3 < short >;
using vec3b = vec3 < char >;
using vec3d = vec3 < double >;


#endif