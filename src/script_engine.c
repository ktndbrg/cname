#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL/SDL.h>

/* Fedora has the tcl header outside the tcl folder
But Debian/Ubuntu has it in the commented version!*/
/* #include <tcl/tcl.h> */
#include <tcl/tcl.h>

static int status = 0;

extern Tcl_Interp *p_interp;

double time_scale;
int last_tick, tick, frames;
int timer1;
int timer2;

void Script_Engine (void)
{
	/* Evaluate the file */
	
	status = Tcl_Eval (p_interp, "MainProc");
	
	if (status != TCL_OK)
	{
		fprintf (stderr, "Error is script: %s\n", Tcl_GetStringResult (p_interp));
		exit (1);
	}
	
	last_tick = tick;
	tick = SDL_GetTicks();
	time_scale = (double) (tick - last_tick) / 30.0;
	frames++;
	
	return;
}

void Frames_Per_Seconds (void)
{
	time_scale = 1;
	frames = 0;
	timer1 = time (NULL);
	srand (timer1);
	last_tick = SDL_GetTicks ();
}

void Clean_Up (void)
{
	Tcl_DeleteInterp (p_interp);
	
	timer2 = time (NULL);
	printf ("Avarage FPS: %.0f\n", (float)(frames / (timer2 - timer1)));
	
	return;
}

