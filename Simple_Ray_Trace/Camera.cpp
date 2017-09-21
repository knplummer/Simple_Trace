#include "Camera.h"

Camera::Camera()
{
	position = Vec3(); //defalut to origin of the scene
	direction = Vec3(0, 0, 1); //default to look down z axis into scene
	camRight = Vec3(); //direction of right side of camera
	camDown = Vec3(); //direction of bottom of camera
	lookAt = Vec3(); //point the camera is looking at
}

Camera::Camera(Vec3 p, Vec3 dir, Vec3 r, Vec3 down)
{
	position = p;
	direction = dir;
	camRight = r;
	camDown = down;
}

Camera::Camera(Vec3 pos, Vec3 look) 
{
	position = pos;
	lookAt = look;
	direction = CamDir(DiffBtwn());
	camRight = CamRight(direction);
	camDown = CamDown(camRight, direction);
}


//Get Methods
Vec3 Camera::GetPos() {
	return position;
}

Vec3 Camera::GetDirection() {
	return direction;
}

Vec3 Camera::GetCamRight() {
	return camRight;
}

Vec3 Camera::GetCamDown() {
	return camDown;
}
Vec3 Camera::GetLookAt() {
	return lookAt;
}



//Set Methods
void Camera::SetPos(Vec3 pos) {
	position = pos;
}

void Camera::SetDirection(Vec3 d) {
	direction = d;
}

void Camera::SetCamRight(Vec3 r) {
	camRight = r;
}

void Camera::SetCamDown(Vec3 d) {
	camDown = d;
}
void Camera::SetLookAt(Vec3 l) {
	lookAt = l;
}

//Camera Methods

//Returns the distance between the point it is looking at as a vector
Vec3 Camera::DiffBtwn() {
	return Vec3(position.GetX() - lookAt.GetX(), position.GetY() - lookAt.GetY(), position.GetZ() - lookAt.GetZ());
}

Vec3 Camera::CamDir(Vec3 dif) {
	return dif.Invert().Norm();
}

Vec3 Camera::CamRight(Vec3 camDir) {
	Vec3 y(0, 1, 0);
	return y.CrossProduct(camDir).Norm();
}

Vec3 Camera::CamDown(Vec3 camRight, Vec3 camDir) {
	return camRight.CrossProduct(camDir);
}