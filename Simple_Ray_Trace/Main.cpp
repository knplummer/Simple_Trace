#include <iostream> //standard input/output
#include <fstream> //file operations input/output
#include <sstream> //string stream operate on strings
#include <vector> //array that can change size
#include <string> //for variables of string type
#include <cmath>
#include <limits>

#include <stdlib.h> //random generators, malloc, etc..
#include <stdio.h> //input/output operations on buffers
#include <time.h> //manipulate date and time info

#include "Vec3.h" //3D vector
#include "Ray.h" //Ray of light
#include "Camera.h" //Camera object
#include "Color.h"//Material of objects
#include "PointLight.h"//Light Object
#include "Sphere.h"//Sphere Object
#include "Plane.h"//Plane Object



using namespace std;

struct RGBAType {
	double r;
	double g;
	double b;
	double a;
};

//function definitions
void SaveBMP(const char * filename, int w, int h, int dpi, RGBAType * data);
void RayTrace(int, int, int);
int ClosestObjectIndex(vector<double> intersections);
Color GetColor(Vec3, Vec3, vector<Object*>, int, double, double, vector<LightSource*>);

int  xAndY; //used to determine the x and y coordinates of an individual pixel

int main() {
	int height;
	int width;
	int dpi = 300;
	cout << "Image Width: ";
	cin >> width;
	cout << endl;
	cout << "Image Height: ";
	cin >> height;
	cout << endl;

	//set up resolution anti aliasing and file location selection options

	//RayTrace the image
	time_t start = time(0);
	RayTrace(width, height, dpi);
	time_t end = time(0);

	time_t total = end - start;
	
	int minutes = total / 3600;
	cout << total;

	return 0;
}

//separate funtion to move this into different class later
void RayTrace(int width, int height, int dpi) {

	//use to calculate the current percentage of an image rendered
	int totalPixels = width * height;
	int fiftyPercent = totalPixels / 2;
	int currentPixel = 0;

	//calculates aspect ratio of an image
	double aspectRatio = (double)width / (double)height;

	//defines the ambient light of a scene, allow user to set this
	double ambientLight = 0.2;

	//helps adjust for numerical error
	double accuracy = 0.000001;

	//Grid Axis vectors
	Vec3 x (1, 0, 0);
	Vec3 y (0, 1, 0);
	Vec3 z (0, 0, 1);
	Vec3 origin(0, 0, 0);




	//*****Begin Scene Definition****//
	Vec3 camPos(3, 1.5, -4);

	//Define the camera for the scene
	Camera sceneCam(camPos, origin);

	//Object colors
	Color lightGreen(0.5, 1, 0.5, 1, 0.3);
	Color gray();
	Color black(0, 0, 0, 1, 0);
	Color maroon(0.5, 0.25, 0.25, 1, 0);

	//Defines a light
	Color whiteLight(1, 1, 1, 0, 0);
	Vec3 lightPos(-7, 10, -10);
	PointLight sceneLight1(lightPos, whiteLight);

	//Defines a sphere
	Sphere sphere1(origin, 1, lightGreen);

	//Defines a plane
	Plane plane(y, -1, maroon);

	//Add objects to list of objects in the scene (list will become a propery of scene)
	vector<Object*> sceneObjects;
	sceneObjects.push_back(dynamic_cast<Object*>(&sphere1));
	sceneObjects.push_back(dynamic_cast<Object*>(&plane));

	//Add lights to a list
	vector<LightSource*>sceneLights;
	sceneLights.push_back(dynamic_cast<LightSource*>(&sceneLight1));

	//*****End Scene Definition*****//


	//slightly left and right of cam direction
	double xAmount;
	double yAmount;


	//resolution 300 is high res
	RGBAType *pixels = new RGBAType[totalPixels]; //pointer to array of colors that is number of total pixels

	cout << "Rendering...0%";
	//Nested for loops hit each pixel of an image
	for (int x = 0; x < width; x++) { //loop left to right across the image
		for (int y = 0; y < height; y++) { //loop to to bottom of the image
			//rendering calculations
			xAndY = y * width + x;


			//start with no anti-aliasing
			//Amount of variation from the direction the camera is pointing for a ray to be sent through each pixel in the image plane
			//find this equation
			if (width > height) {
				xAmount = ((x + 0.5) / width)*aspectRatio - (((width - height) / (double)height / 2));
				yAmount = ((height - y) + 0.5) / height;
			}
			else if(height > width) {
				xAmount = (x + 0.5) / width;
				yAmount = (((height - y) + 0.5) / height) / aspectRatio - (((height - width) / (double)width) / 2);
			}
			else {
				xAmount = (x + 0.5) / width;
				yAmount = ((height - y) + 0.5) / height;
			}

			Vec3 camRayOrigin = sceneCam.GetPos(); //The location of the camera

			//Calculates the direction of the ray to pass through the current pixel in the image plane
			//find this equation
			Vec3 camRayDirection = sceneCam.GetDirection().AddVector(sceneCam.GetCamRight().ScalarMult(xAmount - 0.5).AddVector(sceneCam.GetCamDown().ScalarMult(yAmount - 0.5))).Norm();

			Ray camRay(camRayOrigin, camRayDirection);//The ray that passes through the image plane into the scene

			//Begin looking for intersections in the scene with camRay

			vector<double>intersections;

			for (int i = 0; i < sceneObjects.size(); i++) {
				intersections.push_back(sceneObjects.at(i)->FindIntersection(camRay));
			}

			int index = ClosestObjectIndex(intersections);

			//if the pixel misses everything set bg to black
			if (index == -1) {
				pixels[xAndY].r = 0;
				pixels[xAndY].g = 0;
				pixels[xAndY].b = 0;
				pixels[xAndY].a = 0;
			}
			else {
				if (intersections.at(index) > accuracy) {
					//determine postition and direction vectors at point of intersection
					Vec3 intersectionPosition = camRayOrigin.AddVector(camRayDirection.ScalarMult(intersections.at(index)));
					Vec3 intersectionDirection = camRayDirection;


					Color intersectionColor = GetColor(intersectionPosition, intersectionDirection, sceneObjects, index, accuracy, ambientLight, sceneLights);

					pixels[xAndY].r = intersectionColor.GetRed();
					pixels[xAndY].g = intersectionColor.GetGreen();
					pixels[xAndY].b = intersectionColor.GetBlue();
					//until transparency is implemented alpha can be 0 or 1
					pixels[xAndY].a = intersectionColor.GetAlpha();
				}
				
			}
			



			//increase pixel and check to see if 50% rendered
			currentPixel++;
			if (currentPixel == fiftyPercent) {
				cout << "...50%";
			}
		}
	}
	
	//save the image
	SaveBMP("C:/Users/Kalen/Desktop/scene.bmp", width, height, dpi, pixels);

	cout << "...100%" << endl;
}

