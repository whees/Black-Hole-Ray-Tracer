#include "Quat.h"


#pragma once

class Ray
{
public:
	Quat pos;
	Quat axis;
	float p;
	float u;
	float M;
	float span;
	float RES;
	float tdot;
	float interval;
	
	
	Ray();
	Ray(float* wijk, float* xyz, float pp, float MM, float ss, float RR);

	float pdot();

	bool trace();

};

