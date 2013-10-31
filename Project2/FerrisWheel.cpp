/*
 * Ground.cpp: A class for drawing the ground.
 *
 * (c) 2001-2002: Stephen Chenney, University of Wisconsin at Madison.
 */


#include "Objects.h"
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
	GLfloat  WHITE[3] = {0.75f, 0.75f, 0.75f};
	{
	GLfloat flb[3] = {-1.0f, 2.0f, 0.0f};
	GLfloat fru[3] = {-1.5f, 0.0f, 1.0f};
	GLfloat blb[3] = {-11.0f, 2.0f, 0.0f};
	GLfloat bru[3] = {-10.5f, 0.0f, 1.0f};

	glBegin(GL_QUADS);
		MyQuad a(WHITE, flb, fru,blb, bru);
		a.Construct();
	glEnd();
	}
	
	{
	GLfloat flb[3] = {-5.0f, 0.0f, 1.0f};
	GLfloat bru[3] = {-7.0f, 2.0f, 16.0f};

	glBegin(GL_QUADS);
		MyQuad a(WHITE, flb, bru);
		a.Construct();
	glEnd();
	}

	{
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
	
	GLfloat flb[3] = {8.0f, 0.0f, 11.0f};
	GLfloat fru[3] = {8.5f, 2.0f, 13.0f};
	GLfloat blb[3] = {12.0f, 0.0f, 11.0f};
	GLfloat bru[3] = {11.5f, 2.0f, 13.0f};

	//Quad (WHITE,  lb, rb, lu, ru, 2.0f, 1);
		MyQuad a(WHITE, flb, fru, blb, bru);
		glBegin(GL_QUADS);
		a.Construct();
		glEnd();
	}
	{
//	GLfloat  WHITE[3] = {0,0,0.33f};
	GLfloat lb[3] = {8.0f, 0.0f, 11.0f};
	GLfloat rb[3] = {12.0f, 0.0f, 11.0f};
	GLfloat lu[3] = {8.5f, 0.0f, 9.0f};
	GLfloat ru[3] = {11.5f, 0.0f, 9.0f};
//	Quad (WHITE,  lb, rb, lu, ru, 2.0f, 1);
		
	GLfloat flb[3] = {8.0f, 0.0f, 11.0f};
	GLfloat fru[3] = {8.5f, 2.0f, 9.0f};
	GLfloat blb[3] = {12.0f, 0.0f, 11.0f};
	GLfloat bru[3] = {11.5f, 2.0f, 9.0f};

	//Quad (WHITE,  lb, rb, lu, ru, 2.0f, 1);
		MyQuad a(WHITE, flb, fru, blb, bru);
		glBegin(GL_QUADS);
		a.Construct();
		glEnd();
	}
	glTranslatef(0.0,0.0, -2.0);
}

