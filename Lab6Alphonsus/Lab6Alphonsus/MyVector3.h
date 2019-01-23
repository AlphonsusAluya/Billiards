#ifndef MYVECTOR3 
#define MYVECTOR3


/// <summary>
/// your name here or no marks
/// 

#include <iostream>
#include <SFML/Graphics.hpp>


class MyVector3
{
public:
	double x;
	double y;
	double z;

	MyVector3();
	~MyVector3();
	std::string toString();


	
	MyVector3(double x, double y, double z);
	MyVector3(sf::Vector3f t_sfVector);
	MyVector3(sf::Vector3i t_sfVector);
	MyVector3(sf::Vector2i t_sfVector);
	MyVector3(sf::Vector2u t_sfVector);
	MyVector3(sf::Vector2f t_sfVector); 
	
	
	MyVector3 operator +(const MyVector3 t_right) const;
	MyVector3 operator -(const MyVector3 t_right) const;
	MyVector3 operator *(const double t_scalar) const;
	MyVector3 operator /(const double t_divisor) const;
	MyVector3 operator +=(const MyVector3 t_right);
	MyVector3 operator -=(const MyVector3 t_right);

	bool operator == (const MyVector3 t_right) const;
	bool operator != (const MyVector3 t_right) const;

	// negative of a vector 
	MyVector3 operator -();  // this changes the vector
	//new methods for bouncing off sides of table in billiards
	void reverseX(); // this negates the x element of the vector
	void reverseY();  // this negates the y element of the vector

	double length()const;
	double lengthSquared()const;
	double dot(const MyVector3 t_other) const;
	MyVector3 crossProduct(const MyVector3 t_other)const;
	double angleBetween(const MyVector3 t_other)const;  // answer in degrees
	MyVector3 unit() const;  // vector doesn't change
	void normalise(); // vector changes and will have length 1 
	MyVector3 projection(const MyVector3 t_onto)const;
	// projection onto the other vector so answer will parallel to other vector.
	MyVector3 rejection(const MyVector3 t_onto)const;

	
	operator sf::Vector2f() { return sf::Vector2f{static_cast<float>(x),static_cast<float>(y) }; }; // {2.4,-2.6,3.0} ->  {2.4~,-2.6~}
	operator sf::Vector2i() { return sf::Vector2i{ }; };// {2.4,-2.6,3.0} ->  {2,-3}
	operator sf::Vector2u();// {2.4,-2.6,3.0} ->  {2,3}  needs more space than an inline
	operator sf::Vector3i() { return sf::Vector3i{ }; };// {2.4,-2.6,3.0} ->  {2,-3,3}
	operator sf::Vector3f() { return sf::Vector3f{ }; };// {2.4,-2.6,3.0} ->  {2.4~,-2.6~, 3.0}

};



#endif // !MYVECTOR3