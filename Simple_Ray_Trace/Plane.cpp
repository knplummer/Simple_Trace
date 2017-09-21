#include "Plane.h"

Plane::Plane()
{
	normal = Vec3(0,1,0); //defalut nomal to be the y axis
	distance = 0; //sets on the origin
	color = Color(); //default color to gray
}

Plane::Plane(Vec3 n, double d, Color c)
{
	normal = n;
	distance = d;
	color = c;
}


//Get Methods
Vec3 Plane::GetNormal() {
	return normal;
}

double Plane::GetDistance() {
	return distance;
}

Color Plane::GetColor() {
	return color;
}


//Set Methods
void Plane::SetNormal(Vec3 n) {
	normal = n;
}

void Plane::SetDistance(double d) {
	distance = d;
}

void Plane::SetColor(Color c) {
	color = c;
}


//Plane Functions
Vec3 Plane::GetNormalAt(Vec3 point) {
	return normal;
}

double Plane::FindIntersection(Ray r) {
	double a = r.GetDirection().DotProduct(normal);
	if (a == 0) {
		//ray is parallel to the plane
		return -1; //never intersects
	}
	else {

		double b = normal.DotProduct(r.GetOrigin().AddVector(normal.ScalarMult(distance).Invert()));
		return -1 * b / a;
	}
}