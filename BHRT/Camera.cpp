#include "Camera.h"
#include <vector>


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
	mult = 1;
	
}

Camera::Camera(float* poss, float* dirr, float scalee, float ress, float focll, float mass,float rspann, float rress, int multt)
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
	mult = multt;
}

void Camera::take_pic(SDL_Renderer* render, int** allorder, int index, int batch_size)
{

	
	for (int i = index; i < index + batch_size; i++)
	{
			bool draw = false;
			float X = allorder[i][0];
			float Y = allorder[i][1];
			
			Ray ray = point(X,Y);
			draw = ray.trace();
			
	
		
			if (draw)
			{
				SDL_SetRenderDrawColor(render, 255 * exp(-ray.interval/40), 0, 255 * exp(-ray.interval/40), 255);
				SDL_Rect* dest = new SDL_Rect;
				*dest = { int(X) * mult, int(Y) * mult, mult, mult };
				SDL_RenderFillRect(render, dest);
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
	float dirrr[4] = { 0,dirr[0],dirr[1],dirr[2] };
	Quat dir_quat = Quat(dirrr);
	dir_quat = dir * dir_quat * dir.invize();
	dirr[0] = dir_quat.wijk[1];
	dirr[1] = dir_quat.wijk[2];
	dirr[2] = dir_quat.wijk[3];



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
