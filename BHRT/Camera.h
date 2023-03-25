#include <iostream>
#include "Quat.h"
#include "Ray.h"
#include "SDL.h"
#include <cmath>

#pragma once
class Camera
{
public:
	Quat dir;
	float* wijk;
	float scale, RES, focl;
	float Mass;
	float rspan, rRES;
	int mult;
	

	Camera();
	Camera(float* poss, float* dirr, float scalee, float ress, float focll, float mass, float rspan, float rress, int multt);

	void take_pic(SDL_Renderer* render,int** allorder, int index, int batch_size);

	Ray point(float X, float Y);



};

