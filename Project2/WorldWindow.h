/*
 * CS559 Maze Project
 *
 * Class header file for the WorldWindow class. The WorldWindow is
 * the window in which the viewer's view of the world is displayed.
 *
 * (c) Stephen Chenney, University of Wisconsin at Madison, 2001-2002
 *
 */

#ifndef _WORLDWINDOW_H_
#define _WORLDWINDOW_H_

#include <Fl/Fl.h>
#include <Fl/Fl_Gl_Window.h>
#include <vector>

#include "Objects.h"
enum
{
	DEFAULT = 0,
	ROLLERCOASTER,
	WALK,
	FERRISWHEEL,
	MAX_DISPLAY_MODES
};

// Subclass the Fl_Gl_Window because we want to draw OpenGL in here.
class WorldWindow : public Fl_Gl_Window {
    public:
	// Constructor takes window position and dimensions, the title.
	WorldWindow(int x, int y, int w, int h, char *label);
	~WorldWindow()
	{
		for (unsigned i = 0; i < items.size(); ++i)
		{
			delete items.at(i);
			items.at(i) = NULL;;
		}
	}

	// draw() method invoked whenever the view changes or the window
	// otherwise needs to be redrawn.
	void	draw(void);

	// Event handling method. Uses only mouse events.
	int	handle(int);

	// Update the world according to any events that have happened since
	// the last time this method was called.
	bool	Update(float);

    private:
	int display_mode;
	std::vector<OGLItem*> items;	// Items to draw each frame
	int rollercoaster, ferriswheel;
	static const double FOV_X; // The horizontal field of view.

	float	phi;	// Viewer's inclination angle.
	float	theta;	// Viewer's azimuthal angle.
	float	dist;	// Viewer's distance from the look-at point.
	float home_x;
	float home_y;
	float home_phi;
	float home_theta;
	float home_dist;
				
	float	x_at;	// The x-coord to look at.
	float	y_at;	// The y-coord to look at. z_at is assumed 2.0.

	int     button;	// The mouse button that is down, -1 if none.
	int	x_last;	// The location of the most recent mouse event
	int	y_last;
	int	x_down; // The location of the mouse when the button was pushed
	int	y_down;
	float   phi_down;   // The view inclination angle when the mouse
			    // button was pushed
	float   theta_down; // The view azimuthal angle when the mouse
			    // button was pushed
	float	dist_down;  // The distance when the mouse button is pushed.
	float	x_at_down;  // The x-coord to look at when the mouse went down.
	float	y_at_down;  // The y-coord to look at when the mouse went down.

	void	Drag(float);	// The function to call for mouse drag events
	void KeyMove(int key);
};


#endif
