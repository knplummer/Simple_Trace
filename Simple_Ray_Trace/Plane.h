#pragma once

using namespace std;

#ifndef PLANE_H
#define PLANE_H

#include "Vec3.h"
#include "Color.h"
#include "Object.h"
#include <math.h>

//Defines a Plane object
class Plane : public Object
{

private:
	Vec3 normal; //plane normal
	double distance; //Plane distance from origin
	Color color; //Plane color

public:
	//Default Constructor
	Plane();
	//Creates a new Plane with the specified coordinates, size, and color
	Plane(Vec3, double, Color);

	//Get Methods
	Vec3 GetNormal();
	double GetDistance();
	Color GetColor();

	//Set Methods
	void SetNormal(Vec3);
	void SetDistance(double);
	void SetColor(Color);

	//Plane Functions
	Vec3 GetNormalAt(Vec3);
	double FindIntersection(Ray);

};

#endif

