#ifndef __VEC2_H
#define __VEC2_H



/*
This class is used for math like positions and stuff
*/
template<typename type>
struct vec2
{
    type x;
    type y;

    //structor
    vec2();
    vec2(type tx, type ty);

    //Math operatrions
    vec2 operator+(vec2 rhs);
    vec2 operator-(vec2 rhs);
    vec2 operator*(vec2 rhs);
    vec2 operator/(type rhs);
    vec2 operator*(type rhs);
    vec2 operator+=(vec2 rhs);
    vec2 operator-=(vec2 rhs);
    vec2 operator*=(vec2 rhs);
    vec2 operator/=(type rhs);
    vec2 operator*=(type rhs);
    //returns the normalized vector
    vec2 Normalized();
    //returns the dot product between it an two vectors
    type Dot(vec2 rhs);
        
    //returns the length of the vector
    type Length();

    //returns the distance between this vector and another
    type Distance(vec2 rhs);

		
};


//structor
template<typename type>
vec2<type>::vec2() :x(0.0f), y(0.0f)
{
}

template<typename type>
vec2<type>::vec2(type tx, type ty) : x(tx), y(ty)
{

}

template<typename type>
vec2<type> vec2<type>::operator+(vec2 rhs)
{
    return vec2(x + rhs.x, y + rhs.y);
}

template<typename type>
vec2<type> vec2<type>::operator-(vec2 rhs)
{
    return vec2(x - rhs.x, y - rhs.y);
}

template<typename type>
vec2<type> vec2<type>::operator*(vec2 rhs)
{
    return vec2(x * rhs.x, y * rhs.y);
}

template<typename type>
vec2<type> vec2<type>::operator/(type rhs)
{
    return vec2(x / rhs, y / rhs);
}

template<typename type>
vec2<type> vec2<type>::operator*(type rhs)
{
    return vec2(x * rhs, y * rhs);
}

template<typename type>
vec2<type> vec2<type>::Normalized()
{
    float length = Length();
    return vec2(x / length, y / length);
}

template<typename type>
type vec2<type>::Dot(vec2 rhs)
{
    return (x * rhs.x + y * rhs.y);
}

template<typename type>
type vec2<type>::Length()
{
    return sqrt(x * x + y*y);
}

template<typename type>
type vec2<type>::Distance(vec2 rhs)
{
    return vec2(x - rhs.x, y - rhs.y).Length();
}

template<typename type>
vec2<type> vec2<type>::operator+=(vec2 rhs)
{
    x += rhs.x;
    y += rhs.y;
    return *this;
}

template<typename type>
vec2<type> vec2<type>::operator-=(vec2 rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

template<typename type>
vec2<type> vec2<type>::operator*=(vec2 rhs)
{
    x *= rhs.x;
    y *= rhs.y;
    return *this;
}

template<typename type>
vec2<type> vec2<type>::operator/=(type rhs)
{
    x /= rhs;
    y /= rhs;
    return *this;
}

template<typename type>
vec2<type> vec2<type>::operator*=(type rhs)
{
    x *= rhs;
    y *= rhs;
    return *this;
}

using vec2f = vec2 < float > ;
using vec2i = vec2 < int > ;
using vec2s = vec2 < short > ;
using vec2b = vec2 < char > ;
using vec2d = vec2 < double > ;


#endif //__VEC2_H