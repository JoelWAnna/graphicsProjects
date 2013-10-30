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
	MyQuad(GLfloat c[3], GLfloat frontLeftBottom[3], GLfloat backRightTop[3])
	{
		memcpy(color, c, 3*sizeof(GLfloat));
		memcpy(flb, frontLeftBottom, 3*sizeof(GLfloat));
		memcpy(bru, backRightTop, 3*sizeof(GLfloat));
		flu[0] = flb[0];
		flu[1] = flb[1];
		flu[2] = bru[2];

		frb[0] = bru[0];
		frb[1] = flb[1];
		frb[2] = flb[2];
		
		fru[0] = bru[0];
		fru[1] = flb[1];
		fru[2] = bru[2];
		
		blb[0] = flb[0];
		blb[1] = bru[1];
		blb[2] = flb[2];
		
		blu[0] = flb[0];
		blu[1] = flb[1];
		blu[2] = bru[2];

		brb[0] = bru[0];
		brb[1] = bru[1];
		brb[2] = flb[2];

	}
	GLfloat color[3],
			flb[3],
			flu[3],
			fru[3],
			frb[3],
			blb[3],
			blu[3],
			bru[3],
			brb[3];
	void Construct() {
	glVertex3fv(blu); //top
	glVertex3fv(flu);
	glVertex3fv(fru);	
	glVertex3fv(bru);

	glVertex3fv(bru); //back
	glVertex3fv(brb);
	glVertex3fv(blb);	
	glVertex3fv(blu);

	glVertex3fv(blu); // left
	glVertex3fv(blb);
	glVertex3fv(flb);	
	glVertex3fv(flu);

	glVertex3fv(flu); //front
	glVertex3fv(flb);
	glVertex3fv(frb);	
	glVertex3fv(fru);

	glVertex3fv(frb); //front
	glVertex3fv(brb);
	glVertex3fv(bru);	
	glVertex3fv(fru);
	glVertex3fv(frb); 

	glVertex3fv(flb); // bottom
	glVertex3fv(blb);
	glVertex3fv(brb);	
	glVertex3fv(frb);
	}
};


#endif
