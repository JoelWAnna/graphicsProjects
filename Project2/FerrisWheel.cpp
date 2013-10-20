/*
 * Ground.cpp: A class for drawing the ground.
 *
 * (c) 2001-2002: Stephen Chenney, University of Wisconsin at Madison.
 */


#include "FerrisWheel.h"
#include "libtarga.h"
#include <stdio.h>
#include <GL/glu.h>

// Destructor
FerrisWheel::~FerrisWheel(void)
{
    if ( initialized )
    {
	glDeleteLists(display_list, 1);
    }
}


// Initializer. Returns false if something went wrong, 
bool
FerrisWheel::Initialize(void)
{
	// Create the display list.
    display_list = glGenLists(1);
    glNewList(display_list, GL_COMPILE);
	/*
	glBegin(GL_QUAD_STRIP);
	glColor3f(0, 0, 0);
	glVertex3f(5.0, 0.0, 1.0);
	glVertex3f(15.0, 0.0, 1.0);
	glVertex3f(6.0, 0.0, 2.0);
	glVertex3f(14.0, 0.0, 2.0);
	
	glColor3f(1, 0, 0);
	glVertex3f(5.0, 0.0, 1.0);
	glVertex3f(6.0, 0.0, 2.0);
	glVertex3f(0.0, 0.0, 7.0);
	glVertex3f(1.0, 0.0, 8.0);

	
	glColor3f(1, .5, 0);
	glVertex3f(0.0, 0.0, 7.0);
	glVertex3f(1.0, 0.0, 8.0);
	glVertex3f(0.0, 0.0, 17.0);
	glVertex3f(1.0, 0.0, 16.0);

	
	glColor3f(1, 1, 0);
	glVertex3f(0.0, 0.0, 17.0);
	glVertex3f(1.0, 0.0, 16.0);
	glVertex3f(5.0, 0.0, 23.0);
	glVertex3f(6.0, 0.0, 22.0);

	glColor3f(0, 1, 0);
	glVertex3f(5.0, 0.0, 23.0);
	glVertex3f(6.0, 0.0, 22.0);
	glVertex3f(16.0, 0.0, 23.0);
	glVertex3f(15.0, 0.0, 22.0);

	
	glColor3f(0, 0, 1);
	glVertex3f(16.0, 0.0, 23.0);
	glVertex3f(15.0, 0.0, 22.0);
	glVertex3f(20.0, 0.0, 17.0);
	glVertex3f(19.0, 0.0, 16.0);
	
	glColor3f(.5, 0, 1);
	glVertex3f(20.0, 0.0, 17.0);
	glVertex3f(19.0, 0.0, 16.0);
	glVertex3f(20.0, 0.0, 7.0);
	glVertex3f(19.0, 0.0, 8.0);

	glColor3f(1, 1, 1);
	glVertex3f(20.0, 0.0, 7.0);
	glVertex3f(19.0, 0.0, 8.0);
	glVertex3f(15.0, 0.0, 1.0);
	glVertex3f(14.0, 0.0, 2.0);

	glEnd();*/
	
	glBegin(GL_QUAD_STRIP);

	glColor3f(0, 0, 0);
	glVertex3f(5.0, 0.0, 1.0);
	glVertex3f(15.0, 0.0, 1.0);
	glVertex3f(5.5, 0.0, 2.0);
	glVertex3f(14.5, 0.0, 2.0);
	
	glVertex3f(5.5, 2.0, 2.0);
	glVertex3f(14.5, 2.0, 2.0);
	glVertex3f(5.0, 2.0, 1.0);
	glVertex3f(15.0, 2.0, 1.0);

	glVertex3f(5.5, 2.0, 2.0);
	glVertex3f(14.5, 2.0, 2.0);
	glVertex3f(5.0, 0.0, 1.0);
	glVertex3f(15.0, 0.0, 1.0);

	
	glColor3f(1, 0, 0);
	glVertex3f(5.0, 0.0, 1.0);
	glVertex3f(5.5, 0.0, 2.0);
	glVertex3f(0.0, 0.0, 7.0);
	glVertex3f(1.0, 0.0, 7.5);

	glVertex3f(0.0, 2.0, 7.0);
	glVertex3f(1.0, 2.0, 7.5);
	glVertex3f(5.0, 2.0, 1.0);
	glVertex3f(5.5, 2.0, 2.0);

	
	glColor3f(1, .5, 0);
	glVertex3f(0.0, 0.0, 7.0);
	glVertex3f(1.0, 0.0, 7.5);
	glVertex3f(0.0, 0.0, 17.0);
	glVertex3f(1.0, 0.0, 16.5);
	
	glVertex3f(0.0, 2.0, 17.0);
	glVertex3f(1.0, 2.0, 16.5);
	glVertex3f(0.0, 2.0, 7.0);
	glVertex3f(1.0, 2.0, 7.5);

	
	glColor3f(1, 1, 0);
	glVertex3f(0.0, 0.0, 17.0);
	glVertex3f(1.0, 0.0, 16.5);
	glVertex3f(5.0, 0.0, 23.0);
	glVertex3f(5.5, 0.0, 22.0);
	
	glVertex3f(5.0, 2.0, 23.0);
	glVertex3f(5.5, 2.0, 22.0);
	glVertex3f(0.0, 2.0, 17.0);
	glVertex3f(1.0, 2.0, 16.5);

	glColor3f(0, 1, 0);
	glVertex3f(5.0, 0.0, 23.0);
	glVertex3f(5.5, 0.0, 22.0);
	glVertex3f(16.0, 0.0, 23.0);
	glVertex3f(15.5, 0.0, 22.0);
	
	glVertex3f(16.0, 2.0, 23.0);
	glVertex3f(15.5, 2.0, 22.0);
	glVertex3f(5.0, 2.0, 23.0);
	glVertex3f(5.5, 2.0, 22.0);

	
	glColor3f(0, 0, 1);
	glVertex3f(16.0, 0.0, 23.0);
	glVertex3f(15.5, 0.0, 22.0);
	glVertex3f(20.0, 0.0, 17.0);
	glVertex3f(19.0, 0.0, 16.5);
	
	glVertex3f(20.0, 2.0, 17.0);
	glVertex3f(19.0, 2.0, 16.5);
	glVertex3f(16.0, 2.0, 23.0);
	glVertex3f(15.5, 2.0, 22.0);
	
	glColor3f(.5, 0, 1);
	glVertex3f(20.0, 0.0, 17.0);
	glVertex3f(19.0, 0.0, 16.5);
	glVertex3f(20.0, 0.0, 7.0);
	glVertex3f(19.0, 0.0, 7.5);
	
	glVertex3f(20.0, 2.0, 7.0);
	glVertex3f(19.0, 2.0, 7.5);
	glVertex3f(20.0, 2.0, 17.0);
	glVertex3f(19.0, 2.0, 16.5);

	glColor3f(1, 1, 1);
	glVertex3f(20.0, 0.0, 7.0);
	glVertex3f(19.0, 0.0, 7.5);
	glVertex3f(15.0, 0.0, 1.0);
	glVertex3f(14.5, 0.0, 2.0);

	glVertex3f(20.0, 2.0, 7.0);
	glVertex3f(19.0, 2.0, 7.5);
	glVertex3f(15.0, 2.0, 1.0);
	glVertex3f(14.5, 2.0, 2.0);

	glEnd();
	/*a = 0.0 ;
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0, 0.0, 1.0);
	for (int i = 0 ; i < res ; i++ ){
		glVertex3f(cos(a), sin(a), 4.0);
		a += d ;
	}
	glEnd() ;*/

	

	/*
	glBegin(GL_TRIANGLES);
	glColor3f(.5,0,.5);
	glVertex3f(35, 35, -2);
	glVertex3f(35, -35, -2);
	glVertex3f(-35, 35, -2);
	
	glColor3f(.5,.5, 0);
	glVertex3f(35, 35, 2);
	glVertex3f(35, -35, 2);
	glVertex3f(-35, 35, 2);
	glEnd();
	glBegin(GL_QUADS);
		
	  glColor3f(.75,0,.75);
	  glVertex3f(20, 20, 1);
	  glVertex3f(-20, 20, 1);
	  glVertex3f(20, -20, 1);
	  glVertex3f(-20, -20, 1);
	glEnd();
	glBegin(GL_QUADS);
	// front
      glColor3f(1, 0, 0);
      glVertex3f(-1, 1, 1);
      glVertex3f(-1, -1, 1);
      glVertex3f(1, -1, 1);
      glVertex3f(1, 1, 1);

      // back
      glColor3f(0, 1, 0);
      glVertex3f(-1, 1, -1);
      glVertex3f(1, 1, -1);
      glVertex3f(1, -1, -1);
      glVertex3f(-1, -1, -1);

      // top
      glColor3f(0, 0, 1);
      glVertex3f(-1, 1, -1);
      glVertex3f(-1, 1, 1);
      glVertex3f(1, 1, 1);
      glVertex3f(1, 1, -1);

      // bottom
      glColor3f(1, 1, 0);
      glVertex3f(-1, -1, -1);
      glVertex3f(1, -1, -1);
      glVertex3f(1, -1, 1);
      glVertex3f(-1, -1, 1);

      // left
      glColor3f(0, 1, 1);
      glVertex3f(-1, 1, -1);
      glVertex3f(-1, -1, -1);
      glVertex3f(-1, -1, 1);
      glVertex3f(-1, 1, 1);

      // right
      glColor3f(1, 0, 1);
      glVertex3f(1, 1, 1);
      glVertex3f(1, -1, 1);
      glVertex3f(1, -1, -1);
      glVertex3f(1, 1, -1);
   glEnd();
   */
    glEndList();

    // We only do all this stuff once, when the GL context is first set up.
    initialized = true;

    return true;
}


// Draw just calls the display list we set up earlier.
void
FerrisWheel::Draw(void)
{
	static float angle=0;
	angle +=0.5;

    glPushMatrix();
	glTranslatef(10,0,13);
    glRotatef((float)angle, 0.0f, 1.0f, 0.0f);
	glTranslatef(-10,0,-13);
    glCallList(display_list);
    glPopMatrix();
}


