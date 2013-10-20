/*
 * Tree.h: Header file for a class that draws the tree.
 *
 */


#ifndef _TREE_H_
#define _TREE_H_

#include <Fl/gl.h>
#include <cmath>
#define M_PI       3.14159265358979323846
class Tree {
  private:
    GLubyte display_list;   // The display list that does all the work.
    GLuint  texture_obj;    // The object for the grass texture.
    bool    initialized;    // Whether or not we have been initialised.

  public:
    // Constructor. Can't do initialization here because we are
    // created before the OpenGL context is set up.
    Tree(void) { display_list = 0; initialized = false; };

    // Destructor. Frees the display lists and texture object.
    ~Tree(void);

    // Initializer. Creates the display list.
    bool    Initialize(void);

    // Does the drawing.
    void    Draw(void);
};


#endif
