/*
 * FerrisWheel.h: Header file for a class that draws the FerrisWheel.
 *
 */


#ifndef _OGL__ITEM__
#define _OGL__ITEM__

class OGLItem {
  public:
	  virtual ~OGLItem(void){};

    // Initializer. Creates the display list.
    virtual bool    Initialize(void)=0;

	virtual void    Update(float) {};	// Updates the location 

    // Does the drawing.
    virtual void    Draw(void)=0;
	virtual void    View(void) {};
};


#endif
