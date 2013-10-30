/*
 * Wall.cpp: A class for drawing the Wall.
 *
 * (c) 2001-2002: Stephen Chenney, University of Wisconsin at Madison.
 */


#include "Wall.h"
#include "Objects.h"
#include "libtarga.h"
#include <stdio.h>
#include <GL/glu.h>

// Destructor
Wall::~Wall(void)
{
    if ( initialized )
    {
	glDeleteLists(display_list, 1);
	glDeleteTextures(1, &texture_obj);
    }
}
void Quad(GLfloat color[3], GLfloat p1[3] , GLfloat p2[3] , GLfloat p3[3] , GLfloat p4[3] , GLfloat width, int widx);/*
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

*/

// Initializer. Returns false if something went wrong, like not being able to
// load the texture.
bool
Wall::Initialize(void)
{
    ubyte   *image_data;
    int	    image_height, image_width;

    // Load the image for the texture. The texture file has to be in
    // a place where it will be found.
    if ( ! ( image_data = (ubyte*)tga_load("wall.tga", &image_width,
					   &image_height, TGA_TRUECOLOR_24) ) )
    {
		
	fprintf(stderr, "Wall::Initialize: Couldn't load wall.tga\n");
	return false;
    }

    // This creates a texture object and binds it, so the next few operations
    // apply to this texture.
    glGenTextures(1, &texture_obj);
    glBindTexture(GL_TEXTURE_2D, texture_obj);

    // This sets a parameter for how the texture is loaded and interpreted.
    // basically, it says that the data is packed tightly in the image array.
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // This sets up the texture with high quality filtering. First it builds
    // mipmaps from the image data, then it sets the filtering parameters
    // and the wrapping parameters. We want the grass to be repeated over the
    // Wall.
    gluBuild2DMipmaps(GL_TEXTURE_2D,3, image_width, image_height, 
		      GL_RGB, GL_UNSIGNED_BYTE, image_data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		    GL_NEAREST_MIPMAP_LINEAR);

    // This says what to do with the texture. Modulate will multiply the
    // texture by the underlying color.
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 

    // Now do the geometry. Create the display list.
    display_list = glGenLists(1);
    glNewList(display_list, GL_COMPILE);
	// Use white, because the texture supplies the color.
	glColor3f(1.0, 1.0, 1.0);

	// The surface normal is up for the Wall.
	glNormal3f(0.0, 0.0, 1.0);

	// Turn on texturing and bind the grass texture.
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_obj);

	// Draw the Wall as a quadrilateral, specifying texture coordinates.
	glBegin(GL_QUADS);
	GLfloat color[3]={1,1,1},
			flb[3]={50.0, 50.0, 0.0},
			flu[3]={50.0, 50.0, 5.0},
			fru[3]={45.0, 50.0, 5.0},
			frb[3]={45.0, 50.0, 0.0},
			blb[3]={50.0, 45.0, 0.0},
			blu[3]={50.0, 45.0, 5.0},
			bru[3]={45.0, 45.0, 5.0},
			brb[3]={45.0, 45.0, 0.0};
	
	glTranslatef(100,100,0);
	MyQuad(color, flb, bru).Construct();

	
	glTranslatef(-50,-50,0);
	
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
	

	//Quad(color, lb, lu, ru,rb, 5.0f, 1);

	/*glVertex3f(50.0, 50.0, 0.0);
	glVertex3f(50.0, 50.0, 5.0);		
	glVertex3f(50.0, 45.0, 5.0);				
	glVertex3f(45.0, 45.0, 5.0);
	  */  
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
	glEnd();

	// Turn texturing off again, because we don't want everything else to
	// be textured.
	glDisable(GL_TEXTURE_2D);
    glEndList();

    // We only do all this stuff once, when the GL context is first set up.
    initialized = true;

    return true;
}


// Draw just calls the display list we set up earlier.
void
Wall::Draw(void)
{
    glPushMatrix();
    glCallList(display_list);
    glPopMatrix();
}