void createWheel()
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
	{
	GLfloat  RED[3] = {1,0,0};
	GLfloat lb[3] = {5.0f, 0.0f, 1.0f};
	GLfloat rb[3] = {0.0f, 0.0f, 6.0f};
	GLfloat lu[3] = {5.5f, 0.0f, 2.0f};
	GLfloat ru[3] = {1.0f, 0.0f, 6.5f};
	Quad (RED,  lb, rb, lu, ru, 2.0f, 1);
	}
	if (1){
	GLfloat  ORANGE[3] = {1,0.5f,0};
	GLfloat lb[3] = {19.0f, 0.5f, 10.0f};
	GLfloat ru[3] = {1.0f, 1.5f, 12.0f};
	glBegin(GL_QUADS);

	MyQuad a(ORANGE, lb, ru);
	a.Construct();
	glEnd();
	//Quad (ORANGE,  lb, rb, lu, ru, 1.0f, 1);
	}

	{
	GLfloat  ORANGE[3] = {1,0.5f,0};
	GLfloat lb[3] = {0.0f, 0.0f, 6.0f};
	GLfloat rb[3] = {0.0f, 0.0f, 16.0f};
	GLfloat lu[3] = {1.0f, 0.0f, 6.5f};	
	GLfloat ru[3] = {1.0f, 0.0f, 15.5f};
	Quad (ORANGE,  lb, rb, lu, ru, 2.0f, 1);
	}

	{
	GLfloat  YELLOW[3] = {1,1,0};
	GLfloat lb[3] = {0.0f, 0.0f, 16.0f};
	GLfloat rb[3] = {5.0f, 0.0f, 21.0f};
	GLfloat lu[3] = {1.0f, 0.0f, 15.5f};	
	GLfloat ru[3] = {5.5f, 0.0f, 20.0f};
	Quad (YELLOW,  lb, rb, lu, ru, 2.0f, 1);
	}
	{
	GLfloat  GREEN[3] = {0,1,0};
	GLfloat lb[3] = {5.0f, 0.0f, 21.0f};
	GLfloat rb[3] = {16.0f, 0.0f, 21.0f};	
	GLfloat lu[3] = {5.5f, 0.0f, 20.0f};
	GLfloat ru[3] = {15.5f, 0.0f, 20.0f};
	Quad (GREEN,  lb, rb, lu, ru, 2.0f, 1);
	}
	{
	GLfloat  BLUE[3] = {0,0,1};
	GLfloat lb[3] = {16.0f, 0.0f, 21.0f};
	GLfloat rb[3] = {20.0f, 0.0f, 16.0};
	GLfloat lu[3] = {15.5f, 0.0f, 20.0f};
	GLfloat ru[3] = {19.0f, 0.0f, 15.5f};
	Quad (BLUE,  lb, rb, lu, ru, 2.0f, 1);
	}
	{
	GLfloat  PURPLE[3] = {0.5f,0,1};
	GLfloat lb[3] = {20.0f, 0.0f, 16.0f};
	GLfloat rb[3] = {20.0f, 0.0f, 6.0};	
	GLfloat lu[3] = {19.0f, 0.0f, 15.5f};
	GLfloat ru[3] = {19.0f, 0.0f, 6.5f};
	Quad (PURPLE,  lb, rb, lu, ru, 2.0f, 1);
	}
	{
	GLfloat  WHITE[3] = {1.0f,1,1};
	GLfloat lb[3] = {20.0f, 0.0f, 6.0f};
	GLfloat rb[3] = {15.0f, 0.0f, 1.0};	
	GLfloat lu[3] = {19.0f, 0.0f, 6.5f};
	GLfloat ru[3] = {14.5f, 0.0f, 2.0f};
	Quad (WHITE,  lb, rb, lu, ru, 2.0f, 1);
	}
}
// Initializer. Returns false if something went wrong, 
bool
FerrisWheel::Initialize(void)
{
	display_list_frame = glGenLists(1);
    glNewList(display_list_frame, GL_COMPILE);
	createFrame();
    glEndList();
	// Create the display list.
    display_list_wheel = glGenLists(1);
    glNewList(display_list_wheel, GL_COMPILE);

	createWheel();
	glTranslatef(0,10,0);
	createWheel();
    glEndList();
	
	display_list_seat = glGenLists(1);
    glNewList(display_list_seat, GL_COMPILE);
	
	glTranslatef(0,-10,-2);
	const float y0 = 2.1f, y1 = 9.9f;
	{
	GLfloat  g[3] = {0,.5f,0};
	GLfloat p1[3] = {9.0f, y0, 0.0f};
	GLfloat p2[3] = {9.0f, y0, 4.0f};
	GLfloat p3[3] = {11.0f, y0, 4.0f};
	GLfloat p4[3] = {11.0f, y0, 0.0f};

	GLfloat p5[3] = {9.0f, y1, 0.0f};
	GLfloat p6[3] = {9.0f, y1, 4.0f};
	GLfloat p7[3] = {11.0f, y1, 4.0f};
	GLfloat p8[3] = {11.0f, y1, 0.0f};
	
	glBegin(GL_QUADS);
	glColor3fv(g);
	MyQuad a(g, p1, p7);
	a.Construct();
/*		
		// Top of quad
		glVertex3fv(p7);
		glVertex3fv(p6);
		glVertex3fv(p2);
		glVertex3fv(p3);
		//bottom of the quad
		glVertex3fv(p8);
		glVertex3fv(p5);
		glVertex3fv(p1);
		glVertex3fv(p4);
		// front
		glVertex3fv(p3);
		glVertex3fv(p2);
		glVertex3fv(p1);
		glVertex3fv(p4);
		// back
		glVertex3fv(p7);
		glVertex3fv(p6);
		glVertex3fv(p5);
		glVertex3fv(p8);
		// left
		glVertex3fv(p2);
		glVertex3fv(p6);
		glVertex3fv(p5);
		glVertex3fv(p1);
		// right
		glVertex3fv(p2);
		glVertex3fv(p3);
		glVertex3fv(p4);
		glVertex3fv(p8);
		*/
	glEnd();
	}
	{
	GLfloat  g[3] = {0,.5f,0};
/*	GLfloat lb[3] = {13.0f, 2.0f, 0.0f};
	GLfloat rb[3] = {13.0f, 10.0f, 0.0f};
	GLfloat lu[3] = {11.0f, 10.0f, 0.0f};
	GLfloat ru[3] = {11.0f, 2.0f, 0.0f};*/
//	Quad (g,  lb, rb, lu, ru, 2.0f, 2);	GLfloat p1[3] = {9.0f, 2.1f, 0.0f};
	
	GLfloat p1[3] = {11.0f, y0, 0.0f};
	GLfloat p4[3] =	{11.0f, y0, 2.0f};
	GLfloat p2[3] =	{13.0f, y0, 2.0f};
	GLfloat p3[3] = {13.0f, y0, 0.0f};

	GLfloat p5[3] = {11.0f, y1, 0.0f};
	GLfloat p8[3] = {11.0f, y1, 2.0f};
	GLfloat p6[3] = {13.0f, y1, 2.0f};
	GLfloat p7[3] = {13.0f, y1, 0.0f};

	
	glBegin(GL_QUADS);
	glColor3fv(g);
	MyQuad b(g, p1, p6);
	b.Construct();
	/*	// Top of quad
		glVertex3fv(p7);
		glVertex3fv(p6);
		glVertex3fv(p2);
		glVertex3fv(p3);
		//bottom of the quad
		glVertex3fv(p8);
		glVertex3fv(p5);
		glVertex3fv(p1);
		glVertex3fv(p4);
		// front
		glVertex3fv(p3);
		glVertex3fv(p2);
		glVertex3fv(p1);
		glVertex3fv(p4);
		// back
		glVertex3fv(p7);
		glVertex3fv(p6);
		glVertex3fv(p5);
		glVertex3fv(p8);
		// left
		glVertex3fv(p2);
		glVertex3fv(p6);
		glVertex3fv(p5);
		glVertex3fv(p1);
		// right
		glVertex3fv(p2);
		glVertex3fv(p3);
		glVertex3fv(p4);
		glVertex3fv(p8);
		*/
	glEnd();
	}

	glEndList();

    // We only do all this stuff once, when the GL context is first set up.
    initialized = true;

    return true;
}