//return the index of the closest intersection
int ClosestObjectIndex(vector<double> intersections) {
	//if no intersections prevent unnessacary calculations
	if (intersections.size() == 0) {
		return -1;
	}
	else if (intersections.size() == 1) {
		if (intersections[0] > 0) {
			return 0;
		}
		else {
			return -1;
		}
	}
	else {
		int minValue = -1;
		double max = 0;
		for (int i = 0; i < intersections.size(); i++) {
			if (max < intersections[i]) {
				max = intersections[i];
			}
		}
		if (max > 0) {
			for (int i = 0; i < intersections.size(); i++) {
				if (intersections[i] > 0 && intersections[i] <= max) {
					max = intersections[i];
					minValue = i;
				}
			}
			return minValue; 
		}
		else {
			return -1;
		}
	}

}

//Return the color of a pixel based on all the scene factors
Color GetColor(Vec3 intersectionPosition, Vec3 intersectionDirection, vector<Object*> sceneObjects, int index, double accuracy, double ambientLight, vector<LightSource*>sceneLights) {
	
	Color objectColor = sceneObjects.at(index)->GetColor();
	Vec3 objectNormal = sceneObjects.at(index)->GetNormalAt(intersectionPosition);

	Color finalColor = objectColor.ColorScalar(ambientLight);

	for each (LightSource* light in sceneLights){
		//find this equation
		Vec3 lightDirection = light->GetPosition().AddVector(intersectionPosition.Invert()).Norm();

		//angle between the normal of the object and the light
		float cosineAngle = objectNormal.DotProduct(lightDirection);

		if (cosineAngle > 0) {
			//test for shadows
			bool inShadow = false;

			Vec3 distanceToLight = light->GetPosition().AddVector(intersectionPosition.Invert()).Norm();
			float distanceToLightMagnitude = distanceToLight.Magintude();

			/*Create a new ray from the intersection point to the light source
			  Check for intersections with object to determine if in shadow*/
			Ray shadowRay(intersectionPosition, light->GetPosition().AddVector(intersectionPosition.Invert()).Norm());

			vector<double> shadowRayInteresections;

			for each(Object* o in sceneObjects) {
				if (!inShadow) {
					shadowRayInteresections.push_back(o->FindIntersection(shadowRay));
				}
			}

			for each(double intersection in shadowRayInteresections) {
				if (intersection > accuracy && intersection <= distanceToLightMagnitude) {
					inShadow = true;
					break;
				}
			}

			if (!inShadow) {
				//find this equation
				finalColor = finalColor.ColorAdd(objectColor.ColorMult(light->GetColor()).ColorScalar(cosineAngle));

				if (objectColor.GetSpecial() > 0 && objectColor.GetSpecial() <= 1) {
					double dot1 = objectNormal.DotProduct(intersectionDirection.Invert());
					Vec3 vec1 = objectNormal.ScalarMult(dot1);
					Vec3 add1 = vec1.AddVector(intersectionDirection);
					Vec3 vec2 = add1.ScalarMult(2);
					Vec3 add2 = intersectionDirection.Invert().AddVector(vec2);
					Vec3 reflectionDirection = add2.Norm();

					double specular = reflectionDirection.DotProduct(lightDirection);

					if (specular > 0) {
						specular = pow(specular, 10);
						finalColor = finalColor.ColorAdd(light->GetColor().ColorScalar(specular*objectColor.GetSpecial()));
					}
				}
			}
		}
	}
	return finalColor.Clip();
}










