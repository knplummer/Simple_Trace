#pragma once

using namespace std;

#ifndef COLOR_H
#define COLOR_H

#include <math.h>

//Defines a color material
class Color
{

private:
	double red; 
	double green; 
	double blue; 
	double alpha;
	double special;

public:
	//Default Constructor
	Color();
	//Creates a new color with the specified values
	Color(double, double, double, double, double);

	//Get Methods
	double GetRed();
	double GetGreen();
	double GetBlue();
	double GetAlpha();
	double GetSpecial();

	//Set Methods
	void SetRed(double);
	void SetGreen(double);
	void SetBlue(double);
	void SetAlpha(double);
	void SetSpecial(double);

	double Brightness();
	Color ColorScalar(double);
	Color ColorAdd(Color);
	Color ColorMult(Color);
	Color ColorAvg(Color);
	Color Clip();
};

#endif

