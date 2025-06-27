#pragma once
#include <cmath>
#include "vec3.h"
#include "vec4.h"

#define PI 3.14159265358979323846f

inline float radians(float angle)
{
	return angle * PI / 180.0;
}

inline float degrees(float angle)
{
	return angle * 180.0 / PI;
}

struct mat4
{
	union 
	{
		struct { float data[16]; };
		struct { vec4 columns[4]; };
	};
	mat4();
	mat4(float v);
	mat4(const vec4& column1, const vec4& column2, const vec4& column3, const vec4& column4);
	
	mat4& operator *=(const mat4& other);
};

inline mat4 operator *(mat4 left, const mat4& right)
{
	return left *= right;
}

inline vec4 operator *(const mat4& left, const vec4& right)
{
	return vec4(
		dot(vec4(left.data[0], left.data[4], left.data[8], left.data[12]), right),
		dot(vec4(left.data[1], left.data[5], left.data[9], left.data[13]), right),
		dot(vec4(left.data[2], left.data[6], left.data[10], left.data[14]), right),
		dot(vec4(left.data[3], left.data[7], left.data[11], left.data[15]), right)
	);
}

inline vec3 operator *(const mat4& left, const vec3& right)
{
	return vec3(
		dot(vec3(left.data[0], left.data[4], left.data[8]), right) + left.data[12],
		dot(vec3(left.data[1], left.data[5], left.data[9]), right) + left.data[13],
		dot(vec3(left.data[2], left.data[6], left.data[10]), right) + left.data[14]
	);
}

inline mat4 transpose(const mat4& matrix)
{
	mat4 mat;
	mat.data[1] = matrix.data[4], mat.data[2] = matrix.data[8], mat.data[3] = matrix.data[12];
	mat.data[4] = matrix.data[1], mat.data[6] = matrix.data[9], mat.data[7] = matrix.data[13];
	mat.data[8] = matrix.data[2], mat.data[9] = matrix.data[6], mat.data[11] = matrix.data[14];
	mat.data[12] = matrix.data[3], mat.data[13] = matrix.data[7], mat.data[14] = matrix.data[11];
	return mat;
}

inline mat4 inverse(const mat4& matrix)
{

}

inline mat4 translate(const vec3& translation_vector)
{
	mat4 mat(1.0f);
	mat.data[12] = translation_vector.x;
	mat.data[13] = translation_vector.y;
	mat.data[14] = translation_vector.z;
	return mat;
}

inline mat4 rotate(float angle, const vec3& axis)
{
	vec3 normalized_axis = normalize(axis);
	float c = cos(angle), s = sin(angle), omc = 1.0f - c;
	mat4 mat(1.0f);

	mat.data[0] = c + normalized_axis.x * normalized_axis.x * omc;
	mat.data[1] = normalized_axis.y * normalized_axis.x * omc + normalized_axis.z * s;
	mat.data[2] = normalized_axis.z * normalized_axis.x * omc - normalized_axis.y * s;
	
	mat.data[4] = normalized_axis.x * normalized_axis.y * omc - normalized_axis.z * s;
	mat.data[5] = c + normalized_axis.y * normalized_axis.y * omc;
	mat.data[6] = normalized_axis.z * normalized_axis.y * omc + normalized_axis.x * s;
	
	mat.data[8] = normalized_axis.x * normalized_axis.z * omc + normalized_axis.y * s;
	mat.data[9] = normalized_axis.y * normalized_axis.z * omc - normalized_axis.x * s;
	mat.data[10] = c + normalized_axis.z * normalized_axis.z * omc;

	return mat;
}

inline mat4 scale(const vec3& scaling_vector)
{
	mat4 mat(1.0f);
	mat.data[0] = scaling_vector.x;
	mat.data[5] = scaling_vector.y;
	mat.data[10] = scaling_vector.z;
	return mat;
}

inline mat4 orthographic(float left, float right, float bottom, float top, float near, float far)
{
	mat4 mat(1.0f);
	mat.data[0] = 2.0 / (right - left), mat.data[1] = 0, mat.data[2] = 0;
	mat.data[4] = 0, mat.data[5] = 2.0 / (top - bottom), mat.data[6] = 0;
	mat.data[8] = 0, mat.data[9] = 0, mat.data[10] = 2.0 / (near - far);
	mat.data[12] = -(right + left) / (right - left), mat.data[13] = -(top + bottom) / (top - bottom), mat.data[14] = (near + far) / (near - far);
	return mat;
}

inline mat4 perspective(float fovy, float aspect_ratio, float near, float far)
{
	mat4 mat;
	mat.data[0] = 1.0 / (aspect_ratio * tan(fovy / 2.0f));
	mat.data[5] = aspect_ratio * mat.data[0];
	mat.data[10] = (near + far) / (near - far);
	mat.data[11] = -1;
	mat.data[14] = (2 * near * far) / (near - far);
	return mat;
}

inline mat4 lookAt(vec3 center_of_projection, vec3 target, vec3 world_up)
{
	vec3 front = target - center_of_projection;
	front = normalize(front);
	vec3 right = normalize(cross(front, world_up));
	vec3 up = cross(right, front);
	mat4 mat(1.0f);
	
	mat.data[0] = right.x, mat.data[1] = up.x, mat.data[2] = -front.x;
	
	mat.data[4] = right.y, mat.data[5] = up.y, mat.data[6] = -front.y;
	
	mat.data[8] = right.z, mat.data[9] = up.z, mat.data[10] = -front.z;

	mat.data[12] = -dot(right, center_of_projection), mat.data[13] = -dot(up, center_of_projection), mat.data[14] = dot(front, center_of_projection);
	return mat;
}