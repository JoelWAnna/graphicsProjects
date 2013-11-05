/*
 * FerrisWheel.h: Header file for a class that draws the FerrisWheel.
 *
 */


#ifndef _OBJECTS__
#define _OBJECTS__

#include "Ground.h"
#include "Tree.h"
#include "FerrisWheel.h"
#include "Track.h"
#include "Wall.h"

struct MyQuad
{
	enum
	{
		X = 0,
		Y = 1,
		Z = 2,
		RGB = 3
	};

	MyQuad(GLfloat c[3], GLfloat frontLeftBottom[3], GLfloat backRightTop[3])
	;/*{
		memcpy(color, c, 3*sizeof(GLfloat));
		//memcpy(flb, frontLeftBottom, 3*sizeof(GLfloat));
		//memcpy(bru, backRightTop, 3*sizeof(GLfloat));
		
		color[0] = c[0];
		color[1] = c[1];
		color[2] = c[2];

		flb[X] = frontLeftBottom[X];
		flb[Y] = frontLeftBottom[Y];
		flb[Z] = frontLeftBottom[Z];

		
		bru[X] = backRightTop[X];
		bru[Y] = backRightTop[Y];
		bru[Z] = backRightTop[Z];

		flu[X] = flb[X];
		flu[Y] = flb[Y];
		flu[Z] = bru[Z];

		frb[X] = bru[X];
		frb[Y] = flb[Y];
		frb[Z] = flb[Z];
		
		fru[X] = bru[X];
		fru[Y] = flb[Y];
		fru[Z] = bru[Z];
		
		blb[X] = flb[X];
		blb[Y] = bru[Y];
		blb[Z] = flb[Z];
		
		blu[X] = flb[X];
		blu[Y] = bru[Y];
		blu[Z] = bru[Z];

		brb[X] = bru[X];
		brb[Y] = bru[Y];
		brb[Z] = flb[Z];

	}*/
	
	MyQuad(GLfloat c[3], GLfloat frontLeftBottom[3], GLfloat frontRightTop[3], GLfloat backLeftBottom[3], GLfloat backRightTop[3])
	;/*{
		//memcpy(color, c, 3*sizeof(GLfloat));
		//memcpy(flb, frontLeftBottom, 3*sizeof(GLfloat));
		//memcpy(bru, backRightTop, 3*sizeof(GLfloat));
		
		color[0] = c[0];
		color[1] = c[1];
		color[2] = c[2];

		flb[X] = frontLeftBottom[X];
		flb[Y] = frontLeftBottom[Y];
		flb[Z] = frontLeftBottom[Z];

		fru[X] = frontRightTop[X];
		fru[Y] = frontRightTop[Y];
		fru[Z] = frontRightTop[Z];
				
		flu[X] = frontRightTop[X];
		flu[Y] = flb[Y];
		flu[Z] = frontRightTop[Z];

		frb[X] = flb[X];
		frb[Y] = fru[Y];
		frb[Z] = flb[Z];

		blb[X] = backLeftBottom[X];
		blb[Y] = backLeftBottom[Y];
		blb[Z] = backLeftBottom[Z];

		bru[X] = backRightTop[X];
		bru[Y] = backRightTop[Y];
		bru[Z] = backRightTop[Z];

		blu[X] = bru[X];
		blu[Y] = backLeftBottom[Y];
		blu[Z] = bru[Z];

		brb[X] = blb[X];
		brb[Y] = bru[Y];
		brb[Z] = flb[Z];
		
	}*/
	static void Rotatef(float angle, int XYZ, GLfloat p[3])
	;/*{
		float matrix[4][4] = {1,0,0,0,
							  0,1,0,0,
							  0,0,1,0,
							  0,0,0,1,};
		float angleRad = angle * M_PI /180.0;
		switch (XYZ)
		{
			case X:
			matrix[2][2] = matrix[1][1] = cos(angleRad);
			matrix[2][1] = -sin(angleRad);
			matrix[1][2] = sin(angleRad);
			break;
		case Y:
			matrix[2][2] = matrix[0][0] = cos(angleRad);
			matrix[0][2] = -sin(angleRad);
			matrix[2][0] = sin(angleRad);
			break;
		case Z:
			matrix[1][1] = matrix[0][0] = cos(angleRad);
			matrix[1][0] = -sin(angleRad);
			matrix[0][1] = sin(angleRad);
			break;
		}
		MatrixMul(matrix, p);
	}*/

