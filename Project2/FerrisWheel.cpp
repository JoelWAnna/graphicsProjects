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
	glDeleteLists(display_list_frame, 1);
	glDeleteLists(display_list_wheel, 1);
    }
}
void Quad(GLfloat color[3], GLfloat p1[3] , GLfloat p2[3] , GLfloat p3[3] , GLfloat p4[3] , GLfloat width, int widx)
{
	glBegin(GL_QUAD_STRIP);
	GLfloat p5[3], p6[3], p7[3], p8[3];
	p5[0]=p1[0];
	p5[1]=p1[1];
	p5[2]=p1[2];
	p6[0]=p2[0];
	p6[1]=p2[1];
	p6[2]=p2[2];
	p7[0]=p3[0];
	p7[1]=p3[1];
	p7[2]=p3[2];
	p8[0]=p4[0];
	p8[1]=p4[1];
	p8[2]=p4[2];
	
	p5[widx]=p1[widx]+width;
	p6[widx]=p2[widx]+width;
	p7[widx]=p3[widx]+width;
	p8[widx]=p4[widx]+width;

	glColor3fv(color);
	
	glVertex3fv(p1);
	glVertex3fv(p2);
	glVertex3fv(p3);
	glVertex3fv(p4);
	glVertex3fv(p7);
	glVertex3fv(p8);
	glVertex3fv(p5);
	glVertex3fv(p6);
	glVertex3fv(p1);
	glVertex3fv(p2);
	glVertex3fv(p5);
	glVertex3fv(p6);
	
	glEnd();
}

