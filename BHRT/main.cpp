#include <iostream>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "Quat.h"
#include "Ray.h"
#include "SDL.h"
#include "Camera.h"
#undef main

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif


using namespace std;


float wijk[4] = { 0,0,0,-10 };
float dire[4] = { 1,0,0,0 };
float scale = 0.1;
float RES = 800;
float focl = 0.05;
float mass = 1.36;
float rspan = 4 * 3.14;
float rres = 1000;
float ang = 0;
bool done = false;
Camera* camera = new Camera(wijk, dire, scale, RES, focl, mass, rspan, rres);
SDL_Window* window = SDL_CreateWindow("Output", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, RES, RES, 0);
SDL_Renderer* render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
SDL_Surface* surface = SDL_GetWindowSurface(window);

SDL_Event event;
int main()
{
	
	int k = 0;
	
	while (!done)
	{
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

		camera->take_pic(render);

		SDL_RenderPresent(render);

		k++;
	}

	_CrtDumpMemoryLeaks();
	return 0;
}


/*
* 
* char buffer[32]; // The filename buffer.
		snprintf(buffer, sizeof(char) * 32, "out/file%i.bmp", k);

		k++;
SDL_Surface* sshot = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
SDL_RenderReadPixels(render, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
SDL_SaveBMP(sshot, buffer);
SDL_FreeSurface(sshot);

cout << t << "\n";
t++;
*/