// Draw just calls the display list we set up earlier.
void
FerrisWheel::Draw(void)
{
	bool rotate = false || 01;
	angle +=0.5;
	float xInitial = -30.0f,
		  yInitial = 30.0f;
	float xWheelCenter = 9.75f,
		  yWheelCenter = 0.0f,
		  zWheelCenter = 11.0f;
	
    glPushMatrix();
	glTranslatef(xInitial, yInitial,0);
	glDisable(GL_CULL_FACE);
	glTranslatef(0.0f, -2.1f, 1.0f);
    glCallList(display_list_frame);
	glTranslatef(0.0f, 2.1f, 0.0f);
	glTranslatef(0.0f, 12.1f, 0.0f);
    glCallList(display_list_frame);
	glTranslatef(0.0f, -12.1f, -1.0f);
	glEnable(GL_CULL_FACE);

	glTranslatef(0,0,3);

	glTranslatef(xWheelCenter, yWheelCenter, zWheelCenter);
	if (rotate)glRotatef((float)angle, 0.0f, 1.0f, 0.0f);
	glTranslatef(-xWheelCenter, -yWheelCenter, -zWheelCenter);
	

    glDisable(GL_CULL_FACE);
    glCallList(display_list_wheel);
	glTranslatef(10.0f,5.0f,1.0f);
	if (rotate)glRotatef(-angle, 0, 1.0f, 0);
	glTranslatef(-10.0f,-5.0f,-1.0f);
	glCallList(display_list_seat);   //Black

	glTranslatef(10.0f,5.0f,1.0f);
	if (rotate)glRotatef(angle, 0, 1.0f, 0);
	glTranslatef(-10.0f,-5.0f,-1.0f);
	
	glTranslatef(xWheelCenter, yWheelCenter, zWheelCenter);
	glRotatef(45, 0.0f, 1.0f, 0.0f);
	glTranslatef(-xWheelCenter, -yWheelCenter, -zWheelCenter);
	
	glTranslatef(10.0f,5.0f,1.0f);
	if (rotate)glRotatef(-angle-45, 0, 1.0f, 0);
	glTranslatef(-10.0f,-5.0f,-1.0f);
	glTranslatef(0.0f,10.0f,2.5f);
	glCallList(display_list_seat);//red
/*	
	glTranslatef(0.0f,-10.0f,-2.5f);
	glTranslatef(10.0f,5.0f,1.0f);
	if (rotate)glRotatef(angle+45, 0, 1.0f, 0);
	glTranslatef(-10.0f,-5.0f,-1.0f);

	glTranslatef(xWheelCenter, yWheelCenter, zWheelCenter);
	glRotatef(-45, 0.0f, 1.0f, 0.0f);
	glTranslatef(-xWheelCenter, -yWheelCenter, -zWheelCenter);
	glTranslatef(10.0f,5.0f,1.0f);
	if (rotate)glRotatef(angle, 0, 1.0f, 0);
	glTranslatef(-10.0f,-5.0f,-1.0f);
		
	
	glCallList(display_list_seat);//
	*/
	glPopMatrix();
    glPushMatrix();
	glTranslatef(xInitial, yInitial,0);
	glTranslatef(0,0,3);
	glTranslatef(0,10,0);
	
	glTranslatef(xWheelCenter, yWheelCenter, zWheelCenter);
	if (rotate)glRotatef((float)angle, 0.0f, 1.0f, 0.0f);
	glTranslatef(-xWheelCenter, -yWheelCenter, -zWheelCenter);
	glTranslatef(0,0,20);

	glTranslatef(10.0f,5.0f,1.0f);
	if (rotate)glRotatef(-angle, 0, 1.0f, 0);
	glTranslatef(-10.0f,-5.0f,-1.0f);

    glCallList(display_list_seat);//green

    glPopMatrix();
    glPushMatrix();
	
	glTranslatef(xInitial, yInitial,0);
	glTranslatef(0,0,3);
	glTranslatef(0,10,0);
	
	glTranslatef(xWheelCenter, yWheelCenter, zWheelCenter);
	if (rotate)glRotatef((float)angle, 0.0f, 1.0f, 0.0f);
	glTranslatef(-xWheelCenter, -yWheelCenter, -zWheelCenter);

	glTranslatef(10,0,10);

	glTranslatef(10.0f,5.0f,1.0f);
	if (rotate)glRotatef(-angle, 0, 1.0f, 0);
	glTranslatef(-10.0f,-5.0f,-1.0f);

    glCallList(display_list_seat);//purple

    glPopMatrix();
    glPushMatrix();
	glTranslatef(xInitial, yInitial,0);
	glTranslatef(0,0,3);
	glTranslatef(0,10,0);
	
	glTranslatef(xWheelCenter, yWheelCenter, zWheelCenter);
	if (rotate)glRotatef((float)angle, 0.0f, 1.0f, 0.0f);
	glTranslatef(-xWheelCenter, -yWheelCenter, -zWheelCenter);
	glTranslatef(-10,0,10);

	glTranslatef(10.0f,5.0f,1.0f);
	if (rotate)glRotatef(-angle, 0, 1.0f, 0);
	glTranslatef(-10.0f,-5.0f,-1.0f);

    glCallList(display_list_seat); //orange
	
	glPopMatrix();
    glPushMatrix();

	glTranslatef(xInitial, yInitial,0);
	glTranslatef(0,0,3);
	glTranslatef(0,10,0);
	
	glTranslatef(xWheelCenter, yWheelCenter, zWheelCenter);
	if (rotate)glRotatef((float)angle, 0.0f, 1.0f, 0.0f);
	glTranslatef(-xWheelCenter, -yWheelCenter, -zWheelCenter);

	glTranslatef(0.0f,0,14.5f);
	glTranslatef(xWheelCenter, yWheelCenter, zWheelCenter);
	glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(-xWheelCenter, -yWheelCenter, -zWheelCenter);

	glTranslatef(10.0f,5.0f,1.0f);
	if (rotate)glRotatef(-angle-45, 0, 1.0f, 0);
	glTranslatef(-10.0f,-5.0f,-1.0f);

    glCallList(display_list_seat); //yellow
	
	glPopMatrix();
    glPushMatrix();

	glTranslatef(xInitial, yInitial,0);
	glTranslatef(0,0,3);
	glTranslatef(0,10,0);
	
	glTranslatef(xWheelCenter, yWheelCenter, zWheelCenter);
	if (rotate)glRotatef((float)angle, 0.0f, 1.0f, 0.0f);
	glTranslatef(-xWheelCenter, -yWheelCenter, -zWheelCenter);

	glTranslatef(1.0f,0,14.5f);
	glTranslatef(xWheelCenter, yWheelCenter, zWheelCenter);
	glRotatef(-45.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(-xWheelCenter, -yWheelCenter, -zWheelCenter);

	glTranslatef(10.0f,5.0f,1.0f);
	if (rotate)glRotatef(-angle+45, 0, 1.0f, 0);
	glTranslatef(-10.0f,-5.0f,-1.0f);

    glCallList(display_list_seat); // blue
		
	glPopMatrix();
    glPushMatrix();

	glTranslatef(xInitial, yInitial,0);
	glTranslatef(0,0,3);
	glTranslatef(0,10,0);
	
	glTranslatef(xWheelCenter, yWheelCenter, zWheelCenter);
	if (rotate)glRotatef((float)angle, 0.0f, 1.0f, 0.0f);
	glTranslatef(-xWheelCenter, -yWheelCenter, -zWheelCenter);

	glTranslatef(0.0f,0,-1.0f);
	glTranslatef(xWheelCenter, yWheelCenter, zWheelCenter);
	glRotatef(-45.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(-xWheelCenter, -yWheelCenter, -zWheelCenter);

	glTranslatef(10.0f,5.0f,1.0f);
	if (rotate)glRotatef(-angle+45, 0, 1.0f, 0);
	glTranslatef(-10.0f,-5.0f,-1.0f);

    glCallList(display_list_seat); // 
	glEnable(GL_CULL_FACE);
    glPopMatrix();
}


