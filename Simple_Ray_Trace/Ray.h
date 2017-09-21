#pragma once

using namespace std;

#ifndef RAY_H
#define RAY_H

#include <math.h>
#include "Vec3.h"

//Defines a ray of light
class Ray
{

private:
	Vec3 origin; //ray origin
	Vec3 direction; //ray direction

public:
	//Default Constructor
	Ray();
	//Creates a new point with the specified coordinates
	Ray(Vec3, Vec3);

	//Get Methods
	Vec3 GetOrigin();
	Vec3 GetDirection();

	//Set Methods
	void SetOrigin(Vec3);
	void SetDirection(Vec3);

};

#endif

