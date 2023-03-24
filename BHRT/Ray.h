#include "Quat.h"
#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif
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

