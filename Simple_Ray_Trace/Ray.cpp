#include "Ray.h"

Ray::Ray()
{
	origin = Vec3(); //defalut to origin of the scene
	direction = Vec3(1, 0, 0); //default to direction of x axis
}

Ray::Ray(Vec3 o, Vec3 d)
{
	origin = o;
	direction = d;
}


//Get Methods
Vec3 Ray::GetOrigin() {
	return origin;
}

Vec3 Ray::GetDirection() {
	return direction;
}


//Set Methods
void Ray::SetOrigin(Vec3 o) {
	origin = o;
}

void Ray::SetDirection(Vec3 d) {
	direction = d;
}