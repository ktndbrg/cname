#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>

void Init_Engine (void);

void Input_System (void);
void Script_Engine (void);
void Render_System (void);
void Audio_System (void);

void Frames_Per_Seconds (void);

char run_flag;

int main (void)
{
	Init_Engine ();
	SDL_ShowCursor(0);
	
	Frames_Per_Seconds ();
	
	run_flag = 1;
	while (run_flag)
	{
		Input_System ();
		Script_Engine ();
		Render_System ();
		Audio_System ();
	}
	
	return 0;
}

