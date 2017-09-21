#include "Sphere.h"

Sphere::Sphere()
{
	position = Vec3(); //defalut to origin of the scene
	radius = 1;
	color = Color(); //default color to gray
}

Sphere::Sphere(Vec3 p, double r, Color c)
{
	position = p;
	radius = r;
	color = c;
}


//Get Methods
Vec3 Sphere::GetPosition() {
	return position;
}

double Sphere::GetRadius() {
	return radius;
}

Color Sphere::GetColor() {
	return color;
}


//Set Methods
void Sphere::SetPostion(Vec3 p) {
	position = p;
}

void Sphere::SetRadius(double r) {
	radius = r;
}

void Sphere::SetColor(Color c) {
	color = c;
}

Vec3 Sphere::GetNormalAt(Vec3 point) {
	//Normal always points away from center
	Vec3 normal = point.AddVector(position.Invert()).Norm();
	return normal;
}

double Sphere::FindIntersection(Ray r) {
	double a = 1;
	double b = (2 * (r.GetOrigin().GetX() - position.GetX())*r.GetDirection().GetX()) + (2 * (r.GetOrigin().GetY() - position.GetY())*r.GetDirection().GetY()) + (2 * (r.GetOrigin().GetZ() - position.GetZ())*r.GetDirection().GetZ());
	double c = pow(r.GetOrigin().GetX() - position.GetX(), 2) + pow(r.GetOrigin().GetY() - position.GetY(), 2) + pow(r.GetOrigin().GetZ() - position.GetZ(), 2) - (radius*radius);

	//b^2 - 4ac where a=1
	double discriminant = b*b - 4 * c;

	if (discriminant > 0) {
		//the ray intersects the sphere
		//two roots find one closer to camera

		//root 1
		double root1 = ((-1 * b - sqrt(discriminant)) / 2) - 0.000001;//.0001 helps with accuracy errors

		if (root1 > 0) {
			//first root is smallest positive root
			return root1;
		}
		else {
			//second root is smallest positve root
			return ((sqrt(discriminant) - b) / 2) - 0.000001; //root 2
		}
	}
	else {
		//ray missed the sphere
		return -1;
	}
}