#pragma once

using namespace std;

#ifndef VEC3_H
#define VEC3_H

#include <math.h>

//Defines a point in 3D space
class Vec3
{

private:
	double x; //x-coordinate
	double y; //y-coordinate
	double z; //z-coordinate

public:
	//Default Constructor
	Vec3();
	//Creates a new point with the specified coordinates
	Vec3(double, double, double);

	//Get Methods
	double GetX();
	double GetY();
	double GetZ();

	//Set Methods
	void SetX(double);
	void SetY(double);
	void SetZ(double);

	//Linear Algebra Methods
	double Magintude();
	Vec3 Norm();
	Vec3 Invert();
	double DotProduct(Vec3);
	Vec3 CrossProduct(Vec3);
	Vec3 AddVector(Vec3);
	Vec3 ScalarMult(double);

};

#endif

