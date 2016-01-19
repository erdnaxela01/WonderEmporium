#ifndef __MAT_4_H
#define __MAT_4_H

#include "vec3.h"
#include "vec4.h"
#include <cassert>


//matrix class that can be used for nefarious purposes
template<typename type>
struct mat4
{
    type m00;
    type m01;
    type m02;
    type m03;
    type m10;
    type m11;
    type m12;
    type m13;
    type m20;
    type m21;
    type m22;
    type m23;
    type m30;
    type m31;
    type m32;
    type m33;

	mat4();
    mat4(type fill[4][4]);
    mat4(type angular);
    mat4(type fill[16]);

    mat4 operator*(const mat4& lhs);
    mat4 operator*=(const mat4& lhs);
    mat4 operator+(const mat4& lhs);
    mat4 operator+=(const mat4& lhs);
    mat4 operator-(const mat4& lhs);
    mat4 operator-=(const mat4& lhs);
    mat4 operator*(type lhs);
    mat4 operator*=(type lhs);
    mat4 operator/(type lhs);
    mat4 operator/=(type lhs);

	vec4<type> operator*(vec4<type>);

    mat4 Transpose();

    type* GetArray();

    static void Identity(mat4*);
    static void Translation(vec3<type> transpose, mat4* output, mat4* inverse = nullptr);
    static void RotationX(float radAngle, mat4* output, mat4* inverse = nullptr);
    static void RotationY(float radAngle, mat4* output, mat4* inverse = nullptr);
    static void RotationZ(float radAngle, mat4* output, mat4* inverse = nullptr);
    static void Scale(vec3<type> scaling, mat4* output, mat4* inverse = nullptr);
    static void Inverse(vec3<type> transpose, float xRotate, float yRotate, float zRotate, vec3<type> scale, mat4* inverse);
    static void Transform(vec3<type> transpose, float xRotate, float yRotate, float zRotate, vec3<type> scale, mat4* output, mat4* inverse = nullptr);
    static void Frustum(type aspect, type nearZ, type farZ, type fov, mat4* output, bool leftHanded = true);
    static void Ortho2D(type left, type right, type bottom, type top, type near, type far, mat4* output);

};

template<typename type>
mat4<type>::mat4()
{
	Identity(this);
}

template<typename type>
mat4<type>::mat4(type fill[4][4])
{
    m00 = fill[0][0];
    m01 = fill[0][1];
    m02 = fill[0][2];
    m03 = fill[0][3];
    m10 = fill[1][0];
    m11 = fill[1][1];
    m12 = fill[1][2];
    m13 = fill[1][3];
    m20 = fill[2][0];
    m21 = fill[2][1];
    m22 = fill[2][2];
    m23 = fill[2][3];
    m30 = fill[3][0];
    m31 = fill[3][1];
    m32 = fill[3][2];
    m33 = fill[3][3];
}

template<typename type>
mat4<type>::mat4(type angular)
{
    m00 = angular;
    m01 = 0;
    m02 = 0;
    m03 = 0;
    m10 = 0;
    m11 = angular;
    m12 = 0;
    m13 = 0;
    m20 = 0;
    m21 = 0;
    m22 = angular;
    m23 = 0;
    m30 = 0;
    m31 = 0;
    m32 = 0;
    m33 = angular;
}

template<typename type>
mat4<type>::mat4(type fill[16])
{
    m00 = fill[0];
    m01 = fill[1];
    m02 = fill[2];
    m03 = fill[3];
    m10 = fill[4];
    m11 = fill[5];
    m12 = fill[6];
    m13 = fill[7];
    m20 = fill[8];
    m21 = fill[9];
    m22 = fill[10];
    m23 = fill[11];
    m30 = fill[12];
    m31 = fill[13];
    v32 = fill[14];
    m33 = fill[15];
}

