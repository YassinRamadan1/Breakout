#pragma once

#include <iostream>
#include <cmath>

struct vec3
{
	union
	{
		struct { float x, y, z; };
		struct { float s, t, p; };
		struct { float r, g, b; };
	};

	vec3();
	vec3(float v);
	vec3(float x, const float y, const float z);
	vec3& operator+=(const vec3& other);
	vec3& operator-=(const vec3& other);
	vec3& operator*=(const vec3& other);
	vec3& operator/=(const vec3& other);

	friend std::ostream& operator<<(std::ostream& stream, const vec3& vec);
};

inline float dot(const vec3& left, const vec3& right)
{
	return left.x * right.x + left.y * right.y + left.z * right.z;
}

inline vec3 cross(const vec3& left, const vec3& right)
{
	return vec3(left.y * right.z - right.y * left.z, left.z * right.x - right.z * left.x, left.x * right.y - right.x * left.y);
}

inline float length2(const vec3& vector)
{
	return dot(vector, vector);
}

inline float length(const vec3& vector)
{
	return sqrt(length2(vector));
}

inline vec3 operator+(vec3 left, const vec3& right)
{
	return left += right;
}

inline vec3 operator+(vec3 left, const float& right)
{
	return left + vec3(right);
}

inline vec3 operator+(const float& left, vec3 right)
{
	return right + left;
}

inline vec3 operator-(vec3 left, const vec3& right)
{
	return left -= right;
}

inline vec3 operator-(vec3 left, const float& right)
{
	return left - vec3(right);
}

inline vec3 operator-(const float& left, vec3 right)
{
	return right - left;
}

inline vec3 operator*(vec3 left, const vec3& right)
{
	return left *= right;
}

inline vec3 operator*(vec3 left, const float& right)
{
	return left * vec3(right);
}

inline vec3 operator*(const float& left, vec3 right)
{
	return right * left;
}
		
inline vec3 operator/(vec3 left, const vec3& right)
{
	return left /= right;
}

inline vec3 operator/(vec3 left, const float& right)
{
	return left / vec3(right);
}

inline vec3 operator/(const float& left, vec3 right)
{
	return right / left;
}

inline vec3 normalize(const vec3& vector)
{
	return vector / length(vector);
}