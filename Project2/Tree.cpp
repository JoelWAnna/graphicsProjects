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

void Tree::newTree(int x, int y, float heightT, float heightL, float radiusT, float radiusL)
{
	
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	
	glTranslatef(x, y, 0);
	glColor3f(.5, .2, 0);
	gluCylinder(quadratic, radiusT, radiusT, heightT,32,32);
	
	glTranslatef(0, 0, heightT-.1f);
	//GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	
	glColor3f(0, 1, 0);
	for (int i = 0; i < 10; ++i)
	{
		gluCylinder(quadratic,radiusL - (radiusL/10)*i, (radiusL - (radiusL/10)*i)/2 ,heightL/10,32,32);
		glTranslatef(0, 0, heightL/10 -.05f);
	}
	
	glTranslatef(0, 0, -(heightL/10 -.05f)*10);
	glTranslatef(0, 0, -(heightT-.1f));
	glTranslatef(-x, -y, 0);
}
// Initializer. Returns false if something went wrong, 
bool
Tree::Initialize(void)
{
	// Create the display list.
    display_list = glGenLists(1);
    glNewList(display_list, GL_COMPILE);
	
	newTree(-45, 0, 2.0, 3.0, 0.5f, 1.0f);
	newTree(-45, 4, 2.0, 3.0, 0.25f, 1.5f);
	newTree(45, 0, 1.5, 4.0, 1.0, 2.0);
	newTree(0, 30, 3.0, 6.0, 1.5, 3.0);
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


