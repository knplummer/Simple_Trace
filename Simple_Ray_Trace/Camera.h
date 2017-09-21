#pragma once

using namespace std;

#ifndef CAMERA_H
#define CAMERA_H

#include "Vec3.h"

//Defines a Camera 
class Camera
{

private:
	Vec3 position; //Camera position in 3D space
	Vec3 direction; //Direction the camera is looking

	//used to orient the camera in 3D space
	Vec3 camRight; //define the direction of the right side of the camera
	Vec3 camDown; //define the position of the bottom of the camera

	Vec3 lookAt; //point the camera is looking at?

public:
	//Default Constructor
	Camera();
	//Creates a new camera given a position, direction, right, and down
	Camera(Vec3, Vec3, Vec3, Vec3);
	//Creates a camera given a postion in space and look at vector
	Camera(Vec3, Vec3);

	//Get Methods
	Vec3 GetPos();
	Vec3 GetDirection();
	Vec3 GetCamRight();
	Vec3 GetCamDown();
	Vec3 GetLookAt();

	//Set Methods
	void SetPos(Vec3);
	void SetDirection(Vec3);
	void SetCamRight(Vec3);
	void SetCamDown(Vec3);
	void SetLookAt(Vec3);

	//Camera Methods
	Vec3 DiffBtwn();
	Vec3 CamDir(Vec3);
	Vec3 CamRight(Vec3);
	Vec3 CamDown(Vec3, Vec3);
};

#endif

