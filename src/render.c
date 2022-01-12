#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

float camera_pos_x = 0.0f;
float camera_pos_y = 0.0f;
float camera_pos_z = 0.0f;
float camera_rot_x = 0.0f;
float camera_rot_y = 0.0f;
float camera_rot_z = 0.0f;

void camera (void)
{
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	
	glTranslatef (camera_pos_x, camera_pos_y, camera_pos_z);
	glRotatef (camera_pos_y, 0.0f, 1.0f, 0.0f);
	gluPerspective (60.0f, (float)1920.0f/1080.0f, 1.0f, 1000.0f);
	gluLookAt (0.0f, 0.0f, 125.0f, 0.0f, 0.0f, -1000.0f, 0.0f, 1.0f, 0.0f);
	/*glOrtho (-100.0f, 100.0f, -100.0f, 100.0f, -100.0f, 100.0f);*/
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
	glShadeModel (GL_SMOOTH);
}

void Render_System (void)
{
	static float i = 0;
	/* Make the camera for every frame */
	camera ();
	
	/* Removes the back of the polygon
	glEnable (GL_CULL_FACE);*/
	glEnable (GL_DEPTH_TEST);
	
	/* Simple OpenGL Render code */
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glRotatef (camera_rot_x, 1.0f, 0.0f, 0.0f);
	glRotatef (camera_rot_y, 0.0f, 1.0f, 0.0f);
	glRotatef (camera_rot_z, 0.0f, 0.0f, 1.0f);
	
	glPushMatrix ();
	glRotatef (i, 0.0f, 0.0f, 1.0f);
	
	glPolygonMode (GL_BACK, GL_LINE);
	
	/* The Triangle */
	float y_t = (-30.0f * sqrt (3) / 2);
	
	glTranslatef (0.0f, 0.0f, 0.1f);
	glTranslatef (0.0f, y_t / 2.0f, 0.0f);
	glBegin (GL_TRIANGLES);
		glColor3f (1.0f, 0.0f, 0.0f);
		glVertex3f (-15.0f, y_t, 0.0f);
		glColor3f (0.0f, 1.0f, 0.0f);
		glVertex3f (15.0f, y_t, 0.0f);
		glColor3f (0.0f, 0.0f, 1.0f);
		glVertex3f (0.0f, 0.0f, 0.0f);
	glEnd ();
	
	glPopMatrix ();
	/* Make the X, Y and Z lines */
	glBegin (GL_LINES);
		glColor3f (1.0f, 0.0f, 0.0f);
		glVertex3f (-50.0f, 0.0f, 0.0f);
		glVertex3f (50.0f, 0.0f, 0.0f);
		
		glColor3f (0.0f, 1.0f, 0.0f);
		glVertex3f (0.0f, -50.0f, 0.0f);
		glVertex3f (0.0f, 50.0f, 0.0f);
		
		glColor3f (0.0f, 0.0f, 1.0f);
		glVertex3f (0.0f, 0.0f, -50.0f);
		glVertex3f (0.0f, 0.0f, 50.0f);
	glEnd ();
	
	/* Make the grid */
	int j;
	glColor3f (0.1f, 0.1f, 0.1f);
	for (j = -50; j <= 50; j += 10)
	{
		if (j == 0)
			continue;
		glLoadIdentity ();
		glRotatef (camera_rot_x, 1.0f, 0.0f, 0.0f);
		glRotatef (camera_rot_y, 0.0f, 1.0f, 0.0f);
		glRotatef (camera_rot_z, 0.0f, 0.0f, 1.0f);
		glTranslatef (0.0f, (float) j, 0.0f);
		
		
		glBegin (GL_LINES);
			glVertex3f (-50.0f, 0.0f, 0.0f);
			glVertex3f (50.0f, 0.0f, 0.0f);
		glEnd ();
	}
	for (j = -50; j <= 50; j += 10)
	{
		if (j == 0)
			continue;
		glLoadIdentity ();
		glRotatef (camera_rot_x, 1.0f, 0.0f, 0.0f);
		glRotatef (camera_rot_y, 0.0f, 1.0f, 0.0f);
		glRotatef (camera_rot_z, 0.0f, 0.0f, 1.0f);
		glTranslatef ((float) j, 0.0f, 0.0f);
		
		
		glBegin (GL_LINES);
			glVertex3f (0.0f, -50.0f, 0.0f);
			glVertex3f (0.0f, 50.0f, 0.0f);
		glEnd ();
	}
	for (j = -50; j <= 50; j += 10)
	{
		if (j == 0)
			continue;
		glLoadIdentity ();
		glRotatef (camera_rot_x, 1.0f, 0.0f, 0.0f);
		glRotatef (camera_rot_y, 0.0f, 1.0f, 0.0f);
		glRotatef (camera_rot_z, 0.0f, 0.0f, 1.0f);
		glTranslatef ((float) j, 0.0f, 0.0f);
		
		
		glBegin (GL_LINES);
			glVertex3f (0.0f, 0.0f, -50.0f);
			glVertex3f (0.0f, 0.0f, 50.0f);
		glEnd ();
	}
	for (j = -50; j <= 50; j += 10)
	{
		if (j == 0)
			continue;
		glLoadIdentity ();
		glRotatef (camera_rot_x, 1.0f, 0.0f, 0.0f);
		glRotatef (camera_rot_y, 0.0f, 1.0f, 0.0f);
		glRotatef (camera_rot_z, 0.0f, 0.0f, 1.0f);
		glTranslatef (0.0f, 0.0f, (float) j);
		
		
		glBegin (GL_LINES);
			glVertex3f (-50.0f, 0.0f, 0.0f);
			glVertex3f (50.0f, 0.0f, 0.0f);
		glEnd ();
	}
	for (j = -50; j <= 50; j += 10)
	{
		if (j == 0)
			continue;
		glLoadIdentity ();
		glRotatef (camera_rot_x, 1.0f, 0.0f, 0.0f);
		glRotatef (camera_rot_y, 0.0f, 1.0f, 0.0f);
		glRotatef (camera_rot_z, 0.0f, 0.0f, 1.0f);
		glTranslatef (0.0f, (float) j, 0.0f);
		
		
		glBegin (GL_LINES);
			glVertex3f (0.0f, 0.0f, -50.0f);
			glVertex3f (0.0f, 0.0f, 50.0f);
		glEnd ();
	}
	for (j = -50; j <= 50; j += 10)
	{
		if (j == 0)
			continue;
		glLoadIdentity ();
		glRotatef (camera_rot_x, 1.0f, 0.0f, 0.0f);
		glRotatef (camera_rot_y, 0.0f, 1.0f, 0.0f);
		glRotatef (camera_rot_z, 0.0f, 0.0f, 1.0f);
		glTranslatef (0.0f, 0.0f, (float) j);
		
		
		glBegin (GL_LINES);
			glVertex3f (0.0f, -50.0f, 0.0f);
			glVertex3f (0.0f, 50.0f, 0.0f);
		glEnd ();
	}
	
	glLoadIdentity ();
	glRotatef (camera_rot_x, 1.0f, 0.0f, 0.0f);
	glRotatef (camera_rot_y, 0.0f, 1.0f, 0.0f);
	glRotatef (camera_rot_z, 0.0f, 0.0f, 1.0f);
	
	/* The Floor */
	glBegin (GL_TRIANGLES);
		glColor3f (1.0f, 0.0f, 0.0f);
		glVertex3f (-50.0f, -50.0f, 50.0f);
		glColor3f (0.0f, 1.0f, 0.0f);
		glVertex3f (50.0f, -50.0f, 50.0f);
		glColor3f (0.0f, 0.0f, 1.0f);
		glVertex3f (50.0f, -50.0f, -50.0f);
		
		glColor3f (0.0f, 0.0f, 1.0f);
		glVertex3f (50.0f, -50.0f, -50.0f);
		glColor3f (0.0f, 1.0f, 0.0f);
		glVertex3f (-50.0f, -50.0f, -50.0f);
		glColor3f (1.0f, 0.0f, 0.0f);
		glVertex3f (-50.0f, -50.0f, 50.0f);
	glEnd ();
	/* We need to swapbuffers after render */
	/*glFlush ();*/
	SDL_GL_SwapBuffers ();
	
	i += 1.0f;
	
	glLoadIdentity ();
	
	return;
}

