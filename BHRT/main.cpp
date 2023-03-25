#include <iostream>
#include <stdlib.h>
#include "Quat.h"
#include "Ray.h"
#include "SDL.h"
#include "Camera.h"
#include "randomize.cpp"
#include <time.h>
#include <cstdlib>
#undef main
using namespace std;



void scramble(int** arr, int RES)
{
	for (int i = 0; i < RES; i++)
	{
		for (int j = 0; j < RES; j++)
		{
			int index = rand() % (RES*RES);
			int* dummy = arr[i * RES + j];
			arr[i * RES + j] = arr[index];
			arr[index] = dummy;
			
		}
	
	}

	
	return;
}


float wijk[4] = { 0,0,0,-10 };
float dire[4] = { 1,0,0,0 };
float scale = 0.1;
float mult = 4;
float RES = 200;
float focl = 0.05;
float mass = 1.1;
float rspan = 2 * 3.14;
float rres = 1000;
float ang = 0;
bool done = false;


int batch_side = 20;
int n_batch = pow(int(RES / batch_side), 2);
int last_batch_side = int(RES) % batch_side;
int** all_batches = new int*[RES * RES];


Camera* camera = new Camera(wijk, dire, scale, RES, focl, mass, rspan, rres,mult);
SDL_Window* window = SDL_CreateWindow("Output", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, RES*mult, RES * mult, 0);
SDL_Renderer* render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
SDL_Surface* surface = SDL_GetWindowSurface(window);
SDL_Event event;




int main()
{
	srand(time(NULL));
	if (last_batch_side > 0)
		n_batch += 1;
	else
		last_batch_side = batch_side;
	

	for (int i = 0; i < RES; i++)
	{
		for (int j = 0; j < RES; j++)
		{
			all_batches[int(i) * int(RES) + j] = new int[2];
			all_batches[int(i) * int(RES) + j][0] = i;
			all_batches[int(i) * int(RES) + j][1] = j;

		}
	}

	scramble(all_batches, RES);


	
	while (!done)
	{
		for (int i = 0; i < n_batch; i++)
		{
			while (SDL_PollEvent(&event)) {

				switch (event.type) {


				case SDL_KEYDOWN:
					// Handle any key presses here.
					switch (event.key.keysym.sym) {
					case SDLK_RIGHT:
						ang += 0.05;

						break;
					case SDLK_LEFT:
						ang -= 0.05;

						break;
					case SDLK_UP:
						focl *= 1.1;

						break;
					case SDLK_DOWN:
						focl /= 1.1;

						break;

					case SDLK_1:
						mass -= 0.01;

						break;
					case SDLK_2:
						mass += 0.01;

						break;

					default:
						break;
					}
					dire[0] = cos(ang);
					dire[2] = sin(ang);
					camera->dir = Quat(dire);
					camera->focl = focl;
					camera->Mass = mass;
					SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
					SDL_RenderClear(render);
					i = 0;

					break;



				case SDL_QUIT:
					done = true;
					break;

				default:
					break;
				}   // End switch
			}
			int this_batch_size = batch_side * batch_side;
			if (i == n_batch - 1)
			{
				this_batch_size = last_batch_side * last_batch_side;
			}
			int this_batch_index = i * batch_side * batch_side;
			cout << this_batch_index << endl;;
			camera->take_pic(render,all_batches,this_batch_index,this_batch_size);
			SDL_RenderPresent(render);

			

		}
	
	}

	return 0;
}


/*
while (SDL_PollEvent(&event)) {

			switch (event.type) {


			case SDL_KEYDOWN:
				// Handle any key presses here.
				switch (event.key.keysym.sym) {
				case SDLK_LEFT:
					ang += 0.1;

					break;
				case SDLK_RIGHT:
					ang -= 0.1;

					break;


				default:
					break;
				}
				dire[0] = cos(ang);
				dire[2] = sin(ang);
				camera->dir = Quat(dire);


				break;



			case SDL_QUIT:
				done = true;
				break;

			default:
				break;
			}   // End switch
		}

*/