void createFrame()
{	
	
	GLfloat  WHITE[3] = {0.33f,0,0.33f};
	{
//	GLfloat  WHITE[3] = {0,0,0.33f};
	GLfloat lb[3] = {7.5f, 0.0f, 11.0f};
	GLfloat rb[3] = {11.5f, 0.0f, 11.0f};
	GLfloat lu[3] = {8.0f, 0.0f, 13.0f};
	GLfloat ru[3] = {11.0f, 0.0f, 13.0f};
	Quad (WHITE,  lb, rb, lu, ru, 2.0f, 1);
	}
	{
//	GLfloat  WHITE[3] = {0,0,0.33f};
	GLfloat lb[3] = {7.5f, 0.0f, 11.0f};
	GLfloat rb[3] = {11.5f, 0.0f, 11.0f};
	GLfloat lu[3] = {8.0f, 0.0f, 9.0f};
	GLfloat ru[3] = {11.0f, 0.0f, 9.0f};
	Quad (WHITE,  lb, rb, lu, ru, 2.0f, 1);
	}
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
	{
	GLfloat  BLACK[3] = {0,0,0};
	GLfloat lb[3] = {9.0f, 0.5f, 20.0f};	
	GLfloat rb[3] = {9.0f, 0.5f, 2.0f};
	GLfloat lu[3] = {11.0f, 0.5f, 20.0f};
	GLfloat ru[3] = {11.0f, 0.5f, 2.0f};
	Quad (BLACK,  lb, rb, lu, ru, 1.0f, 1);
	}

	{
	GLfloat  BLACK[3] = {0,0,0};
	GLfloat lb[3] = {5.0f, 0.0f, 1.0f};
	GLfloat rb[3] = {15.0f, 0.0f, 1.0f};
	GLfloat lu[3] = {5.5f, 0.0f, 2.0f};
	GLfloat ru[3] = {14.5f, 0.0f, 2.0f};
	Quad (BLACK,  lb, rb, lu, ru, 2.0f, 1);
	}
/*	

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
	
	glVertex3f(5.0, 0.0, 1.0);
	glVertex3f(15.0, 0.0, 1.0);
	glVertex3f(5.5, 2.0, 2.0);
	glVertex3f(14.5, 2.0, 2.0);

	
	glVertex3f(5.5, 0.0, 2.0);
	glVertex3f(14.5, 0.0, 2.0);
	glVertex3f(5.0, 0.0, 1.0);
	glVertex3f(15.0, 0.0, 1.0);

	glEnd();*/
	{
	GLfloat  RED[3] = {1,0,0};
	GLfloat lb[3] = {5.0f, 0.0f, 1.0f};
	GLfloat rb[3] = {0.0f, 0.0f, 6.0f};
	GLfloat lu[3] = {5.5f, 0.0f, 2.0f};
	GLfloat ru[3] = {1.0f, 0.0f, 6.5f};
	Quad (RED,  lb, rb, lu, ru, 2.0f, 1);
	}/*
	glBegin(GL_QUAD_STRIP);
	glColor3f(1, 0, 0);
	glVertex3f(5.0, 0.0, 1.0);
	glVertex3f(5.5, 0.0, 2.0);
	glVertex3f(0.0, 0.0, 6.0);
	glVertex3f(1.0, 0.0, 6.5);

	glVertex3f(0.0, 2.0, 6.0);
	glVertex3f(1.0, 2.0, 6.5);
	glVertex3f(5.0, 2.0, 1.0);
	glVertex3f(5.5, 2.0, 2.0);

		glEnd();*/
	{
	GLfloat  ORANGE[3] = {1,0.5f,0};
	GLfloat lb[3] = {19.0f, 0.5f, 10.0f};	
	GLfloat rb[3] = {19.0f, 0.5f, 12.0f};
	GLfloat lu[3] = {1.0f, 0.5f, 10.0f};	
	GLfloat ru[3] = {1.0f, 0.5f, 12.0f};
	Quad (ORANGE,  lb, rb, lu, ru, 1.0f, 1);
	}

	{
	GLfloat  ORANGE[3] = {1,0.5f,0};
	GLfloat lb[3] = {0.0f, 0.0f, 6.0f};
	GLfloat rb[3] = {0.0f, 0.0f, 16.0f};
	GLfloat lu[3] = {1.0f, 0.0f, 6.5f};	
	GLfloat ru[3] = {1.0f, 0.0f, 15.5f};
	Quad (ORANGE,  lb, rb, lu, ru, 2.0f, 1);
	}
	/*
	glBegin(GL_QUAD_STRIP);
	glColor3f(1, .5, 0);
	glVertex3f(0.0, 0.0, 6.0);
	glVertex3f(1.0, 0.0, 6.5);
	glVertex3f(0.0, 0.0, 16.0);
	glVertex3f(1.0, 0.0, 15.5);
	
	glVertex3f(0.0, 2.0, 16.0);
	glVertex3f(1.0, 2.0, 15.5);
	glVertex3f(0.0, 2.0, 6.0);
	glVertex3f(1.0, 2.0, 6.5);

	*/

	{
	GLfloat  YELLOW[3] = {1,1,0};
	GLfloat lb[3] = {0.0f, 0.0f, 16.0f};
	GLfloat rb[3] = {5.0f, 0.0f, 21.0f};
	GLfloat lu[3] = {1.0f, 0.0f, 15.5f};	
	GLfloat ru[3] = {5.5f, 0.0f, 20.0f};
	Quad (YELLOW,  lb, rb, lu, ru, 2.0f, 1);
	}
	/*
	glColor3f(1, 1, 0);
	glVertex3f(0.0, 0.0, 16.0);
	glVertex3f(1.0, 0.0, 15.5);
	glVertex3f(5.0, 0.0, 21.0);
	glVertex3f(5.5, 0.0, 20.0);
	
	glVertex3f(5.0, 2.0, 21.0);
	glVertex3f(5.5, 2.0, 20.0);
	glVertex3f(0.0, 2.0, 16.0);
	glVertex3f(1.0, 2.0, 15.5);
	*/
	{
	GLfloat  GREEN[3] = {0,1,0};
	GLfloat lb[3] = {5.0f, 0.0f, 21.0f};
	GLfloat rb[3] = {16.0f, 0.0f, 21.0f};	
	GLfloat lu[3] = {5.5f, 0.0f, 20.0f};
	GLfloat ru[3] = {15.5f, 0.0f, 20.0f};
	Quad (GREEN,  lb, rb, lu, ru, 2.0f, 1);
	}
	/*
	glColor3f(0, 1, 0);
	glVertex3f(5.0, 0.0, 21.0);
	glVertex3f(5.5, 0.0, 20.0);
	glVertex3f(16.0, 0.0, 21.0);
	glVertex3f(15.5, 0.0, 20.0);
	
	glVertex3f(16.0, 2.0, 21.0);
	glVertex3f(15.5, 2.0, 20.0);
	glVertex3f(5.0, 2.0, 21.0);
	glVertex3f(5.5, 2.0, 20.0);
	*/
	{
	GLfloat  BLUE[3] = {0,0,1};
	GLfloat lb[3] = {16.0f, 0.0f, 21.0f};
	GLfloat rb[3] = {20.0f, 0.0f, 16.0};
	GLfloat lu[3] = {15.5f, 0.0f, 20.0f};
	GLfloat ru[3] = {19.0f, 0.0f, 15.5f};
	Quad (BLUE,  lb, rb, lu, ru, 2.0f, 1);
	}
	/*
	glColor3f(0, 0, 1);
	glVertex3f(16.0, 0.0, 21.0);
	glVertex3f(15.5, 0.0, 20.0);
	glVertex3f(20.0, 0.0, 16.0);
	glVertex3f(19.0, 0.0, 15.5);
	
	glVertex3f(20.0, 2.0, 16.0);
	glVertex3f(19.0, 2.0, 15.5);
	glVertex3f(16.0, 2.0, 21.0);
	glVertex3f(15.5, 2.0, 20.0);
	*/
	{
	GLfloat  PURPLE[3] = {0.5f,0,1};
	GLfloat lb[3] = {20.0f, 0.0f, 16.0f};
	GLfloat rb[3] = {20.0f, 0.0f, 6.0};	
	GLfloat lu[3] = {19.0f, 0.0f, 15.5f};
	GLfloat ru[3] = {19.0f, 0.0f, 6.5f};
	Quad (PURPLE,  lb, rb, lu, ru, 2.0f, 1);
	}
	/*
	// Purple
	glColor3f(.5, 0, 1);
	glVertex3f(20.0, 0.0, 16.0);
	glVertex3f(19.0, 0.0, 15.5);
	glVertex3f(20.0, 0.0, 6.0);
	glVertex3f(19.0, 0.0, 6.5);
	
	glVertex3f(20.0, 2.0, 6.0);
	glVertex3f(19.0, 2.0, 6.5);
	glVertex3f(20.0, 2.0, 16.0);
	glVertex3f(19.0, 2.0, 15.5);
	*/
	{
	GLfloat  WHITE[3] = {1.0f,1,1};
	GLfloat lb[3] = {20.0f, 0.0f, 6.0f};
	GLfloat rb[3] = {15.0f, 0.0f, 1.0};	
	GLfloat lu[3] = {19.0f, 0.0f, 6.5f};
	GLfloat ru[3] = {14.5f, 0.0f, 2.0f};
	Quad (WHITE,  lb, rb, lu, ru, 2.0f, 1);
	}
	/*
	// White
	glColor3f(1, 1, 1);
	glVertex3f(20.0, 0.0, 6.0);
	glVertex3f(19.0, 0.0, 6.5);
	glVertex3f(15.0, 0.0, 1.0);
	glVertex3f(14.5, 0.0, 2.0);

	glVertex3f(20.0, 2.0, 6.0);
	glVertex3f(19.0, 2.0, 6.5);
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
}
// Initializer. Returns false if something went wrong, 
bool
FerrisWheel::Initialize(void)
{
	display_list_frame = glGenLists(1);
    glNewList(display_list_frame, GL_COMPILE);
	
	GLfloat  WHITE[3] = {0.75f, 0.75f, 0.75f};
	{
	GLfloat lb[3] = {-1.0f, 0.0f, 1.0f};
	GLfloat rb[3] = {-11.0f, 0.0f, 1.0};	
	GLfloat lu[3] = {-1.5f, 0.0f, 2.0f};
	GLfloat ru[3] = {-10.5f, 0.0f, 2.0f};
	Quad (WHITE,  lb, rb, lu, ru, 2.0f, 1);
	}
	
	{
//	GLfloat  WHITE[3] = {0.75,0,0.75};
	GLfloat lb[3] = {-5.0f, 0.0f, 2.0f};
	GLfloat rb[3] = {-5.0f, 0.0f, 16.0f};
	GLfloat lu[3] = {-7.0f, 0.0f, 2.0f};
	GLfloat ru[3] = {-7.0f, 0.0f, 16.0f};
	Quad (WHITE,  lb, rb, lu, ru, 2.0f, 1);
	}

	{
//	GLfloat  WHITE[3] = {0.75,0.75,0};
	GLfloat lb[3] = {-7.0f, 0.0f, 16.0f};
	GLfloat rb[3] = {2.0f, 0.0f, 16.0f};
	GLfloat lu[3] = {-6.5f, 0.0f, 18.0f};
	GLfloat ru[3] = {3.0f, 0.0f, 18.0f};
	Quad (WHITE,  lb, rb, lu, ru, 2.0f, 1);
	}

	{
//	GLfloat  WHITE[3] = {0,0.75,0};
	GLfloat lb[3] = {8.0f, 0.0f, 12.0f};
	GLfloat rb[3] = {2.0f, 0.0f, 16.0f};
	GLfloat lu[3] = {11, 0.0f, 12.0f};
	GLfloat ru[3] = {3.0f, 0.0f, 18.0f};
	Quad (WHITE,  lb, rb, lu, ru, 2.0f, 1);
	}
	
	
	glTranslatef(0.0,0.0, 2.0);
	{
//	GLfloat  WHITE[3] = {0,0,0.33f};
	GLfloat lb[3] = {8.0f, 0.0f, 11.0f};
	GLfloat rb[3] = {12.0f, 0.0f, 11.0f};
	GLfloat lu[3] = {8.5f, 0.0f, 13.0f};
	GLfloat ru[3] = {11.5f, 0.0f, 13.0f};
	Quad (WHITE,  lb, rb, lu, ru, 2.0f, 1);
	}
	{
//	GLfloat  WHITE[3] = {0,0,0.33f};
	GLfloat lb[3] = {8.0f, 0.0f, 11.0f};
	GLfloat rb[3] = {12.0f, 0.0f, 11.0f};
	GLfloat lu[3] = {8.5f, 0.0f, 9.0f};
	GLfloat ru[3] = {11.5f, 0.0f, 9.0f};
	Quad (WHITE,  lb, rb, lu, ru, 2.0f, 1);
	}
	glTranslatef(0.0,0.0, -2.0);
    glEndList();
	// Create the display list.
    display_list_wheel = glGenLists(1);
    glNewList(display_list_wheel, GL_COMPILE);

	createFrame();
	glTranslatef(0,10,0);
	createFrame();
    glEndList();

	display_list_seat = glGenLists(1);
    glNewList(display_list_seat, GL_COMPILE);
	
	glTranslatef(0,-10,-2);
	
	{
	GLfloat  g[3] = {0,.5f,0};
	GLfloat lb[3] = {9.0f, 2.0f, 0.0f};;
	GLfloat rb[3] = {9.0f, 10.0f, 0.0f};
	GLfloat lu[3] = {11.0f, 2.0f, 0.0f};
	GLfloat ru[3] = {11.0f, 10.0f, 0.0f};
	Quad (g,  lb, rb, lu, ru, 4.0f, 2);
	}
	{
	GLfloat  g[3] = {0,.5f,0};
	GLfloat lb[3] = {13.0f, 2.0f, 0.0f};
	GLfloat rb[3] = {13.0f, 10.0f, 0.0f};
	GLfloat lu[3] = {11.0f, 10.0f, 0.0f};
	GLfloat ru[3] = {11.0f, 2.0f, 0.0f};
	Quad (g,  lb, rb, lu, ru, 2.0f, 2);
	}
	
/*	glTranslatef(0,10,2);
	glTranslatef(9.75f,0,11.0f);
	glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(-9.75f,0,-11.0f);
	glTranslatef(0,-10,-2);
	
	{
	GLfloat  g[3] = {0,.5f,0};
	GLfloat lb[3] = {9.0f, 1.0f, 0.0f};
	GLfloat rb[3] = {11.0f, 10.0f, 0.0f};
	GLfloat lu[3] = {9.0f, 10.0f, 0.0f};
	GLfloat ru[3] = {11.0f, 1.0f, 0.0f};
	Quad (g,  lb, rb, lu, ru, 4.0f, 2);
	}
	{
	GLfloat  g[3] = {0,.5f,0};
	GLfloat lb[3] = {13.0f, 1.0f, 0.0f};
	GLfloat rb[3] = {13.0f, 10.0f, 0.0f};
	GLfloat lu[3] = {11.0f, 10.0f, 0.0f};
	GLfloat ru[3] = {11.0f, 1.0f, 0.0f};
	Quad (g,  lb, rb, lu, ru, 2.0f, 2);
	}
	
	glTranslatef(0,10,2);
	glTranslatef(9.75f,0,11.0f);
	glRotatef(-45.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(-9.75f,0,-11.0f);
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
	angle +=0.5;

    glPushMatrix();
	glTranslatef(-30,30,0);
	glDisable(GL_CULL_FACE);
	glTranslatef(0,-2.1,1);
    glCallList(display_list_frame);
	glTranslatef(0, 2.1,0);
	glTranslatef(0, 12.1,0);
    glCallList(display_list_frame);
	glTranslatef(0, -12.1,-1);
	glEnable(GL_CULL_FACE);

	glTranslatef(0,0,3);
	/*
	glTranslatef(10, 14,11);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	gluCylinder(quadratic, 2.0, 2.0, 14.0f, 32,32);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(-10,-14,-11);
*/
	glTranslatef(9.75f,0,11.0f);
	glRotatef((float)angle, 0.0f, 1.0f, 0.0f);
	glTranslatef(-9.75f,0,-11.0f);
	

    glDisable(GL_CULL_FACE);
    glCallList(display_list_wheel);
	glTranslatef(10.0f,5.0f,1.0f);
	glRotatef(-angle, 0, 1.0f, 0);
	glTranslatef(-10.0f,-5.0f,-1.0f);
	glCallList(display_list_seat);

	glTranslatef(10.0f,5.0f,1.0f);
	glRotatef(angle, 0, 1.0f, 0);
	glTranslatef(-10.0f,-5.0f,-1.0f);
	
	glTranslatef(9.75f,0,11.0f);
	glRotatef(45, 0.0f, 1.0f, 0.0f);
	glTranslatef(-9.75f,0,-11.0f);
	
	glTranslatef(10.0f,5.0f,1.0f);
	glRotatef(-angle-45, 0, 1.0f, 0);
	glTranslatef(-10.0f,-5.0f,-1.0f);
	glTranslatef(0.0f,10.0f,1.0f);
	glCallList(display_list_seat);
	/*
	glTranslatef(0.0f,-10.0f,1.0f);
	glTranslatef(10.0f,5.0f,1.0f);
	glRotatef(angle+45, 0, 1.0f, 0);
	glTranslatef(-10.0f,-5.0f,-1.0f);
	
	glTranslatef(9.75f,0,11.0f);
	glRotatef(90, 0.0f, 1.0f, 0.0f);
	glTranslatef(-9.75f,0,-11.0f);
	
	glTranslatef(10.0f,5.0f,1.0f);
	glRotatef(-angle-90, 0, 1.0f, 0);
	glTranslatef(-10.0f,-5.0f,-1.0f);
	glTranslatef(0.0f,10.0f,1.0f);
	glCallList(display_list_seat);*/
	glEnable(GL_CULL_FACE);
    glPopMatrix();
}


