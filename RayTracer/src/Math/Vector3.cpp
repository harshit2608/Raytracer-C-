#include "rtpch.h"

#include "Math/Vector3.h"

namespace RayT
{

	Vector3::Vector3()
		: x(0.0), y(0.0), z(0.0)
	{
	}

	Vector3::Vector3(double X, double Y, double Z)
		: x(X), y(Y), z(Z)
	{
	}

	Vector3::Vector3(const Vector3 &v)
		: x(v.x), y(v.y), z(v.z)
	{
	}

	RayT::Vector3 Vector3::operator+(const Vector3 &v) const
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	RayT::Vector3 Vector3::operator-(const Vector3 &v) const
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	void Vector3::operator/=(const double s)
	{
		x = x / s;
		y = y / s;
		z = z / s;
	}

	void Vector3::operator%=(const Vector3 &v)
	{
		*this = cross(v);
	}

	RayT::Vector3 Vector3::operator*(const double s) const
	{
		return Vector3(x / s, y / s, z / s);
	}

	double Vector3::operator*(const Vector3 &v) const
	{
		return x * v.x + y * v.y + z * v.z;
	}

	double Vector3::dot(const Vector3 &v) const
	{
		return x * v.x + y * v.y + z * v.z;
	}

	RayT::Vector3 Vector3::cross(const Vector3 &v) const
	{
		return Vector3(y * v.z - z * v.y,
					   z * v.x - x * v.z,
					   x * v.y - y * v.x);
	}

	void Vector3::conjugate()
	{
		x = -1 * x;
		y = -1 * y;
		z = -1 * z;
	}

	void Vector3::normalize()
	{
		float mag = std::sqrt(x * x + y * y + z * z);

		if (mag > 0.0f)
		{

			//normalize it
			float oneOverMag = 1.0f / mag;

			x = x * oneOverMag;
			y = y * oneOverMag;
			z = z * oneOverMag;
		}
	}

	double Vector3::magnitude()
	{
		float magnitude = std::sqrt(x * x + y * y + z * z);

		return magnitude;
	}

	double Vector3::magnitudeSquare()
	{
		float magnitude = x * x + y * y + z * z;

		return magnitude;
	}

	RayT::Vector3 Vector3::unitVector(Vector3 v)
	{
		return v / v.magnitude();
	}

	void Vector3::zero()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	void Vector3::absolute()
	{
		x = std::abs(x);
		y = std::abs(y);
		z = std::abs(z);
	}

	void Vector3::show()
	{
		std::cout << "(" << x << "," << y << "," << z << ")" << std::endl;
	}

	void Vector3::negate()
	{
		x = -1 * x;
		y = -1 * y;
		z = -1 * z;
	}

	RayT::Vector3 Vector3::operator/(const double s) const
	{
		return Vector3(x / s, y / s, z / s);
	}

	RayT::Vector3 Vector3::operator%(const Vector3 &v) const
	{
		return Vector3(y * v.z - z * v.y,
					   z * v.x - x * v.z,
					   x * v.y - y * v.x);
	}

	void Vector3::operator*=(const double s)
	{
		x *= s;
		y *= s;
		z *= s;
	}

	void Vector3::operator-=(const Vector3 &v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
	}

	void Vector3::operator+=(const Vector3 &v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
	}

	RayT::Vector3 &Vector3::operator=(const Vector3 &v)
	{
		x = v.x;
		y = v.y;
		z = v.z;

		return *this;
	}

	Vector3::~Vector3()
	{
	}

}