/*
 * Ground.cpp: A class for drawing the ground.
 *
 * (c) 2001-2002: Stephen Chenney, University of Wisconsin at Madison.
 */


#include "Tree.h"
#include "libtarga.h"
#include <stdio.h>
#include <GL/glu.h>

// Destructor
Tree::~Tree(void)
{
    if ( initialized )
    {
	glDeleteLists(display_list, 1);
    }
}


// Initializer. Returns false if something went wrong, 
bool
Tree::Initialize(void)
{
	// Create the display list.
    display_list = glGenLists(1);
    glNewList(display_list, GL_COMPILE);

	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	
	glTranslatef(-50, 0, 0);
	glColor3f(.5, .2, 0);
	gluCylinder(quadratic,.5f,.5f,2.0f,32,32);
	
	glTranslatef(0, 0, 1.9);
	//GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	
	glColor3f(0, 1, 0);
	for (int i = 0; i < 10; ++i)
	{
		gluCylinder(quadratic,1.0f - .1*i, (1.0f - .1*i)/2 ,.3f,32,32);
		glTranslatef(0, 0, .25f);
	}

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
Tree::Draw(void)
{
	static float angle=0;
	angle +=0.5;

    glPushMatrix();
    glCallList(display_list);
    glPopMatrix();
}


