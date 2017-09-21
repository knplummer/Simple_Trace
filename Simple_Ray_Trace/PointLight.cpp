#include "PointLight.h"

PointLight::PointLight()
{
	position = Vec3(); //defalut to origin of the scene
	color = Color(1,1,1,1,0); //default color to white
}

PointLight::PointLight(Vec3 p, Color c)
{
	position = p;
	color = c;
}


//Get Methods
Vec3 PointLight::GetPosition() {
	return position;
}

Color PointLight::GetColor() {
	return color;
}


//Set Methods
void PointLight::SetPostion(Vec3 p) {
	position = p;
}

void PointLight::SetColor(Color c) {
	color = c;
}