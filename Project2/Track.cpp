/*
 * Track.cpp: A class that draws the train and its track.
 *
 * (c) 2001-2002: Stephen Chenney, University of Wisconsin at Madison.
 */


#include "Track.h"
#include <stdio.h>
#include <FL/math.h>
#include <GL/glu.h>
#include "Objects.h"
#include <iostream>
#include <fstream>
using namespace std;

// The control points for the track spline.
const int   Track::TRACK_NUM_CONTROLS = 4;
const float Track::TRACK_CONTROLS[TRACK_NUM_CONTROLS][3] =
		{ { -20.0, -20.0, -18.0 }, { 20.0, -20.0, 40.0 },
		  { 20.0, 20.0, -18.0 }, { -20.0, 20.0, 40.0 } };

// The carriage energy and mass
const float Track::TRAIN_ENERGY = 250.0f;


// Normalize a 3d vector.
static void
Normalize_3(float v[3])
{
    double  l = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);

    if ( l == 0.0 )
	return;

    v[0] /= (float)l;
    v[1] /= (float)l;
    v[2] /= (float)l;
}


// Destructor
Track::~Track(void)
{
    if ( initialized )
    {
	glDeleteLists(track_list, 1);
	glDeleteLists(train_list, 1);
    }
}


// Initializer. Would return false if anything could go wrong.
bool
Track::Initialize(void)
{
    CubicBspline    refined(3, true);
    //int		    n_refined;
    float	    p[3];
    int		    i;

    // Create the track spline.
    track = new CubicBspline(3, true);
    for ( i = 0 ; i < TRACK_NUM_CONTROLS ; i++ )
	track->Append_Control(TRACK_CONTROLS[i]);

    // Refine it down to a fixed tolerance. This means that any point on
    // the track that is drawn will be less than 0.1 units from its true
    // location. In fact, it's even closer than that.
    track->Refine_Tolerance(refined, 0.1f);
    n_refined = refined.N();

    // Create the display list for the track - just a set of line segments
    // We just use curve evaluated at integer paramer values, because the
    // subdivision has made sure that these are good enough.
    track_list = glGenLists(1);
    glNewList(track_list, GL_COMPILE);
	glColor3f(1.0f, 1.0, 1.0f);
	glBegin(GL_LINE_STRIP);
	    for ( i = 0 ; i <= n_refined ; i++ )
	    {
		refined.Evaluate_Point((float)i, p);
		glVertex3fv(p);
	    }
	glEnd();
	
    //////////////
	//std::ofstream file("./REPORT.txt");
	    for (int i = 0 ; i <= n_refined ; i++ )
	    {
		//cout << i << endl;
		glPushMatrix();
		
		float p[3];

		track->Evaluate_Point((float)i/n_refined*4, p);
		glTranslatef(p[0], p[1], p[2]);
		float tangent[3];
		track->Evaluate_Derivative((float)i/n_refined*4, tangent);
		Normalize_3(tangent);
		float angle1 = (float)(atan2(tangent[1], tangent[0]) * 180.0 / M_PI);
		float angle2 = (float)(asin(-tangent[2]) * 180.0 / M_PI);
		

		GLfloat color[3] = {(float)i/n_refined, 0.0f, 0.5f};
		
		GLfloat flb2[3] = {-.2f, -.2f,  0.0f},//-p[2]},
			bru2[3] = {.2f, .2f, 0.0f};//-.125};
//		-.125

		MyQuad posta(color, flb2, bru2);
		posta.flu[MyQuad::Z] = -.125f;
		posta.fru[MyQuad::Z] = 0.0f;
		
		posta.blu[MyQuad::Z] = -.125f;
		posta.bru[MyQuad::Z] = 0.0f;

		posta.Rotatef(angle1, MyQuad::Z);
		posta.Rotatef(-angle2, MyQuad::Y);
		posta.flb[MyQuad::Z] = -p[2];
		posta.frb[MyQuad::Z] = -p[2];
		
		posta.blb[MyQuad::Z] = -p[2];
		posta.brb[MyQuad::Z] = -p[2];
		if (0 && (i < 32))
		{
		posta.print();

/*		if ((posta.flu[MyQuad::X] > posta.blu[MyQuad::X]) ||
		   (posta.flu[MyQuad::Y] > posta.blu[MyQuad::Y]))
		{
				posta.flu[MyQuad::Z] = -.125;
				posta.fru[MyQuad::Z] = -.125;
				posta.blu[MyQuad::Z] = -.625;
				posta.bru[MyQuad::Z] = -.625;
		
		}
		else
		{
			posta.flu[MyQuad::Z] = -.525;
			posta.fru[MyQuad::Z] = -.525;
			posta.blu[MyQuad::Z] = -.125;
			posta.bru[MyQuad::Z] = -.125;
		}
		posta.flb[MyQuad::Z] = -p[2];
		posta.frb[MyQuad::Z] = -p[2];
		
		posta.blb[MyQuad::Z] = -p[2];
		posta.brb[MyQuad::Z] = -p[2];
		*/
		//MyQuad::Rotatef(-angle1, MyQuad::Z,posta.flu);
		//MyQuad::Rotatef(-angle2, MyQuad::Y,posta.flu);
		//posta.fru[MyQuad::Z] = 0;
		//MyQuad::Rotatef(-angle1, MyQuad::Z,posta.fru);
		//MyQuad::Rotatef(-angle2, MyQuad::Y,posta.fru);
		//posta.blu[MyQuad::Z] = 0;
		//MyQuad::Rotatef(-angle1, MyQuad::Z,posta.blu);
		//MyQuad::Rotatef(-angle2, MyQuad::Y,posta.blu);
		//posta.bru[MyQuad::Z] = 0;
		//MyQuad::Rotatef(-angle1, MyQuad::Z,posta.bru);
		//MyQuad::Rotatef(-angle2, MyQuad::Y,posta.bru);
		//MyQuad postb(color, flb3, bru3);
		glBegin(GL_QUADS);
		posta.color[0] = 1;
		posta.color[1] = 1;
		posta.color[2] = 1;
		posta.Construct();		
		glEnd();
		}
	/*	glBegin(GL_QUADS);
		postb.color[0] = 0;
		postb.color[1] = 1;
		postb.color[2] = 0;
		postb.Construct();		
		glEnd();
		*/

		
		

	/*	GLfloat fluP[3] = {0.2,.2,-.125},
				fruP[3] = {0.4,.2,-.125},
				bluP[3] = {.2, .4, -.1250},
				bruP[3] = {.2, .4, -.125};
		MyQuad::Rotatef(angle1, 2, fluP);
		MyQuad::Rotatef(angle2, 1, fluP);
		MyQuad::Rotatef(angle1, 2, fruP);
		MyQuad::Rotatef(angle2, 1, fruP);
		MyQuad::Rotatef(angle1, 2, bluP);
		MyQuad::Rotatef(angle2, 1, bluP);
		MyQuad::Rotatef(angle1, 2, bruP);
		MyQuad::Rotatef(angle2, 1, bruP);*/
		//flb{.2, .2,  -p[2]},
		//	bru2[3] = {.4, .4, -.125};
		/*GLfloat flbP[3] = {0.2,.2,-.125},
				frbP[3] = {.4,.2,-.125},
				blbP[3] = {.2, .4, -.125},
				brbP[3] = {.4, .4, -.125};
		MyQuad c(color, flbP, fluP, fruP, frbP, blbP, bluP, bruP, brbP);
		glBegin(GL_QUADS);
		c.color[0] = .5;
		c.color[1] = 0;
		c.color[2] = 0.5;
		c.Construct();		
		glEnd();*/
//		cout << p[0] << " " << p[1] <<  " " << p[2] << endl;
	//	cout << tangent[0] << " " << tangent[1] <<  " " << tangent[2] << endl;
		glRotatef((float)angle1, 0.0f, 0.0f, 1.0f);
		glRotatef((float)angle2, 0.0f, 1.0f, 0.0f);

		//track->Evaluate_Point((float)((i+1)%(n_refined+1)), q);
		
		GLfloat flb[3] = {0.125f,-1.0f,-.125f},
			bru[3] = {.625f, 1.0f, 0.0f};
		glBegin(GL_QUADS);
		MyQuad board(color, flb, bru);
		board.Construct();
		glEnd();
		GLfloat flba[3] = {0.2f,-.2f,-.125f},
			brua[3] = {.4f, .2f, -.125f};
		MyQuad x(color, flba, brua);
		x.flb[2] = -p[2];
		MyQuad::Rotatef(angle1, 2, x.flb);
		MyQuad::Rotatef(angle2, 1, x.flb);
		x.frb[2] = -p[2];
		
		MyQuad::Rotatef(angle1, 2, x.frb);
		MyQuad::Rotatef(angle2, 1, x.frb);
		x.blb[2] = -p[2];
		
		MyQuad::Rotatef(angle1, 2, x.blb);
		MyQuad::Rotatef(angle2, 1, x.blb);
		x.brb[2] = -p[2];
		MyQuad::Rotatef(angle1, 2, x.brb);
		MyQuad::Rotatef(angle2, 1, x.brb);
		
		glBegin(GL_QUADS);
		x.Construct();
		glEnd();

		glPopMatrix();
	    }
		glEndList();

    // Set up the train. At this point a cube is drawn. NOTE: The
    // x-axis will be aligned to point along the track. The origin of the
    // train is assumed to be at the bottom of the train.
	wheel_list = glGenLists(1);
	glNewList(wheel_list, GL_COMPILE);
    
	GLUquadric *a = gluNewQuadric();
	
	
	glTranslatef(0, -1, .125);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	
	glColor3f(0.0, 1.0, 0.0);
	gluCylinder(a, 0.25f, 0.25f, 0.5f, 32,32);
	
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(0, 1, -.125);
	glEndList();
    
	train_list = glGenLists(1);
	glNewList(train_list, GL_COMPILE);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 1.0f);
	glVertex3f(-0.5f, -0.5f, 1.0f);
	glVertex3f(0.5f, -0.5f, 1.0f);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.0f);
	glVertex3f(0.5f, 0.5f, 0.0f);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.5f, 0.5f, 0.0f);
	glVertex3f(0.5f, 0.5f, 1.0f);
	glVertex3f(0.5f, -0.5f, 1.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 1.0f);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.5f, 0.5f, 1.0f);
	glVertex3f(0.5f, 0.5f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 1.0f);

	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(0.5f, -0.5f, 1.0f);
	glVertex3f(-0.5f, -0.5f, 1.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);
    glEnd();
    glEndList();

    initialized = true;

    return true;
}


