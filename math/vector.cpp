#include "vector.h"
#include <limits>

#define _USE_MATH_DEFINES
#include <math.h>


using namespace m2d;



vector::~vector()
{}

//default: x and y are initialized with 0
vector::vector() :x(0.0f), y(0.0f)
{}

//copy constructor
vector::vector(const vector& c)
{
	x = c.x;
	y = c.y;
}

//Initializes x & y with the given values
vector::vector(float X, float Y) :x(X), y(Y)
{}

//X and Y are initialized with the value of b
vector::vector(float b) : x(b), y(b)
{}

/////////////
//Operators//
/////////////

vector vector::operator+(vector const& v) const
{
	return vector(x + v.x, y + v.y);
}

vector vector::operator-(vector const& v) const
{
	return vector(x - v.x, y - v.y);
}

float vector::operator*(vector const& v) const
{
	return x*v.x + y*v.y;
}

vector vector::operator*(const float s) const
{
	return vector(x*s, y*s);
}

vector vector::operator*(const float s) const
{
	return vector(x/s, y/s);
}


void vector::operator+=(vector const &v)
{
	x += v.x;
	y += v.y;
}
void vector::operator-=(vector const &v)
{
	x -= v.x;
	y -= v.y;
}
void vector::operator*=(const float s)
{
	x *= s;
	y *= s;
}

void vector::operator/=(const float s)
{
	x /= s;
	y /= s;
}

bool vector::operator==(vector const & v)
{
	return (*this - v).length() < std::numeric_limits<float>::epsilon();
}

////////////////
//manipulators//
////////////////

//changes the vector as to make it the length of 1
void vector::normalize()
{
	float length = this->length();
	x /= length;
	y /= length;
}

//rotate the vector by rad (Radians)
void vector::rotate(float const rad)
{
	rotateRad(rad);
}

//rotate the vector by rad (Radians)
void vector::rotateRad(float const rad)
{
	x = x*std::cosf(rad) - y*std::sinf(rad);
	y = x*std::sinf(rad) + y*std::cosf(rad);
}

//rotate the vector by deg (Degrees)
void vector::rotateDeg(float const deg)
{
	float rad = M_PI * 2 * deg / 360.0f;
	rotateRad(rad);
}

//scale this vector by s
void vector::scale(float const s)
{
	x *= s;
	y *= s;
}

//flips this vector around (*-1)
void vector::flip()
{
	x *= -1.0f;
	y *= -1.0f;
}

//mirrors this vector along a line coming from the origin
void vector::mirror(vector const &v)
{
	x = -x + 2 * ((*this)*v)*v.x;
	y = -y + 2 * ((*this)*v)*v.y;
}

//shears the vector along the line given
void vector::shear(vector const &v, float m)
{
	x = x + m * (x*-v.x+y*v.y)*v.x;
	y = y + m * (x*-v.x + y*v.y)*v.y;
}

///////////////
//calculators//
///////////////

//calculates the angle between this vector and vec in radians
float vector::angle(vector const &vec) const
{

	return std::acos(((*this)*vec) / (this->length()* vec.length()));
}

//gets the length of this vector
float vector::length() const
{
	return x*x + y*y;
}