#include "Camera.h"
#include <vector>
#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

float* cross(float* ijk, float* bcd)
{
	static float out[3] = {0,0,0};

	for (int i = 0; i < 3; i++)
	{
		out[i] = *(ijk + (i + 1) % 3) * *(bcd + (i + 2) % 3) - *(bcd + (i + 1) % 3) * *(ijk + (i + 2) % 3);
	}

	return out;
}

Camera::Camera()
{
	float init[4] = { 1,0,0,0 };
	wijk = new float[4];
	for (int i = 0; i < 4; i++)
	{
		wijk[i] = 0;
	}
	dir = Quat(init);
	scale = 1;
	RES = 1000;
	focl = 1;
	Mass = 1;
	rspan = 0;
	rRES = 0;
	
}

Camera::Camera(float* poss, float* dirr, float scalee, float ress, float focll, float mass,float rspann, float rress)
{
	wijk = new float[4];
	for (int i = 0; i < 4; i++)
	{
		wijk[i] = poss[i];
	}
	
	dir = Quat(dirr);
	scale = scalee;
	RES = ress;
	focl = focll;
	Mass = mass;
	rspan = rspann;
	rRES = rress;
}

void Camera::take_pic(SDL_Renderer* render)
{
	SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
	SDL_RenderClear(render);
	
	for (float X = 0; X < RES; X++)
	{
		for (float Y = 0; Y < RES; Y++)
		{
			bool draw = false;
			Ray ray = point(X, Y);
			draw = ray.trace();
			
		
		
			if (draw)
			{
				SDL_SetRenderDrawColor(render, 255 * exp(-ray.interval/40), 0, 255 * exp(-ray.interval/40), 255);
				SDL_RenderDrawPoint(render, X, Y);
			}
			

		}
	}

}

Ray Camera::point(float X, float Y)
{
	float x = (X / (RES - 1) - 0.5) * scale;
	float y = (Y / (RES - 1) - 0.5) * scale;
	float z = focl;

	
	float len = sqrt(x * x + y * y + focl * focl);
	float dirr[3] = { x / len,y / len,focl / len };
	float pos_dir[3] = { wijk[1],wijk[2],wijk[3] };
	float* axis = cross(dirr,pos_dir);
	float mag = sqrt(axis[0] * axis[0] + axis[1] * axis[1] + axis[2] * axis[2]);
	for (int i = 0; i < 3; i++)
	{
		axis[i] /= mag;
	}
	
	float r = sqrt(pos_dir[0] * pos_dir[0] + pos_dir[1] * pos_dir[1] + pos_dir[2] * pos_dir[2]);
	float dr  = (dirr[0] * pos_dir[0] + dirr[1] * pos_dir[1] + dirr[2] * pos_dir[2]);
	float p = -dr / r / r;



	
	
	return Ray(wijk, axis, p, Mass, rspan, rRES);
}
