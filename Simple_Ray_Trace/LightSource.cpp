#include "LightSource.h"

LightSource::LightSource() {}

//Get Methods
Vec3 LightSource::GetPosition() {
	return Vec3(0, 0, 0);
}

Color LightSource::GetColor() {
	return Color(1, 1, 1, 1, 0);
}

