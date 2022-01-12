#include <stdio.h>
#include <stdlib.h>

#include <SDL/SDL.h>
/* Fedora has the tcl header outside the tcl folder
But Debian/Ubuntu has it in the commented version!*/
/* #include <tcl/tcl.h> */
#include <tcl/tcl.h>
#include <GL/gl.h>
#include <GL/glu.h>

/* We need a 16:9 display, so divide width by 16 and multiply by 9 
* We need to divide with a float in order not to lose some numbers, then cast it as a int to pass to SDL
* Now, BBB screen is 480x272, but 480/16*9 = 270, but this shouldn't make too much of a difference */
#define SCREEN_WIDTH 1920//480
#define SCREEN_HEIGHT 1080//272
#define SCREEN_BITS 32

/* From the SDL Book */
typedef struct sound_s {
	Uint8 *samples;
	Uint32 length;
} sound_t, *sound_p;

typedef struct playing_s {
	int active;
	sound_p sound;
	Uint32 position;
} playing_t, *playing_p;

#define VOLUME_PER_SOUND SDL_MIX_MAXVOLUME / 2
int LoadAndConvertSound (char *filename, SDL_AudioSpec *spec, sound_p sound);
void AudioCallback (void *user_data, Uint8 *audio, int length);
void ClearPlayingSounds (void);
int PlaySound (sound_p sound);
void CloseAudio (void);
void sound (void);

void Init_SDL (void);
void Init_OpenGL (void);
void Init_TCL (void);
void Clean_Up (void);

Tcl_Interp *p_interp;

void Init_Engine (void)
{
	Init_SDL ();
	
	Init_OpenGL ();
	
	Init_TCL ();
	
	return;
}

void Init_SDL (void)
{
	/* Initialize SDL_VIDEO and AUDIO System */
	SDL_Surface *p_screen;
	if ((SDL_Init (SDL_INIT_VIDEO | SDL_INIT_AUDIO)) != 0)
	{
		/* If SDL_Init returns with something other than 0, an error has occurd */
		fprintf (stderr, "Error initializing SDL: %s\n", SDL_GetError ());
		exit (1);
	}
	atexit (SDL_Quit);
	atexit (SDL_CloseAudio);
	sound ();
	
	/* Sets the minimum bit sizes for color */
	SDL_GL_SetAttribute (SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute (SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute (SDL_GL_BLUE_SIZE, 8);
	
	/* Enables V-Sync (Doublebuffer) */
	SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, 1);
	
	/* This seems to give a problem if fs_flag != 0. Need a check out (fs_flag)?SDL_FULLSCREEN:0*/
	if ((p_screen = SDL_SetVideoMode (SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BITS, SDL_OPENGL)) == NULL)
	{
		fprintf (stderr, "Error setting videomode: %s\n", SDL_GetError ());
		exit (1);
	}
	
	/* Title of App, also icon pic */
	SDL_WM_SetCaption ("Qualker", "icon.png");
	
	return;
}

void Init_OpenGL (void)
{
	/* We need the viewport to be same as screen size */
	glViewport (0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glClearColor (0.2f, 0.2f, 0.2f, 0.0f);
	
	return;
}

void Init_TCL (void)
{
	/* Create and interpretator */
	p_interp = Tcl_CreateInterp ();
	
	/* Link Function */
	/*Tcl_CreateObjCommand (p_interp, "play_sound", c_sound, (ClientData) 0, NULL);*/
	
	/* Link the variables */
	/*Tcl_LinkVar (p_interp, "input", (char *) &userinput, TCL_LINK_INT);*/
	
	Tcl_EvalFile (p_interp, "main_script.tcl");
	
	atexit (Clean_Up);
	
	return;
}

sound_t cannon, explosion;
void sound (void)
{
	SDL_AudioSpec desired, obtained;
	
	
	desired.freq = 44100;
	desired.format = AUDIO_S16;
	desired.samples = 4096;
	desired.channels = 2;
	desired.callback = AudioCallback;
	desired.userdata = NULL;
	
	SDL_OpenAudio (&desired, &obtained);
	
	LoadAndConvertSound ("explosion.wav", &obtained, &explosion);
	LoadAndConvertSound ("cannon.wav", &obtained, &cannon);
	
	ClearPlayingSounds ();
	
	SDL_PauseAudio (0);
	
	atexit (CloseAudio);
}

