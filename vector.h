#pragma once
#include "math2d.h"

class m2d::vector
{
public:
	float x;
	float y;


	~vector();

	//default: x and y are initialized with 0
	vector();

	//copy constructor
	vector(const vector& c);

	//Initializes x & y with the given values
	vector(float X, float Y);

	//X and Y are initialized with the value of b
	vector(float b);

	/////////////
	//Operators//
	/////////////

	vector operator+(vector const& v) const;
	vector operator-(vector const& v) const;
	float operator*(vector const& v) const;
	vector operator*(const float s) const;
	vector operator/(const float s) const;

	void operator+=(vector const &v);
	void operator-=(vector const &v);
	void operator*=(const float s);
	void operator/=(const float s);

	//results in TRUE if this vector and v are ALMOST equal. (s. std::numeric_limits<float>::epsilon())
	bool operator==(vector const & v);

	////////////////
	//manipulators//
	////////////////

	//changes the vector as to make it the length of 1
	void normalize();

	//rotate the vector by rad (Radians)
	void rotate(float const rad); //same as rotateRad

	//rotate the vector by rad (Radians)
	void rotateRad(float const rad);

	//rotate the vector by deg (Degrees)
	void rotateDeg(float const deg);

	//scale this vector by s
	void scale(float const s);

	//flips this vector around (*-1)
	void flip();

	//mirrors this vector along a line coming from the origin
	void mirror(vector const  &v);

	//shears the vector along the line given
	void shear(vector const &v, float m);

	///////////////
	//calculators//
	///////////////

	//calculates the angle between this vector and vec
	float angle(vector const &vec) const;

	//gets the length of this vector
	float length() const;
};

