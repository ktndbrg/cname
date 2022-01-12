#include <stdio.h>
#include <stdlib.h>

#include <SDL/SDL.h>

#define SCREEN_WIDTH 1920//480
#define SCREEN_HEIGHT 1080//272
#define SCREEN_BITS 32//16

unsigned char *keyevent;

static int fs_flag = 0;

void Input_System (void)
{
	extern char run_flag;
	
	extern float camera_pos_x;
	extern float camera_pos_y;
	extern float camera_pos_z;
	extern float camera_rot_x;
	extern float camera_rot_y;
	extern float camera_rot_z;
	
	SDL_PumpEvents();
	
	keyevent = SDL_GetKeyState(NULL);
	
	if (keyevent[SDLK_ESCAPE] || keyevent[SDLK_q])
	{
		run_flag = 0;
	}
	
	if (keyevent[SDLK_f])
	{
		if (fs_flag == 0)
		{
			SDL_SetVideoMode (SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BITS, SDL_FULLSCREEN | SDL_OPENGL);
			++fs_flag;
		}
		else
		{
			SDL_SetVideoMode (SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BITS, SDL_OPENGL);
			--fs_flag;
		}
	}
	
	if (keyevent[SDLK_4])
	{
		camera_pos_x = 0;
		camera_pos_y = 0;
		camera_pos_z = 0;
		camera_rot_x = 0;
		camera_rot_y = 0;
		camera_rot_z = 0;
	}
	
	/* Movement */
	if (keyevent[SDLK_j])
	{
		if (camera_rot_y >= -180)
			camera_rot_y -= 1.0f;
	}
	if (keyevent[SDLK_l])
	{
		if (camera_rot_y <= 180)
			camera_rot_y += 1.0f;
	}
	if (keyevent[SDLK_i])
	{
		if (camera_rot_x <= 180)
			camera_rot_x += 1.0f;
	}
	if (keyevent[SDLK_k])
	{
		if (camera_rot_x >= -180)
			camera_rot_x -= 1.0f;
	}
	
	if (keyevent[SDLK_LEFT])
	{
		camera_pos_x -= 0.01f;
	}
	if (keyevent[SDLK_RIGHT])
	{
		camera_pos_x += 0.01f;
	}
	if (keyevent[SDLK_UP])
	{
		camera_pos_y += 0.01f;
	}
	if (keyevent[SDLK_DOWN])
	{
		camera_pos_y -= 0.01f;
	}
	
	return;
}

