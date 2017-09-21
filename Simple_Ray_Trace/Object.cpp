#include "Object.h"

Object::Object(){}

//Get Methods
Vec3 Object::GetPosition() {
	return Vec3(0,0,0);
}

Color Object::GetColor() {
	return Color(0,0,0,0,0);
}

Vec3 Object::GetNormalAt(Vec3 point) {
	return Vec3(0, 0, 0);
}


//Object Functions
double Object::FindIntersection(Ray) {
	return 0;
}