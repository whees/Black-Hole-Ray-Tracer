#include "Ray.h"
#include <cmath>
#include <iostream>



using namespace std;



Ray::Ray()
{
	float init[4] = { 0,0,0,0 };

	pos = Quat(init);
	axis = Quat(init);
	p = 0;
	u = 1 / pos.norm();
	M = 1;
	span = float(2.0 * 3.1415);
	RES = 100;
	tdot = span / RES;
	interval = 0;
	
	
}

Ray::Ray(float* wijk,float* xyz, float pp, float MM, float ss, float RR)
{
	span = ss;
	RES = RR;
	tdot = span / (RES - 1);
	pos = Quat(wijk);
	float ct2 = sin(tdot / 2);

	float xyzz[4] = { cos(tdot/2),ct2 *xyz[0],ct2 * xyz[1], ct2 * xyz[2]};
	
	axis = Quat(xyzz);
	p = pp;
	M = MM;
	u = 1 / pos.norm();
	interval = 0;



}

float Ray::pdot()
{

	return 3 * M * u * u - u;
	

}

bool Ray::trace()
{
	
	bool out = false;


	for (int i = 0; i < RES; i++)
	{
	
		if (pos.wijk[3] > 10)
		{
			if (pos.wijk[3] < 12 && sin(pos.wijk[1]*2) > cos(pos.wijk[2]*2))
				out = true;
			break;
		}
		else if(pos.norm() < 2*M || pos.norm() > 20)
		{
			break;
		}

		
	
		float r = 1 / u;
		float a = (1 - p * r * tdot);
		pos = axis * pos * axis.invize();
		for (int i = 0; i < 4; i++)
		{
			pos.wijk[i] *= a;
		}

		float new_r = pos.norm();
		interval += float(sqrt(pow(pos.norm() - r, 2) + pow(r * tdot, 2)));

		p += tdot * pdot();
		u = 1 / new_r;


	}


	return out;
}

