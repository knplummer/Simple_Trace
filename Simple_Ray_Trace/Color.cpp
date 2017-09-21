#include "Color.h"

//Constructor Definitions
Color::Color()
{
	red = 0.5;
	green = 0.5;
	blue = 0.5;
	alpha = 0;
	special = 0;
}

Color::Color(double r, double g, double b, double a, double s)
{
	red = r;
	green = g;
	blue = b;
	alpha = a;
	special = s;
}


//Get Methods
double Color::GetRed() {
	return red;
}

double Color::GetGreen() {
	return green;
}

double Color::GetBlue() {
	return blue;
}

double Color::GetAlpha() {
	return alpha;
}

double Color::GetSpecial() {
	return special;
}


//Set Methods
void Color::SetRed(double r) {
	red = r;
}

void Color::SetGreen(double g) {
	green = g;
}

void Color::SetBlue(double b) {
	blue = b;
}

void Color::SetAlpha(double a) {
	alpha = a;
}

void Color::SetSpecial(double s) {
	blue = s;
}


double Color::Brightness() {
	return (red + green + blue) / 3;
}

Color Color::ColorScalar(double scalar) {
	return Color(red*scalar, green*scalar, blue*scalar, alpha, special);
}

Color Color::ColorAdd(Color color) {
	return Color(red + color.GetRed(), green + color.GetGreen(), blue + color.GetBlue(), alpha, special);
}

Color Color::ColorMult(Color color) {
	return Color(red * color.GetRed(), green * color.GetGreen(), blue * color.GetBlue(), alpha, special);
}

Color Color::ColorAvg(Color color) {
	return Color((red + color.GetRed()) / 2, (green + color.GetGreen()) / 2, (blue + color.GetBlue()) / 2, alpha, special);
}

Color Color::Clip() {
	double allLight = red + green + blue;
	double excessLight = allLight - 3;
	if (excessLight > 0) {
		red = red + excessLight*(red / allLight);
		green = green + excessLight*(green / allLight);
		blue = blue + excessLight*(blue / allLight);
	}

	if (red > 1) {
		red = 1;
	}
	if (green > 1) {
		green = 1;
	}
	if (blue > 1) {
		blue = 1;
	}

	if (red < 0) {
		red = 0;
	}
	if (green < 0) {
		green = 0;
	}
	if (blue < 0) {
		blue = 0;
	}

	return Color(red, green, blue, 1, special);
}



