#ifndef __VEC4_H
#define __VEC4_H


template<typename type>
struct vec4
{
	type x;
	type y;
	type z;
	type w;

	//structor
	vec4();
	vec4(type tx, type ty, type tz, type tw);

	//Math operatrions
	vec4 operator+(vec4 rhs);
	vec4 operator-(vec4 rhs);
	vec4 operator*(vec4 rhs);
	vec4 operator/(type rhs);
	vec4 operator*(type rhs);
	vec4 operator+=(vec4 rhs);
	vec4 operator-=(vec4 rhs);
	vec4 operator*=(vec4 rhs);
	vec4 operator/=(type rhs);
	vec4 operator*=(type rhs);
	//returns the normalized vector
	vec4 Normalized();
	//returns the dot product between it an two vectors
	type Dot(vec4 rhs);

	//returns the length of the vector
	type Length();

	//returns the distance between this vector and another
	type Distance(vec4 rhs);

};

//structor
template<typename type>
vec4<type>::vec4() :x(0.0), y(0.0), z(0.0), w(1.0)
{
}

template<typename type>
vec4<type>::vec4(type tx, type ty, type tz, type tw) : x(tx), y(ty), z(tz), w(tw)
{

}

//Math operatrions
template<typename type>
vec4<type> vec4<type>::operator+(vec4 rhs)
{
	return vec4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

template<typename type>
vec4<type> vec4<type>::operator-(vec4 rhs)
{
	return vec4(x - rhs.x, y - rhs.y, z - rhs.z, w = rhs.w);
}

template<typename type>
vec4<type> vec4<type>::operator*(vec4 rhs)
{
	return vec4(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
}

template<typename type>
vec4<type> vec4<type>::operator/(type rhs)
{
	return vec4(x / rhs, y / rhs, z / rhs, w/ rhs);
}

template<typename type>
vec4<type> vec4<type>::operator*(type rhs)
{
	return vec4(x * rhs, y * rhs, z*rhs, w*rhs);
}

template<typename type>
vec4<type> vec4<type>::Normalized()
{
	float length = Length();
	return vec4(x / length, y / length, z / length, w/length);
}

template<typename type>
type vec4<type>::Dot(vec4 rhs)
{
	return (x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w);
}

template<typename type>
type vec4<type>::Length()
{
	return sqrt(x * x + y*y + z*z + w*w);
}

template<typename type>
type vec4<type>::Distance(vec4 rhs)
{
	return vec4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w).Length();
}


template<typename type>
vec4<type> vec4<type>::operator+=(vec4 rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	w += rhs.w;
	return *this;
}

template<typename type>
vec4<type> vec4<type>::operator-=(vec4 rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	w -= rhs.w;
	return *this;
}

template<typename type>
vec4<type> vec4<type>::operator*=(vec4 rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;
	w *= rhs.w;
	return *this;
}

template<typename type>
vec4<type> vec4<type>::operator/=(type rhs)
{
	x /= rhs;
	y /= rhs;
	z /= rhs;
	w /= rhs;
	return *this;
}

template<typename type>
vec4<type> vec4<type>::operator*=(type rhs)
{
	x *= rhs;
	y *= rhs;
	z *= rhs;
	w *= rhs;
	return *this;
}



using vec4f = vec4 < float >;
using vec4i = vec4 < int >;
using vec4s = vec4 < short >;
using vec4b = vec4 < char >;
using vec4d = vec4 < double >;


#endif