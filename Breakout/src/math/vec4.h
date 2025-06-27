#pragma once

#include <iostream>
#include <cmath>

struct vec4
{
	union
	{
		struct { float x, y, z, w; };
		struct { float s, t, p, q; };
		struct { float r, g, b, a; };
	};

	vec4();
	vec4(float v);
	vec4(float x, float y, float z, float w);
	vec4& operator+=(const vec4& other);
	vec4& operator-=(const vec4& other);
	vec4& operator*=(const vec4& other);
	vec4& operator/=(const vec4& other);

	friend std::ostream& operator<<(std::ostream& stream, const vec4& vec);
};

inline float dot(const vec4& left, const vec4& right)
{
	return left.x * right.x + left.y * right.y + left.z * right.z + left.w * right.w;
}

inline float length2(const vec4& vector)
{
	return dot(vector, vector);
}

inline float length(const vec4& vector)
{
	return sqrt(length2(vector));
}

inline vec4 operator+(vec4 left, const vec4& right)
{
	return left += right;
}

inline vec4 operator+(vec4 left, const float& right)
{
	return left + vec4(right);
}

inline vec4 operator+(const float& left, vec4 right)
{
	return right + left;
}

inline vec4 operator-(vec4 left, const vec4& right)
{
	return left -= right;
}

inline vec4 operator-(vec4 left, const float& right)
{
	return left - vec4(right);
}

inline vec4 operator-(const float& left, vec4 right)
{
	return right - left;
}

inline vec4 operator*(vec4 left, const vec4& right)
{
	return left *= right;
}

inline vec4 operator*(vec4 left, const float& right)
{
	return left * vec4(right);
}

inline vec4 operator*(const float& left, vec4 right)
{
	return right * left;
}
		
inline vec4 operator/(vec4 left, const vec4& right)
{
	return left /= right;
}

inline vec4 operator/(vec4 left, const float& right)
{
	return left / vec4(right);
}

inline vec4 operator/(const float& left, vec4 right)
{
	return right / left;
}

inline vec4 normalize(const vec4& vector)
{
	return vector / length(vector);
}