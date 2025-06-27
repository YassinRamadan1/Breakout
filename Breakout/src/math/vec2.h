#pragma once

#include <iostream>
#include <cmath>

struct vec2
{
	union
	{
		struct { float x, y; };
		struct { float s, t; };
		struct { float r, g; };
	};

	vec2();
	vec2(float v);
	vec2(float x, float y);
	vec2& operator+=(const vec2& other);
	vec2& operator-=(const vec2& other);
	vec2& operator*=(const vec2& other);
	vec2& operator/=(const vec2& other);

	friend std::ostream& operator<<(std::ostream& stream, const vec2& vec);
};

inline float dot(const vec2& left, const vec2& right)
{
	return left.x * right.x + left.y * right.y;
}

inline float length2(const vec2& vector)
{
	return dot(vector, vector);
}

inline float length(const vec2& vector)
{
	return sqrt(length2(vector));
}

inline vec2 operator+(vec2 left, const vec2& right)
{
	return left += right;
}

inline vec2 operator+(vec2 left, const float& right)
{
	return left + vec2(right);
}

inline vec2 operator+(const float& left, vec2 right)
{
	return right + left;
}

inline vec2 operator-(vec2 left, const vec2& right)
{
	return left -= right;
}

inline vec2 operator-(vec2 left, const float& right)
{
	return left - vec2(right);
}

inline vec2 operator-(const float& left, vec2 right)
{
	return right - left;
}

inline vec2 operator*(vec2 left, const vec2& right)
{
	return left *= right;
}

inline vec2 operator*(vec2 left, const float& right)
{
	return left * vec2(right);
}

inline vec2 operator*(const float& left, vec2 right)
{
	return right * left;
}
		
inline vec2 operator/(vec2 left, const vec2& right)
{
	return left /= right;
}

inline vec2 operator/(vec2 left, const float& right)
{
	return left / vec2(right);
}

inline vec2 operator/(const float& left, vec2 right)
{
	return right / left;
}

inline vec2 normalize(const vec2& vector)
{
	return vector / length(vector);
}