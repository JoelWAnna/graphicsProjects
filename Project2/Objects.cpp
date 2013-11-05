#include "Objects.h"
MyQuad::MyQuad(GLfloat c[3], GLfloat frontLeftBottom[3], GLfloat backRightTop[3])
	{
		//memcpy(color, c, 3*sizeof(GLfloat));
		//memcpy(flb, frontLeftBottom, 3*sizeof(GLfloat));
		//memcpy(bru, backRightTop, 3*sizeof(GLfloat));
		copyvector(color, c);
		/*color[0] = c[0];
		color[1] = c[1];
		color[2] = c[2];*/

	/*NUM_POINTS = 8,*/
		/*	points[FLB][3],
			points[FLU][3],
			points[FRU][3],
			points[FRB][3],
			points[BLB][3],
			points[BLU][3],
			points[BRU][3],
			points[BRB][3],*/
		copyvector(points[FLB], frontLeftBottom);
		/*flb[X] = frontLeftBottom[X];
		flb[Y] = frontLeftBottom[Y];
		flb[Z] = frontLeftBottom[Z];*/

		copyvector(points[BRU], backRightTop);
		/*bru[X] = backRightTop[X];
		bru[Y] = backRightTop[Y];
		bru[Z] = backRightTop[Z];*/
		copyvector(points[FLU], points[FLB]);
		points[FLU][Z] = points[BRU][Z];
		/*
		flu[X] = flb[X];
		flu[Y] = flb[Y];
		flu[Z] = bru[Z];
*/
		copyvector(points[FRB], points[FLB]);
		points[FRB][X] = points[BRU][X];
		/*frb[X] = bru[X];
		frb[Y] = flb[Y];
		frb[Z] = flb[Z];*/
		
		copyvector(points[FRU], points[BRU]);
		points[FRU][Y] = points[FLB][Y];
		/*fru[X] = bru[X];
		fru[Y] = flb[Y];
		fru[Z] = bru[Z];
		*/
		copyvector(points[BLB], points[FLB]);
		points[BLB][Y] = points[BRU][Y];
		/*blb[X] = flb[X];
		blb[Y] = bru[Y];
		blb[Z] = flb[Z];*/
		
		copyvector(points[BLU], points[BRU]);
		points[BLU][X] = points[FLB][X];
		/*blu[X] = flb[X];
		blu[Y] = bru[Y];
		blu[Z] = bru[Z];
*/
		copyvector(points[BRB], points[BRU]);
		points[BRB][Z] = points[FLB][Z];
		/*
		brb[X] = bru[X];
		brb[Y] = bru[Y];
		brb[Z] = flb[Z];*/

	}
	
MyQuad::MyQuad(GLfloat c[3], GLfloat frontLeftBottom[3], GLfloat frontRightTop[3], GLfloat backLeftBottom[3], GLfloat backRightTop[3])
	{
		//memcpy(color, c, 3*sizeof(GLfloat));
		//memcpy(flb, frontLeftBottom, 3*sizeof(GLfloat));
		//memcpy(bru, backRightTop, 3*sizeof(GLfloat));
		copyvector(color, c);
		/*color[0] = c[0];
		color[1] = c[1];
		color[2] = c[2];*/

		copyvector(points[FLB], frontLeftBottom);
		/*flb[X] = frontLeftBottom[X];
		flb[Y] = frontLeftBottom[Y];
		flb[Z] = frontLeftBottom[Z];*/
		copyvector(points[FRU], frontRightTop);
		/*fru[X] = frontRightTop[X];
		fru[Y] = frontRightTop[Y];
		fru[Z] = frontRightTop[Z];*/
		
		copyvector(points[FLU], points[FRU]);
		points[FLU][Y] = points[FLB][Y];
		/*
		flu[X] = frontRightTop[X];
		flu[Y] = flb[Y];
		flu[Z] = frontRightTop[Z];*/
		
		copyvector(points[FRB], points[FLB]);
		points[FRB][Y] = points[FRU][Y];
		/*frb[X] = flb[X];
		frb[Y] = fru[Y];
		frb[Z] = flb[Z];*/

		copyvector(points[BLB], backLeftBottom);
		/*blb[X] = backLeftBottom[X];
		blb[Y] = backLeftBottom[Y];
		blb[Z] = backLeftBottom[Z];*/
		copyvector(points[BRU], backRightTop);
		/*bru[X] = backRightTop[X];
		bru[Y] = backRightTop[Y];
		bru[Z] = backRightTop[Z];*/

		copyvector(points[BLU], points[BRU]);
		points[BLU][Y] = points[BLB][Y];
		/*blu[X] = bru[X];
		blu[Y] = backLeftBottom[Y];
		blu[Z] = bru[Z];*/

		points[BRB][X] = points[BLB][X];
		points[BRB][Y] = points[BRU][Y];
		points[BRB][Z] = points[FLB][Z];
		/*brb[X] = blb[X];
		brb[Y] = bru[Y];
		brb[Z] = flb[Z];*/

	}

