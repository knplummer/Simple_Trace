#pragma once

using namespace std;

#ifndef LIGHT_H
#define LIGHT_H

#include "Vec3.h"
#include "Color.h"
#include "LightSource.h"

//Defines a Light object
class PointLight : public LightSource
{

private:
	Vec3 position; //Light position
	Color color; //Light color

public:
	//Default Constructor
	PointLight();
	//Creates a new point with the specified coordinates
	PointLight(Vec3, Color);

	//Get Methods
	virtual Vec3 GetPosition();
	virtual Color GetColor();

	//Set Methods
	void SetPostion(Vec3);
	void SetColor(Color);

};

#endif