//move into separate class with multiple save functions (look for image saving library)
void SaveBMP(const char * filename, int w, int h, int dpi, RGBAType * data) {
	FILE *f;
	int k = w*h; //total pixels
	int s = 4 * k; //multiplying by 4 makes 16 bit image allows for 256 colors per pixel
	int filesize = 54 + s; //space for file header

	double factor = 39.375;
	int m = static_cast<int>(factor);

	int ppm = dpi*m;

	unsigned char bmpfileheader[14] = { 'B', 'M', 0, 0, 0, 0,  0, 0, 0, 0,  54, 0, 0, 0 };
	unsigned char bmpinfoheader[40] = { 40, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  1, 0, 24, 0 }; //14 + 40 = 54 space for file header

	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)(filesize>>8);
	bmpfileheader[4] = (unsigned char)(filesize>>16);
	bmpfileheader[5] = (unsigned char)(filesize>>24);

	bmpinfoheader[4] = (unsigned char)(w);
	bmpinfoheader[5] = (unsigned char)(w>>8);
	bmpinfoheader[6] = (unsigned char)(w>>16);
	bmpinfoheader[7] = (unsigned char)(w>>24);

	bmpinfoheader[8] = (unsigned char)(h);
	bmpinfoheader[9] = (unsigned char)(h >> 8);
	bmpinfoheader[10] = (unsigned char)(h >> 16);
	bmpinfoheader[11] = (unsigned char)(h >> 24);

	bmpinfoheader[21] = (unsigned char)(s);
	bmpinfoheader[22] = (unsigned char)(s >> 8);
	bmpinfoheader[23] = (unsigned char)(s >> 16);
	bmpinfoheader[24] = (unsigned char)(s >> 24);

	bmpinfoheader[25] = (unsigned char)(ppm);
	bmpinfoheader[26] = (unsigned char)(ppm >> 8);
	bmpinfoheader[27] = (unsigned char)(ppm >> 16);
	bmpinfoheader[28] = (unsigned char)(ppm >> 24);

	bmpinfoheader[29] = (unsigned char)(ppm);
	bmpinfoheader[30] = (unsigned char)(ppm >> 8);
	bmpinfoheader[31] = (unsigned char)(ppm >> 16);
	bmpinfoheader[32] = (unsigned char)(ppm >> 24);

	errno_t err;
	if (err = fopen_s(&f, filename, "wb") != 0) {
		cout << "Cannot open file";
	}
	else {

		fwrite(bmpfileheader, 1, 14, f);
		fwrite(bmpinfoheader, 1, 40, f);

		for (int i = 0; i < k; i++) {
			RGBAType rgb = data[i];

			double red = data[i].r * 255;
			double green = data[i].g * 255;
			double blue = data[i].b * 255;

			unsigned char color[3] = { (int)floor(blue), (int)floor(green), (int)floor(red) };

			fwrite(color, 1, 3, f);
		}

		fclose(f);
	}
}