	void Rotatef(float angle, int XYZ)
	; /*{
		float center[3];
			center[X] = blb[X] - flb[X];
			center[Y] = brb[Y] - flb[Y];
			center[Z] = fru[Z] - frb[Z];
		Translatef(center[X], center[Y], center[Z]);
		Rotatef(angle, XYZ, flb);
		Rotatef(angle, XYZ, flu);
		Rotatef(angle, XYZ, frb);
		Rotatef(angle, XYZ, fru);
		Rotatef(angle, XYZ, blb);
		Rotatef(angle, XYZ, blu);
		Rotatef(angle, XYZ, brb);
		Rotatef(angle, XYZ, bru);
		Translatef(-center[X], -center[Y], -center[Z]);
	}*/
	static void MatrixMul(float m[4][4], GLfloat p[3])
	;/*{
		GLfloat original[4] = {p[0], p[1], p[2], 1};
		for (int i=0; i < 3; ++i)
		{
			float accum = 0;
			for (int j=0; j < 4; ++j)
			{
				accum += m[i][j]*original[j];
			}
			p[i]=accum;
		}

	}*/
	void TranslateXf(float x) { Translatef(x, 0, 0); }
	void TranslateYf(float y) { Translatef(0, y, 0); }
	void TranslateZf(float z) { Translatef(0, 0, z); }
	void Translatef(float x, float y, float z)
	;/*{
		flb[X] += x;
		flb[Y] += y;
		flb[Z] += z;

		fru[X] += x;
		fru[Y] += y;
		fru[Z] += z;
				
		flu[X] += x;
		flu[Y] += y;
		flu[Z] += z;

		frb[X] += x;
		frb[Y] += y;
		frb[Z] += z;

		blb[X] += x;
		blb[Y] += y;
		blb[Z] += z;

		bru[X] += x;
		bru[Y] += y;
		bru[Z] += z;

		blu[X] += x;
		blu[Y] += y;
		blu[Z] += z;

		brb[X] += x;
		brb[Y] += y;
		brb[Z] += z;

	}*/

	GLfloat color[3],
			flb[3],
			flu[3],
			fru[3],
			frb[3],
			blb[3],
			blu[3],
			bru[3],
			brb[3];
/*

	    glTexCoord2f(100.0, 100.0);
	    glVertex3f(50.0, 50.0, 0.0);
	    glVertex3f(50.0, 50.0, 5.0);		
	    glVertex3f(50.0, 45.0, 5.0);				
	    glVertex3f(45.0, 45.0, 5.0);
	    glTexCoord2f(-100.0, 100.0);
	    glVertex3f(-50.0, 50.0, 0.0);
		glVertex3f(-50.0, 50.0, 5.0);
	    glTexCoord2f(-100.0, -100.0);
	    glVertex3f(-50.0, -50.0, 0.0);
	    glTexCoord2f(100.0, -100.0);
	    glVertex3f(50.0, -50.0, 0.0);
		glVertex3f(-50.0, -50.0, 5.0);
		
*/
/*

glNormal3d(1, 0, 0);
glTexCoord2f(0, 1);
glVertex3dv(c);
glTexCoord2f(0, 0);
glVertex3dv(b);
glTexCoord2f(1, 0);
glVertex3dv(f);
glTexCoord2f(1, 1);
*/
	void Construct();
	/*{
	glColor3fv(color);
	
	glTexCoord2f(0, 1);
	glVertex3fv(blu); //top
	glTexCoord2f(0, 0);
	glVertex3fv(flu);
	glTexCoord2f(1, 0);
	glVertex3fv(fru);
	glTexCoord2f(1, 1);
	glVertex3fv(bru);

	glTexCoord2f(0, 1);
	glVertex3fv(bru); //back
	glTexCoord2f(0, 0);
	glVertex3fv(brb);
	glTexCoord2f(1, 0);
	glVertex3fv(blb);
	glTexCoord2f(1, 1);
	glVertex3fv(blu);

	
	glTexCoord2f(0,1);
	glVertex3fv(blu); // left
	glTexCoord2f(0, 0);
	glVertex3fv(blb);
	glTexCoord2f(1,0);
	glVertex3fv(flb);
	glTexCoord2f(1, 1);
	glVertex3fv(flu);

	
	glTexCoord2f(0, 1);
	glVertex3fv(flu); //front
	glTexCoord2f(0, 0);
	glVertex3fv(flb);
	glTexCoord2f(1, 0);
	glVertex3fv(frb);
	glTexCoord2f(1, 1);
	glVertex3fv(fru);

	glTexCoord2f(0, 1);
	glVertex3fv(frb); //front
	glTexCoord2f(0, 0);
	glVertex3fv(brb);
	glTexCoord2f(1, 0);
	glVertex3fv(bru);
	glTexCoord2f(1, 1);
	glVertex3fv(fru);
	glVertex3fv(frb); 

	glTexCoord2f(0, 1);
	glVertex3fv(flb); // bottom
	glTexCoord2f(0, 0);
	glVertex3fv(blb);
	glTexCoord2f(1, 0);
	glVertex3fv(brb);
	glTexCoord2f(1, 1);
	glVertex3fv(frb);
	}*/
};


#endif
