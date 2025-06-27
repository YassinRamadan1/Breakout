#include "vec3.h"

vec3::vec3()
{
	this->x = 0.0f, this->y = this->z = 0.0f;
}

vec3::vec3(float v)
{
	this->x = this->y = this->z = v;
}

vec3::vec3(float x, float y, float z)
{
	this->x = x, this->y = y, this->z = z;
}

vec3& vec3::operator+=(const vec3& other)
{
	x += other.x;
	y += other.y;
	z += other.z;

	return *this;
}

vec3& vec3::operator-=(const vec3& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;

	return *this;
}

vec3& vec3::operator*=(const vec3 & other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;

	return *this;
}

vec3& vec3::operator/=(const vec3& other)
{
	x /= other.x;
	y /= other.y;
	z /= other.z;

	return *this;
}

std::ostream& operator<<(std::ostream& stream, const vec3& vec)
{
	stream << "vec3: (" << vec.x << ", " << vec.y << ", " << vec.z << ')';
	return stream;
}