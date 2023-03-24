#include <cmath>
#include <iostream>
#pragma once

using namespace std;




class Quat
{
public:
	float wijk[4];

	~Quat();
	Quat();
	Quat(float* abcd);

	float norm();

	Quat invize();
	Quat operator*(Quat opp);
	void show()
	{
		cout << wijk[0] << " + " << wijk[1] << "i + " << wijk[2] << "j + " << wijk[3] << "k";
		return;
	}
	


};