void MyQuad::Rotatef(float angle, int XYZ, GLfloat p[3])
	{
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
	}

void MyQuad::Rotatef(float angle, int XYZ)
	{
		float center[3];
			center[X] = blb[X] - flb[X];
			center[Y] = brb[Y] - flb[Y];
			center[Z] = fru[Z] - frb[Z];
		Translatef(center[X], center[Y], center[Z]);
		Rotatef(angle, XYZ, points[FLB]);
		Rotatef(angle, XYZ, points[FLU]);
		Rotatef(angle, XYZ, points[FRB]);
		Rotatef(angle, XYZ, points[FRU]);
		Rotatef(angle, XYZ, points[BLB]);
		Rotatef(angle, XYZ, points[BLU]);
		Rotatef(angle, XYZ, points[BRB]);
		Rotatef(angle, XYZ, points[BRU]);
		Translatef(-center[X], -center[Y], -center[Z]);
	}

void MyQuad::MatrixMul(float m[4][4], GLfloat p[3])
	{
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

	}
void MyQuad::Translatef(float x, float y, float z)
	{
		for (int i = FLB; i < NUM_POINTS; ++i)
		{
			points[i][X] += x;
			points[i][Y] += y;
			points[i][Z] += z;
		}
		/*flb[X] += x;
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
*/
	}

void MyQuad::Construct() {
	glColor3fv(color);
	
	glTexCoord2f(0, 1);
	glVertex3fv(blu); //top
	glTexCoord2f(0, 0);
	glVertex3fv(points[FLU]);
	glTexCoord2f(1, 0);
	glVertex3fv(points[FRU]);
	glTexCoord2f(1, 1);
	glVertex3fv(points[BRU]);

	glTexCoord2f(0, 1);
	glVertex3fv(points[BRU]); //back
	glTexCoord2f(0, 0);
	glVertex3fv(points[BRB]);
	glTexCoord2f(1, 0);
	glVertex3fv(points[BLB]);
	glTexCoord2f(1, 1);
	glVertex3fv(points[BLU]);

	
	glTexCoord2f(0,1);
	glVertex3fv(points[BLU]); // left
	glTexCoord2f(0, 0);
	glVertex3fv(points[BLB]);
	glTexCoord2f(1,0);
	glVertex3fv(points[FLB]);
	glTexCoord2f(1, 1);
	glVertex3fv(points[FLU]);

	
	glTexCoord2f(0, 1);
	glVertex3fv(points[FLU]); //front
	glTexCoord2f(0, 0);
	glVertex3fv(points[FLB]);
	glTexCoord2f(1, 0);
	glVertex3fv(points[FRB]);
	glTexCoord2f(1, 1);
	glVertex3fv(points[FRU]);

	glTexCoord2f(0, 1);
	glVertex3fv(points[FRB]); //front
	glTexCoord2f(0, 0);
	glVertex3fv(points[BRB]);
	glTexCoord2f(1, 0);
	glVertex3fv(points[BRU]);
	glTexCoord2f(1, 1);
	glVertex3fv(points[FRU]);
	glVertex3fv(points[FRB]); 

	glTexCoord2f(0, 1);
	glVertex3fv(points[FLB]); // bottom
	glTexCoord2f(0, 0);
	glVertex3fv(points[BLB]);
	glTexCoord2f(1, 0);
	glVertex3fv(points[BRB]);
	glTexCoord2f(1, 1);
	glVertex3fv(points[FRB]);
	}



