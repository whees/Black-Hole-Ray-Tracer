#include "Quat.h"
#include <cmath>


float dot(float* wijk, float* abcd, int dim)
{
	float out;
	
	out = 0;

	for (int i = 0; i < dim; i++)
	{
		out += *(wijk + i) * *(abcd + i);
	}

	return out;
}



Quat::Quat()
{
	for (int i = 0; i < 4; i++)
	{
		wijk[i] = 0;
	}

}

Quat::Quat(float* abcd)
{
	for (int i = 0; i < 4; i++)
	{
		wijk[i] = abcd[i];
	}

}




float Quat::norm()
{
	float half;
	half = dot(wijk, wijk, 4);
	float out = sqrt(half);
	return out;
	
}

Quat Quat::operator*(Quat opp)
{
	Quat out;
	float* mids;
	mids = new float[4];

	mids[0] = *(wijk) * *(opp.wijk) - *(wijk + 1) * *(opp.wijk + 1) - *(wijk + 2) * *(opp.wijk + 2) - *(wijk + 3) * *(opp.wijk + 3);
	mids[1] = *(wijk) * *(opp.wijk + 1) + *(wijk + 1) * *(opp.wijk) + *(wijk + 2) * *(opp.wijk + 3) - *(wijk + 3) * *(opp.wijk + 2);
	mids[2] = *(wijk) * *(opp.wijk + 2) - *(wijk + 1) * *(opp.wijk + 3) + *(wijk + 2) * *(opp.wijk) + *(wijk + 3) * *(opp.wijk + 1);
	mids[3] = *(wijk) * *(opp.wijk + 3) + *(wijk + 1) * *(opp.wijk + 2) - *(wijk + 2) * *(opp.wijk + 1) + *(wijk + 3) * *(opp.wijk + 0);
	

	out = Quat(mids);
	delete[] mids;

	return out;

}

Quat Quat::invize()
{
	
	float init[4] = { wijk[0]/norm(),-wijk[1]/norm(),-wijk[2]/norm(),-wijk[3]/norm()};
	return Quat(init);
}


Quat::~Quat()
{
	
}