// Draw
void
Track::Draw(void)
{
    float   posn[3];
    float   tangent[3];
    double  angle;

    if ( ! initialized )
	return;

    glPushMatrix();
	
   // glDisable(GL_CULL_FACE);
    // Draw the track
    glCallList(track_list);
	//
    glPushMatrix();

    // Figure out where the train is
    track->Evaluate_Point(posn_on_track, posn);

    // Translate the train to the point
    glTranslatef(posn[0], posn[1], posn[2]);

    // ...and what it's orientation is
    track->Evaluate_Derivative(posn_on_track, tangent);
    Normalize_3(tangent);

    // Rotate it to poitn along the track, but stay horizontal
    angle = atan2(tangent[1], tangent[0]) * 180.0 / M_PI;
    glRotatef((float)angle, 0.0f, 0.0f, 1.0f);

    // Another rotation to get the tilt right.
    angle = asin(-tangent[2]) * 180.0 / M_PI;
    glRotatef((float)angle, 0.0f, 1.0f, 0.0f);

    // Draw the train
	glTranslatef(-1,0,0);
    glCallList(train_list);
	
	glTranslatef(1,0,0);
	glDisable(GL_CULL_FACE);
	glPushMatrix();
	glPopMatrix();
	static float lastpos = 0;

	lastpos += speed;
	glTranslatef(0,0, .125);
	glRotatef(lastpos, 0, 1, 0);
	glTranslatef(0,0, -.125);
	glCallList(wheel_list);
	glTranslatef(0,0, .125);
	glRotatef(-lastpos, 0, 1, 0);
	glTranslatef(0,0, -.125);
	glEnable(GL_CULL_FACE);
    glCallList(train_list);
	glTranslatef(1,0,0);
    glCallList(train_list);

    glPopMatrix();
    glPopMatrix();
}


