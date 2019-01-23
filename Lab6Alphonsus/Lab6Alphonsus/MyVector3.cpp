  /// <summary>
/// Vector 3 class
/// Alphonsus Aluya,
///
#include "MyVector3.h"
#include <string.h>
#define PI           3.14159265358979323846

/// <summary>
/// Default constructor set all 3 values to zero
/// </summary>
MyVector3::MyVector3() :
	x{ 0.0 },
	y{ 0.0 },
	z{ 0.0 }
{
}

/// <summary>
/// default destructor
/// nothing to release because we only have
/// primitive type data
/// </summary>
MyVector3::~MyVector3()
{
}

/// <summary>
/// 
/// </summary>
/// <returns>the vector as a string surrounded by square brackets and separated by commas</returns>
std::string MyVector3::toString()
{
	const std::string output = "[" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + "]";
	return output;	
}

MyVector3::MyVector3(double t_x, double t_y, double t_z)
{
	x = t_x;
	y = t_y;
	z = t_z;
}

/// <summary>
/// create a vector 3 from an sf::vector3f
/// </summary>
/// <param name="t_sfVector">input vector</param>
MyVector3::MyVector3(sf::Vector3f t_sfVector)
{
	x = static_cast<double>( t_sfVector.x);
	y = static_cast<double>(t_sfVector.y);
	z = static_cast<double>(t_sfVector.z);
}

MyVector3::MyVector3(sf::Vector3i t_sfVector)
{
	x = static_cast<double>(t_sfVector.x);
	y = static_cast<double>(t_sfVector.y);
	z = static_cast<double>(t_sfVector.z);
}

MyVector3::MyVector3(sf::Vector2i t_sfVector)
{
	x = static_cast<int>(t_sfVector.x);
	y = static_cast<int>(t_sfVector.y);
}

MyVector3::MyVector3(sf::Vector2u t_sfVector)
{
	x = static_cast<int>(t_sfVector.x);
	y = static_cast<int>(t_sfVector.y);
	z = 0;
}

MyVector3::MyVector3(sf::Vector2f t_sfVector)
{
	x = static_cast<int>(t_sfVector.x);
	y = static_cast<int>(t_sfVector.y);
	z = 0;
}

MyVector3::operator sf::Vector2u()
{
	return sf::Vector2u{};
}


MyVector3 MyVector3::operator+(const MyVector3 t_right) const
{
	sf::Vector3f vectorOne{};
	vectorOne.x = x + t_right.x;
	vectorOne.y = y + t_right.y;
	vectorOne.z = z + t_right.z;
	return vectorOne;
}

MyVector3 MyVector3::operator-(const MyVector3 t_right) const
{
	sf::Vector3f vectorOne{};
	vectorOne.x = x - t_right.x;
	vectorOne.y = y - t_right.y;
	vectorOne.z = z - t_right.z;
	return vectorOne;
}

MyVector3 MyVector3::operator*(const double t_scalar) const
{
	sf::Vector3f vectorOne{};
	vectorOne.x = x * t_scalar;
	vectorOne.y = y * t_scalar;
	vectorOne.z = z * t_scalar;
	return vectorOne;
}

MyVector3 MyVector3::operator/(const double t_divisor) const
{
	sf::Vector3f vectorOne{};
	vectorOne.x = x / t_divisor;
	vectorOne.y = y / t_divisor;
	vectorOne.z = z / t_divisor;
	return vectorOne;
}

MyVector3 MyVector3::operator+=(const MyVector3 t_right)
{
	
	return MyVector3(x += t_right.x, y += t_right.y, z += t_right.z);
	
}

MyVector3 MyVector3::operator-=(const MyVector3 t_right)
{
	
	return MyVector3(x -= t_right.x, y -= t_right.y, z -= t_right.z);
}

bool MyVector3::operator==(const MyVector3 t_right) const
{
	sf::Vector3f vectorOne{};
	if (vectorOne.x == t_right.x && vectorOne.y == t_right.y && vectorOne.z == t_right.z)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MyVector3::operator!=(const MyVector3 t_right) const
{
	sf::Vector3f vectorOne{};
	if (vectorOne.x == t_right.x || vectorOne.y == t_right.y || vectorOne.z == t_right.z)
	{
		return true;
	}
	else
	{
		return false;
	}
}

MyVector3 MyVector3::operator-()
{
	MyVector3 x = -x, y = -y, z = -z;
	return MyVector3();
}

void MyVector3::reverseX()
{
	x = x * -1;
}

void MyVector3::reverseY()
{
	y = y * -1;
}

double MyVector3::length() const
{
	float sumOfSquares = (x * x) + (y * y) + (z * z);
	const float length = sqrt(sumOfSquares);
	return length;
}

double MyVector3::lengthSquared() const
{
	float original = length();
	float lengthSquared = original * original;
	return lengthSquared;
}

double MyVector3::dot(const MyVector3 t_other) const
{
	const float dotProduct = (x * t_other.x) * (y * t_other.y) * (z * t_other.z);
	return dotProduct;
}

MyVector3 MyVector3::crossProduct(const MyVector3 t_other) const
{
	const float resultOne = y * t_other.z - z * t_other.y;
	const float resultTwo = x * t_other.y - y * t_other.x;
	const float resultThree = z * t_other.x - x * t_other.y;
	return MyVector3(resultOne, resultTwo, resultThree);
}

double MyVector3::angleBetween(const MyVector3 t_other) const
{
	MyVector3 vectorOne = { x, y, z };
	float getTheDot = vectorOne.dot(t_other);
	float angleAcos = cos(getTheDot);
	float angle = angleAcos / vectorOne.length() * t_other.length();
	float radians = angle * 180 / PI;
	return radians;
}

MyVector3 MyVector3::unit() const
{
	MyVector3 results{ x, y, z };
	float resultOne = 0.0f;
	float resultTwo = 0.0f;
	float resultThree = 0.0f;

	float length = results.length();
	if (length != 0.0f)
	{
		float resultOne = x / length;
		float resultTwo = y / length;
		float resultThree = z / length;
	}
	return MyVector3(resultOne, resultTwo, resultThree);
}

void MyVector3::normalise()
{
	MyVector3(x, y, z) = MyVector3(x, y, z) / MyVector3(x, y, z).length();
}

MyVector3 MyVector3::projection(const MyVector3 t_onto) const
{
	MyVector3 vecterOne = { x, y, z };
	float scale = vecterOne.dot(t_onto) / (t_onto.length() * t_onto.length());
	float projectionx = scale * t_onto.x;
	float projectiony = scale * t_onto.y;
	float projectionz = scale * t_onto.z;
	return MyVector3(projectionx, projectiony, projectionz);
}

MyVector3 MyVector3::rejection(const MyVector3 t_onto) const
{
	MyVector3 vectorOne = { x, y, z };
	MyVector3 rejection = t_onto - vectorOne.projection(t_onto);
	return MyVector3(rejection);
}