template<typename type>
mat4<type> mat4<type>::operator*(const mat4& lhs)
{
    mat4<type> temp;
    temp.m00 = m00 * lhs.m00 + m10 * lhs.m01 + m20 * lhs.m02 + m30 * lhs.m03;
    temp.m10 = m00 * lhs.m10 + m10 * lhs.m11 + m20 * lhs.m12 + m30 * lhs.m13;
    temp.m20 = m00 * lhs.m20 + m10 * lhs.m21 + m20 * lhs.m22 + m30 * lhs.m23;
    temp.m30 = m00 * lhs.m30 + m10 * lhs.m31 + m20 * lhs.m32 + m30 * lhs.m33;

    temp.m01 = m01 * lhs.m00 + m11 * lhs.m01 + m21 * lhs.m02 + m31 * lhs.m03;
    temp.m11 = m01 * lhs.m10 + m11 * lhs.m11 + m21 * lhs.m12 + m31 * lhs.m13;
    temp.m21 = m01 * lhs.m20 + m11 * lhs.m21 + m21 * lhs.m22 + m31 * lhs.m23;
    temp.m31 = m01 * lhs.m30 + m11 * lhs.m31 + m21 * lhs.m32 + m31 * lhs.m33;

    temp.m02 = m02 * lhs.m00 + m12 * lhs.m01 + m22 * lhs.m02 + m32 * lhs.m03;
    temp.m12 = m02 * lhs.m10 + m12 * lhs.m11 + m22 * lhs.m12 + m32 * lhs.m13;
    temp.m22 = m02 * lhs.m20 + m12 * lhs.m21 + m22 * lhs.m22 + m32 * lhs.m23;
    temp.m32 = m02 * lhs.m30 + m12 * lhs.m31 + m22 * lhs.m32 + m32 * lhs.m33;

    temp.m03 = m03 * lhs.m00 + m13 * lhs.m01 + m23 * lhs.m02 + m33 * lhs.m03;
    temp.m13 = m03 * lhs.m10 + m13 * lhs.m11 + m23 * lhs.m12 + m33 * lhs.m13;
    temp.m23 = m03 * lhs.m20 + m13 * lhs.m21 + m23 * lhs.m22 + m33 * lhs.m23;
    temp.m33 = m03 * lhs.m30 + m13 * lhs.m31 + m23 * lhs.m32 + m33 * lhs.m33;

    return temp;
}

template<typename type>
mat4<type> mat4<type>::operator*=(const mat4& lhs)
{
    mat4<type> temp;
    temp = (*this) * lhs;
    
    (*this) = temp;
    return temp;
}

template<typename type>
mat4<type> mat4<type>::operator+(const mat4& lhs)
{
    mat4<type> temp;
    temp.m00 = m00 + lhs.m00;
    temp.m01 = m01 + lhs.m01;
    temp.m02 = m02 + lhs.m02;
    temp.m03 = m03 + lhs.m03;
    temp.m10 = m10 + lhs.m10;
    temp.m11 = m11 + lhs.m11;
    temp.m12 = m12 + lhs.m12;
    temp.m13 = m13 + lhs.m13;
    temp.m20 = m20 + lhs.m20;
    temp.m21 = m21 + lhs.m21;
    temp.m22 = m22 + lhs.m22;
    temp.m23 = m23 + lhs.m23;
    temp.m30 = m30 + lhs.m30;
    temp.m31 = m31 + lhs.m31;
    temp.m32 = m32 + lhs.m32;
    temp.m33 = m33 + lhs.m33;
    return temp;
}

template<typename type>
mat4<type> mat4<type>::operator+=(const mat4& lhs)
{
    m00 += lhs.m00;
    m01 += lhs.m01;
    m02 += lhs.m02;
    m03 += lhs.m03;
    m10 += lhs.m10;
    m11 += lhs.m11;
    m12 += lhs.m12;
    m13 += lhs.m13;
    m20 += lhs.m20;
    m21 += lhs.m21;
    m22 += lhs.m22;
    m23 += lhs.m23;
    m30 += lhs.m30;
    m31 += lhs.m31;
    m32 += lhs.m32;
    m33 += lhs.m33;
    return (*this);
}

template<typename type>
mat4<type> mat4<type>::operator-(const mat4& lhs)
{
    mat4<type> temp;
    temp.m00 = m00 - lhs.m00;
    temp.m01 = m01 - lhs.m01;
    temp.m02 = m02 - lhs.m02;
    temp.m03 = m03 - lhs.m03;
    temp.m10 = m10 - lhs.m10;
    temp.m11 = m11 - lhs.m11;
    temp.m12 = m12 - lhs.m12;
    temp.m13 = m13 - lhs.m13;
    temp.m20 = m20 - lhs.m20;
    temp.m21 = m21 - lhs.m21;
    temp.m22 = m22 - lhs.m22;
    temp.m23 = m23 - lhs.m23;
    temp.m30 = m30 - lhs.m30;
    temp.m31 = m31 - lhs.m31;
    temp.m32 = m32 - lhs.m32;
    temp.m33 = m33 - lhs.m33;
    return temp;
}

template<typename type>
mat4<type> mat4<type>::operator-=(const mat4& lhs)
{
    m00 -= lhs.v00;
    m01 -= lhs.m01;
    m02 -= lhs.m02;
    m03 -= lhs.m03;
    m10 -= lhs.m10;
    m11 -= lhs.m11;
    m12 -= lhs.m12;
    m13 -= lhs.m13;
    m20 -= lhs.m20;
    m21 -= lhs.m21;
    m22 -= lhs.m22;
    m23 -= lhs.m23;
    m30 -= lhs.m30;
    m31 -= lhs.m31;
    m32 -= lhs.m32;
    m33 -= lhs.m33;
    return (*this);
}

