#pragma once

using namespace std;

#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "Vec3.h"
#include "Color.h"

//Defines a LigthtSource
class LightSource
{

private:
	Vec3 position; //Object position
	Color color; //Object color

public:
	//Default Constructor
	LightSource();

	//Get Methods
	virtual Vec3 GetPosition();
	virtual Color GetColor();



};

#endif

