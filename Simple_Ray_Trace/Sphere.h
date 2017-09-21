#pragma once

using namespace std;

#ifndef SPHERE_H
#define SPHERE_H

#include "Vec3.h"
#include "Color.h"
#include "Object.h"
#include <math.h>

//Defines a Sphere object
class Sphere : public Object
{

private:
	Vec3 position; //Sphere position
	double radius; //Sphere radius
	Color color; //Sphere color

public:
	//Default Constructor
	Sphere();
	//Creates a new sphere with the specified coordinates, size, and color
	Sphere(Vec3, double, Color);

	//Get Methods
	Vec3 GetPosition();
	double GetRadius();
	Color GetColor();

	//Set Methods
	void SetPostion(Vec3);
	void SetRadius(double);
	void SetColor(Color);

	Vec3 GetNormalAt(Vec3);
	double FindIntersection(Ray);

};

#endif