template<typename type>
mat4<type> mat4<type>::operator*(type lhs)
{
    mat4<type> temp;
    temp.m00 = m00 * lhs;
    temp.m01 = m01 * lhs;
    temp.m02 = m02 * lhs;
    temp.m03 = m03 * lhs;
    temp.m10 = m10 * lhs;
    temp.m11 = m11 * lhs;
    temp.m12 = m12 * lhs;
    temp.m13 = m13 * lhs;
    temp.m20 = m20 * lhs;
    temp.m21 = m21 * lhs;
    temp.m22 = m22 * lhs;
    temp.m23 = m23 * lhs;
    temp.m30 = m30 * lhs;
    temp.m31 = m31 * lhs;
    temp.m32 = m32 * lhs;
    temp.m33 = m33 * lhs;
    return temp;
}


template<typename type>
mat4<type> mat4<type>::operator*=(type lhs)
{
    m00 *= lhs;
    m01 *= lhs;
    m02 *= lhs;
    m03 *= lhs;
    m10 *= lhs;
    m11 *= lhs;
    m12 *= lhs;
    m13 *= lhs;
    m20 *= lhs;
    m21 *= lhs;
    m22 *= lhs;
    m23 *= lhs;
    m30 *= lhs;
    m31 *= lhs;
    m32 *= lhs;
    m33 *= lhs;
    return (*this);
}

template<typename type>
mat4<type> mat4<type>::operator/(type lhs)
{
    mat4<type> temp;
    temp.m00 = v00 / lhs;
    temp.m01 = m01 / lhs;
    temp.m02 = m02 / lhs;
    temp.m03 = m03 / lhs;
    temp.m10 = m10 / lhs;
    temp.m11 = m11 / lhs;
    temp.m12 = m12 / lhs;
    temp.m13 = m13 / lhs;
    temp.m20 = m20 / lhs;
    temp.m21 = m21 / lhs;
    temp.m22 = m22 / lhs;
    temp.m23 = m23 / lhs;
    temp.m30 = m30 / lhs;
    temp.m31 = m31 / lhs;
    temp.m32 = m32 / lhs;
    temp.m33 = m33 / lhs;
    return temp;
}

template<typename type>
mat4<type> mat4<type>::operator/=(type lhs)
{
    m00 /= lhs;
    m01 /= lhs;
    m02 /= lhs;
    m03 /= lhs;
    m10 /= lhs;
    m11 /= lhs;
    m12 /= lhs;
    m13 /= lhs;
    m20 /= lhs;
    m21 /= lhs;
    m22 /= lhs;
    m23 /= lhs;
    m30 /= lhs;
    m31 /= lhs;
    m32 /= lhs;
    m33 /= lhs;
    return (*this);
}

static float arr[16];

template<typename type>
type* mat4<type>::GetArray()
{
    arr[0] = m00;
    arr[1] = m01;
    arr[2] = m02;
    arr[3] = m03;
    arr[4] = m10;
    arr[5] = m11;
    arr[6] = m12;
    arr[7] = m13;
    arr[8] = m20;
    arr[9] = m21;
    arr[10] = m22;
    arr[11] = m23;
    arr[12] = m30;
    arr[13] = m31;
    arr[14] = m32;
    arr[15] = m33;
    return arr;

}

template<typename type>
mat4<type> mat4<type>::Transpose()
{
	mat4<type> temp = *this;
	std::swap(temp.m01, temp.m10);
	std::swap(temp.m02, temp.m20);
	std::swap(temp.m03, temp.m30);

	std::swap(temp.m12, temp.m21);

	std::swap(temp.m13, temp.m31);
	std::swap(temp.m23, temp.m32);

	return temp;
}

template<typename type>
void mat4<type>::Identity(mat4* output)
{
    output->m00 = 1;
    output->m01 = 0;
    output->m02 = 0;
    output->m03 = 0;
    output->m10 = 0;
    output->m11 = 1;
    output->m12 = 0;
    output->m13 = 0;
    output->m20 = 0;
    output->m21 = 0;
    output->m22 = 1;
    output->m23 = 0;
    output->m30 = 0;
    output->m31 = 0;
    output->m32 = 0;
    output->m33 = 1;
}

template<typename type>
void mat4<type>::Translation(vec3<type> transpose, mat4* output, mat4* inverse)
{
    Identity(output);

    output->m30 = transpose.x;
    output->m31 = transpose.y;
    output->m32 = transpose.z;

    if (inverse != nullptr)
    {
		Identity(inverse);
        inverse->m30 = -transpose.x;
        inverse->m31 = -transpose.y;
        inverse->m32 = -transpose.z;
    }
}

