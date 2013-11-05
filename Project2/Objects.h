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
enum
{
	X = 0,
	Y = 1,
	Z = 2,
	RGB = 3,
	FLB = 0,
	FLU = 1,
	FRU = 2,
	FRB = 3,
	BLB = 4,
	BLU = 5,
	BRU = 6,
	BRB = 7,
	NUM_POINTS = 8,
};
struct MyQuad
{
	GLfloat color[3],
			points[NUM_POINTS][3],
			flb[3],
			flu[3],
			fru[3],
			frb[3],
			blb[3],
			blu[3],
			bru[3],
			brb[3];

	static void copyvector(GLfloat * dest, GLfloat * source, int size=3)
	{
		for (int i = 0; i < size; ++i)
		{
			dest[i]=source[i];
		}
	}

	MyQuad(GLfloat c[3], GLfloat frontLeftBottom[3], GLfloat backRightTop[3]);
	
	MyQuad(GLfloat c[3], GLfloat frontLeftBottom[3], GLfloat frontRightTop[3], GLfloat backLeftBottom[3], GLfloat backRightTop[3]);

	static void Rotatef(float angle, int XYZ, GLfloat p[3]);
	
	void Rotatef(float angle, int XYZ);
	static void MatrixMul(float m[4][4], GLfloat p[3]);
	void TranslateXf(float x) { Translatef(x, 0, 0); }
	void TranslateYf(float y) { Translatef(0, y, 0); }
	void TranslateZf(float z) { Translatef(0, 0, z); }
	void Translatef(float x, float y, float z);
	void Construct();
};


#endif
