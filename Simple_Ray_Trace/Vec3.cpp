#include "Vec3.h"

//Constructor Definitions
Vec3::Vec3()
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

Vec3::Vec3(double i, double j, double k)
{
	x = i;
	y = j;
	z = k;
}


//Get Methods
double Vec3::GetX() {
	return x;
}

double Vec3::GetY() {
	return y;
}

double Vec3::GetZ() {
	return z;
}


//Set Methods
void Vec3::SetX(double i) {
	x = i;
}

void Vec3::SetY(double j) {
	y = j;
}

void Vec3::SetZ(double k) {
	z = k;
}


/****LINEAR ALGEBRA FUNCTIONS*****/

//Vector Magintude
/*
Returns a scalar that is the lenght of
the vector

||v|| = sqrt(v.v) = sqrt(vx^2+vy^2+vz^2)

Page 331 Linear Algebra Book
Page 657 Calculus Book
*/
double Vec3::Magintude() {
	return sqrt((x*x) + (y*y) + (z*z));
}

//Vector Norm
/*
Given a vector retruns a vector in the same
Direction with magnitude of 1

normal = vector components/length of vector = (1/||v||)*v

Page 331 Linear Algebra Book
Page 662 Calculus Book
*/
Vec3 Vec3::Norm() {
	double magnitude = sqrt((x*x) + (y*y) + (z*z));
	return Vec3(x / magnitude, y / magnitude, z / magnitude);
}

//Invert Vector
/*
Returns a vector with the negaitve of the
components
*/
Vec3 Vec3::Invert() {
	return Vec3(-x, -y, -z);
}

//Dot Product/InnerProduct
/*
Returns a scalar used to determine angle between
vectors

x = v^t*w = x1*x2+y1*y2+z1*z2

Page 330 Linear Algebra Book
Page 678 Calculus Book
*/
double Vec3::DotProduct(Vec3 w) {
	return (x*w.GetX()) + (y*w.GetY()) + (z*w.GetZ());
}

//Cross Product
/*
Returns a vector that is orthogonal(perpendicular) to
both vectors used in the calculation

See Determinants Linear Algebra Book
Page 688 Calculus Book
*/
Vec3 Vec3::CrossProduct(Vec3 w) {
	return Vec3(y*w.GetZ() - z*w.GetY(), z*w.GetX() - x*w.GetZ(), x*GetY() - y* w.GetX());
}

//Add Vector
/*
Returns a vector that equals the two vectors
added together

u = v + w

Page 24 Linear Algebra Book
Page 659 Calculus Book
*/
Vec3 Vec3::AddVector(Vec3 w) {
	return Vec3(x + w.GetX(), y + w.GetY(), z + w.GetZ());
}

//Scalar Multiplication
/*
Returns a vector whos components have been
multiplied by a scalar

u = cv

Page 24 Linear Algebra Book
Page 660 Calculus Book
*/
Vec3 Vec3::ScalarMult(double c) {
	return Vec3(c*x, c*y, c*z);
}