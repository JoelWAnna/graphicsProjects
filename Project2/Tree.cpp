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
	
	newTree(-40, 0, 2.0, 3.0, 0.5f, 1.0f);
	newTree(-40, 4, 2.0, 3.0, 0.25f, 1.5f);
	newTree(45, 0, 1.5, 4.0, 1.0, 2.0);
	newTree(0, 30, 3.0, 6.0, 1.5, 3.0);
	glEnd();
	
    glEndList();

    // We only do all this stuff once, when the GL context is first set up.
    initialized = true;

    return true;
}


// Draw just calls the display list we set up earlier.
void
Tree::Draw(void)
{
	
    glPushMatrix();
	glDisable(GL_CULL_FACE);
    glCallList(display_list);
	glEnable(GL_CULL_FACE);
    glPopMatrix();
}


