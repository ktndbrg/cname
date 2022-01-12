#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <SDL/SDL.h>

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
extern sound_t cannon, explosion;

#define MAX_PLAYING_SOUNDS 10
playing_t playing [MAX_PLAYING_SOUNDS];

#define VOLUME_PER_SOUND SDL_MIX_MAXVOLUME / 2
int LoadAndConvertSound (char *filename, SDL_AudioSpec *spec, sound_p sound);
void AudioCallback (void *user_data, Uint8 *audio, int length);
void ClearPlayingSounds (void);
int PlaySound (sound_p sound);
void CloseAudio (void);

extern unsigned char *keyevent;

void Audio_System (void)
{
	SDL_PumpEvents ();
	
	keyevent = SDL_GetKeyState(NULL);
	if (keyevent[SDLK_1])
	{
		PlaySound (&cannon);
	}
	if (keyevent[SDLK_2])
	{
		PlaySound (&explosion);
	}
	
	return;
}

void AudioCallback (void *user_data, Uint8 *audio, int length)
{
	int i;
	
	memset (audio, 0, length);
	
	for (i = 0; i < MAX_PLAYING_SOUNDS; i++)
	{
		if (playing[i].active)
		{
			Uint8 *sound_buf;
			Uint32 sound_len;
			
			sound_buf = playing[i].sound->samples;
			sound_buf += playing[i].position;
			
			if ((playing[i].position + length) > playing[i].sound->length)
			{
				sound_len = playing[i].sound->length - playing[i].position;
			}
			else
			{
				sound_len = length;
			}
			
			SDL_MixAudio (audio, sound_buf, sound_len, VOLUME_PER_SOUND);
			
			playing[i].position += length;
			
			if (playing[i].position >= playing[i].sound->length)
			{
				playing[i].active = 0;
			}
		}
	}
}

int LoadAndConvertSound (char *filename, SDL_AudioSpec *spec, sound_p sound)
{
	SDL_AudioCVT cvt;
	SDL_AudioSpec loaded;
	Uint8 *new_buf;
	
	if (SDL_LoadWAV (filename, &loaded, &sound->samples, &sound->length) == NULL)
	{
		fprintf (stderr, "Unable to load sound: %s\n", SDL_GetError ());
		exit (1);
	}
	
	if (SDL_BuildAudioCVT (&cvt, loaded.format, loaded.channels, loaded.freq, spec->format, spec->channels, spec->freq) < 0)
	{
		fprintf (stderr, "Unablec build CVT: %s\n", SDL_GetError ());
		exit (1);
	}
	
	cvt.len = sound->length;
	new_buf = (Uint8 *) malloc (cvt.len * cvt.len_mult);
	if (new_buf == NULL)
	{
		fprintf (stderr, "Errro allocation memory\n");
		SDL_FreeWAV (sound->samples);
		exit (1);
	}
	
	memcpy (new_buf, sound->samples, sound->length);
	
	cvt.buf = new_buf;
	if (SDL_ConvertAudio (&cvt) < 0)
	{
		fprintf (stderr, "Unable to load sound: %s\n", SDL_GetError ());
		exit (1);
	}
	SDL_FreeWAV (sound->samples);
	sound->samples = new_buf;
	sound->length = sound->length * cvt.len_mult;
	
	return 0;
}

void ClearPlayingSounds (void)
{
	int i;
	for (i = 0; i < MAX_PLAYING_SOUNDS; i++)
	{
		playing[i].active = 0;
	}
}

int PlaySound (sound_p sound)
{
	int i;
	for (i = 0; i < MAX_PLAYING_SOUNDS; i++)
	{
		if (playing[i].active == 0)
			break;
	}
	
	if (i == MAX_PLAYING_SOUNDS)
	{
		return 1;
	}
	
	SDL_LockAudio ();
	playing[i].active = 1;
	playing[i].sound = sound;
	playing[i].position = 0;
	SDL_UnlockAudio ();
	
	return 0;
}

void CloseAudio (void)
{
	SDL_PauseAudio (1);
	SDL_LockAudio ();
	
	free (cannon.samples);
	free (explosion.samples);
	
	SDL_UnlockAudio ();
	
	return;
}

