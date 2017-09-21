#pragma once

using namespace std;

#ifndef OBJECT_H
#define OBJECT_H

#include "Vec3.h"
#include "Color.h"
#include "Ray.h"

//Defines a Object object
class Object
{

private:
	Vec3 position; //Object position
	Color color; //Object color

public:
	//Default Constructor
	Object();

	//Get Methods
	virtual Vec3 GetPosition();
	virtual Color GetColor();
	virtual Vec3 GetNormalAt(Vec3);

	//Object Methods
	/*Returns double because that is the distance to a point of intersection.
	If no intersection the ray continues into the scene infinitely*/
	virtual double FindIntersection(Ray); 


};

#endif