template<typename type>
void mat4<type>::RotationX(float radAngle, mat4* output, mat4* inverse)
{
    Identity(output);

	mat4<type> temp;

	temp.m11 = cos(radAngle);
	temp.m22 = cos(radAngle);
	temp.m21 = -sin(radAngle);
	temp.m12 = sin(radAngle);

	*output = temp;

    if (inverse != nullptr)
    {
		Identity(inverse);
        (*inverse) = temp.Transpose();
    }
}

template<typename type>
void mat4<type>::RotationY(float radAngle, mat4* output, mat4* inverse)
{
    Identity(output);

	mat4<type> temp;

	temp.m00 = cos(radAngle);
	temp.m22 = cos(radAngle);
	temp.m02 = -sin(radAngle);
	temp.m20 = sin(radAngle);

	*output = temp;

    if (inverse != nullptr)
    {
		Identity(inverse);
        (*inverse) = temp.Transpose();
    }
}

template<typename type>
void mat4<type>::RotationZ(float radAngle, mat4* output, mat4* inverse)
{
    Identity(output);

	mat4<type> temp;

    temp.m00 = cos(radAngle);
	temp.m11 = cos(radAngle);
	temp.m10 = -sin(radAngle);
	temp.m01 = sin(radAngle);

	(*output) = temp;

    if (inverse != nullptr)
    {
		Identity(inverse);
        (*inverse) = temp.Transpose();
    }
}

template<typename type>
void mat4<type>::Scale(vec3<type> scaling, mat4* output, mat4* inverse)
{
    Identity(output);

    output->m00 = scaling.x;
	output->m11 = scaling.y;
	output->m22 = scaling.z;

    if (inverse != nullptr)
    {
		Identity(inverse);
		inverse->m00 = 1.0 / scaling.x;
		inverse->m11 = 1.0 / scaling.y;
		inverse->m22 = 1.0 / scaling.z;
    }
}

template<typename type>
void mat4<type>::Inverse(vec3<type> transpose, float xRotate, float yRotate, float zRotate, vec3<type> scale, mat4* inverse)
{
    mat4<type> temp;

    Identity(inverse);

	Scale(scale, &temp, &temp);
	(*inverse) *= temp;

	RotationZ(zRotate, &temp, &temp);
	(*inverse) *= temp;

	RotationY(yRotate, &temp, &temp);
	(*inverse) *= temp;

	RotationX(xRotate, &temp, &temp);
	(*inverse) *= temp;

	Translation(transpose, &temp, &temp);
	(*inverse) *= temp;

}

template<typename type>
void mat4<type>::Transform(vec3<type> transpose, float xRotate, float yRotate, float zRotate, vec3<type> scale, mat4* output, mat4* inverse)
{
    mat4<type> temp;

    Identity(output);

	Translation(transpose, &temp);
	(*output) *= temp;

	RotationX(xRotate, &temp);
	(*output) *= temp;

	RotationY(yRotate, &temp);
	(*output) *= temp;

	RotationZ(zRotate, &temp);
	(*output) *= temp;

	Scale(scale, &temp);
	(*output) *= temp;


    if (inverse != nullptr)
    {
		Identity(inverse);
		Inverse(transpose, xRotate, yRotate, zRotate, scale, inverse);
    }
}

template<typename type>
void mat4<type>::Frustum(type aspect, type nearZ, type farZ, type fov, mat4* output, bool leftHanded)
{
	
	assert(nearZ != farZ);
	assert(output != nullptr);

    Identity(output);

	type c = ((-farZ * nearZ)) / (farZ - nearZ);
	type d = (( farZ) / (farZ - nearZ));

	output->m11 =  1 / tan(0.5 * fov);
	output->m00 = (leftHanded ? -1 : 1)* output->m11 / aspect;
	output->m22 = d;
	output->m32 = c;
	output->m23 =  1;
	output->m33 = 0.0;
}

template<typename type>
void mat4<type>::Ortho2D(type left, type right, type bottom, type top, type near, type far, mat4* output)
{
    Identity(output);

    output->m00 = 2.0 / (right - left);
    output->m11 = 2.0 / (top - bottom);
    output->m22 = 2.0 / (far - near);
	output->m30 = -((right + left) / (right - left));
	output->m31 = -((top + bottom) / (top - bottom));
	output->m32 = -((far + near) / (far - near));
}

template<typename type>
vec4<type> mat4<type>::operator*(vec4<type> v)
{
	vec4<type> temp;
	temp.x = m00 * v.x + m10 * v.y + m20 * v.z + m30 * v.w;
	temp.y = m01 * v.x + m11 * v.y + m21 * v.z + m31 * v.w;
	temp.z = m02 * v.x + m12 * v.y + m22 * v.z + m32 * v.w;
	temp.w = m03 * v.x + m13 * v.y + m23 * v.z + m33 * v.w;

	return temp;
}

using mat4f = mat4 < float > ;
using mat4i = mat4 < int > ;
using mat4d = mat4 < double > ;

#endif