void
Track::Update(float dt)
{
    float   point[3];
    float   deriv[3];
    double  length;
    double  parametric_speed;

    if ( ! initialized )
	return;

    // First we move the train along the track with its current speed.

    // Get the derivative at the current location on the track.
    track->Evaluate_Derivative(posn_on_track, deriv);

    // Get its length.
    length = sqrt(deriv[0]*deriv[0] + deriv[1]*deriv[1] + deriv[2]*deriv[2]);
    if ( length == 0.0 )
	return;

    // The parametric speed is the world train speed divided by the length
    // of the tangent vector.
    parametric_speed = speed / length;

    // Now just evaluate dist = speed * time, for the parameter.
    posn_on_track += (float)(parametric_speed * dt);

    // If we've just gone around the track, reset back to the start.
    if ( posn_on_track > track->N() )
	posn_on_track -= track->N();

    // As the second step, we use conservation of energy to set the speed
    // for the next time.
    // The total energy = z * gravity + 1/2 speed * speed, assuming unit mass
    track->Evaluate_Point(posn_on_track, point);
    if ( TRAIN_ENERGY - 9.81 * point[2] < 0.0 )
	speed = 0.0;
    else
	speed = (float)sqrt(2.0 * ( TRAIN_ENERGY - 9.81 * point[2] ));
}


void Track::View()
{
    float   posn[3];
    float   tangent[3];
    double  angle1, angle2;
	
    // Figure out where the train is
    track->Evaluate_Point((posn_on_track + n_refined - 2), posn);

    // Translate the train to the point
 //   glTranslatef(posn[0], posn[1], posn[2]);

    // ...and what it's orientation is
    track->Evaluate_Derivative((posn_on_track + n_refined - 2), tangent);
    Normalize_3(tangent);

    // Rotate it to poitn along the track, but stay horizontal
    angle1 = atan2(tangent[1], tangent[0]) * 180.0 / M_PI;// +30;
   // glRotatef((float)angle, 0.0f, 0.0f, 1.0f);

    // Another rotation to get the tilt right.
    angle2 = asin(-tangent[2]) * 180.0 / M_PI ;
  //  glRotatef((float)angle, 0.0f, 1.0f, 0.0f);
	posn[2] += 3;//.5;
	GLfloat eye[3], dist=5;
	float x_at = -posn[0],
		  y_at = -posn[1];
	eye[0] = (float)(x_at + dist * cos(angle1 * M_PI / 180.0) * cos(angle2 * M_PI / 180.0));
    eye[1] = (float)(y_at + dist * sin(angle1 * M_PI / 180.0) * cos(angle2 * M_PI / 180.0));
    eye[2] = (float)(posn[2] + dist * sin(angle2 * M_PI / 180.0));
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye[0], eye[1], eye[2], x_at, y_at, posn[2], 0.0, 0.0, 1.0);

}