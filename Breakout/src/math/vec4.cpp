#include "vec4.h"

vec4::vec4()
{
	this->x = this->y = this->z = this->w = 0.0f;
}

vec4::vec4(float v)
{
	this->x = this->y = this->z = this->w = v;
}

vec4::vec4(float x, float y, float z, float w)
{
	this->x = x, this->y = y, this->z = z, this->w = w;
}

vec4& vec4::operator+=(const vec4& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;

	return *this;
}

vec4& vec4::operator-=(const vec4& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	w -= other.w;

	return *this;
}

vec4& vec4::operator*=(const vec4 & other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
	w *= other.w;

	return *this;
}

vec4& vec4::operator/=(const vec4& other)
{
	x /= other.x;
	y /= other.y;
	z /= other.z;
	w /= other.w;

	return *this;
}

std::ostream& operator<<(std::ostream& stream, const vec4& vec)
{
	stream << "vec4: (" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ')';
	return stream;
}