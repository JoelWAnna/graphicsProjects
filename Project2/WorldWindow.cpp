/*
 * CS559 Maze Project
 *
 * Class file for the WorldWindow class.
 *
 * (c) Stephen Chenney, University of Wisconsin at Madison, 2001-2002
 *
 */

#include "WorldWindow.h"
#include <Fl/math.h>
#include <Fl/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <iostream>

#include <FL/fl_ask.H>
const char * HELPmsg = "Press F1 to show this help window\n" \
		   "Press Tab to switch display modes\n" \
		"A and D change theta\n W and S change phi\n" \
		"arrow keys move through the world\n" \
		"- and = change the distance\n" \
		"Home returns to the starting point of the current display mode."; 
const double WorldWindow::FOV_X = 45.0;

WorldWindow::WorldWindow(int x, int y, int width, int height, char *label)
	: Fl_Gl_Window(x, y, width, height, label)
{
    button = -1;
	display_mode = false;
    // Initial viewing parameters.
    home_phi = phi = 45.0f;
    home_theta = theta = 0.0f;
    home_dist = dist = 100.0f;
    home_x = x_at = 0.0f;
    home_y = y_at = 0.0f;

}


void
WorldWindow::draw(void)
{
    double  eye[3];
    float   color[4], dir[4];

    if ( ! valid() )
    {
	// Stuff in here doesn't change from frame to frame, and does not
	// rely on any coordinate system. It only has to be done if the
	// GL context is damaged.

	double	fov_y;

	// Sets the clear color to sky blue.
	glClearColor(0.53f, 0.81f, 0.92f, 1.0);

	// Turn on depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Turn on back face culling. Faces with normals away from the viewer
	// will not be drawn.
	glEnable(GL_CULL_FACE);

	// Enable lighting with one light.
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	// Ambient and diffuse lighting track the current color.
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	// Turn on normal vector normalization. You don't have to give unit
	// normal vector, and you can scale objects.
	glEnable(GL_NORMALIZE);

	// Set up the viewport.
	glViewport(0, 0, w(), h());

	// Set up the persepctive transformation.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	fov_y = 360.0f / M_PI * atan(h() * tan(FOV_X * M_PI / 360.0) / w());
	gluPerspective(fov_y, w() / (float)h(), 1.0, 1000.0);

	// Do some light stuff. Diffuse color, and zero specular color
	// turns off specular lighting.
	color[0] = 1.0f; color[1] = 1.0f; color[2] = 1.0f; color[3] = 1.0f;
	glLightfv(GL_LIGHT0, GL_DIFFUSE, color);
	color[0] = 0.0f; color[1] = 0.0f; color[2] = 0.0f; color[3] = 1.0f;
	glLightfv(GL_LIGHT0, GL_SPECULAR, color);

	// Initialize all the objects.
	items.push_back(new Track()); rollercoaster = 0; // update roller coaster to the index in items of the track
	items.push_back(new Ground());
	items.push_back(new Wall());
	items.push_back(new Tree());
	items.push_back(new FerrisWheel()); ferriswheel = 4; // update ferris wheel to the index in items of the track


	auto iter = items.begin();
	auto iterEnd = items.end();
	while (iter != iterEnd)
	{
		(*iter)->Initialize();
		++iter;
	}

fl_message(HELPmsg);
    }

    // Stuff out here relies on a coordinate system or must be done on every
    // frame.

    // Clear the screen. Color and depth.
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


	switch (display_mode)
	{
	case ROLLERCOASTER:
		items[rollercoaster]->View();
		break;
	case FERRISWHEEL:
		//items[ferriswheel]->View();
		//break;
	case WALK:
	default:
		{
		// Set up the viewing transformation. The viewer is at a distance
		// dist from (x_at, y_ay, 2.0) in the direction (theta, phi) defined
		// by two angles. They are looking at (x_at, y_ay, 2.0) and z is up.
		eye[0] = x_at + dist * cos(theta * M_PI / 180.0) * cos(phi * M_PI / 180.0);
		eye[1] = y_at + dist * sin(theta * M_PI / 180.0) * cos(phi * M_PI / 180.0);
		eye[2] = 2.0 + dist * sin(phi * M_PI / 180.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(eye[0], eye[1], eye[2], x_at, y_at, 2.0, 0.0, 0.0, 1.0);
		}
	}
    // Position the light source. This has to happen after the viewing
    // transformation is set up, so that the light stays fixed in world
    // space. This is a directional light - note the 0 in the w component.
    dir[0] = 1.0; dir[1] = 1.0; dir[2] = 1.0; dir[3] = 0.0;
    glLightfv(GL_LIGHT0, GL_POSITION, dir);


	auto iter = items.begin();
	auto iterEnd = items.end();
	while (iter != iterEnd)
	{
		(*iter)->Draw();
		++iter;
	}
}


void
WorldWindow::Drag(float dt)
{
    int	    dx = x_down - x_last;
    int     dy = y_down - y_last;

    switch ( button )
    {
      case FL_LEFT_MOUSE:
	// Left button changes the direction the viewer is looking from.
	theta = theta_down + 360.0f * dx / (float)w();
	while ( theta >= 360.0f )
	    theta -= 360.0f;
	while ( theta < 0.0f )
	    theta += 360.0f;
	phi = phi_down + 90.0f * dy / (float)h();
	if ( phi > 89.0f )
	    phi = 89.0f;
	if ( phi < -5.0f )
	    phi = -5.0f;
	break;
      case FL_MIDDLE_MOUSE:
	// Middle button moves the viewer in or out.
	dist = dist_down - ( 0.5f * dist_down * dy / (float)h() );
	if ( dist < 1.0f )
	    dist = 1.0f;
	break;
      case FL_RIGHT_MOUSE: {
	// Right mouse button moves the look-at point around, so the world
	// appears to move under the viewer.
	float	x_axis[2];
	float	y_axis[2];

	x_axis[0] = -(float)sin(theta * M_PI / 180.0);
	x_axis[1] = (float)cos(theta * M_PI / 180.0);
	y_axis[0] = x_axis[1];
	y_axis[1] = -x_axis[0];

	x_at = x_at_down + 100.0f * ( x_axis[0] * dx / (float)w()
				    + y_axis[0] * dy / (float)h() );
	y_at = y_at_down + 100.0f * ( x_axis[1] * dx / (float)w()
				    + y_axis[1] * dy / (float)h() );
	} break;
      default:;
    }
}


bool
WorldWindow::Update(float dt)
{
    // Update the view. This gets called once per frame before doing the
    // drawing.

    if ( button != -1 ) // Only do anything if the mouse button is down.
	Drag(dt);

    // Animate the train.
	auto iter = items.begin();
	auto iterEnd = items.end();
	while (iter != iterEnd)
	{
		(*iter)->Update(dt);
		++iter;
	}

    return true;
}

inline void  runFunction(std::vector<OGLItem*> &vector, void (OGLItem::* )());

void WorldWindow::KeyMove(int key)
{
	if (display_mode == ROLLERCOASTER)
		return;
	float dx = 0;
	float dy = 0;
	switch(key)
	{
	case '\\':
		std::cout << "phi: "<< phi << std::endl
				  << "theta: "<< theta << std::endl
				  << "dist: "<< dist << std::endl
				  << "x_at: "<< x_at << std::endl
				  << "y_at: "<< y_at << std::endl;
		break;
	case '-':
		if (dist < 360)
			dist += .5;
		break;
	case '=':
		if (dist > 1.5)
			dist -= .5;
		break;
	case 'd': //right 
		theta += 1;
		while (theta > 360)
			theta -= 360;
		break;
	case 'a': // LEFT
		theta -= 1;
		while (theta < -360)
			theta +=360;
		break;
	case 's': // DOWN
		phi -= 1;
		
		if (phi < -89)
			phi = -89;
	//	if (phi < -5)
	//		phi = -5;
		break;
	case 'w': // UP
		phi += 1;
		if (phi > 89)
			phi = 89;
		break;
	case FL_Home:
		if (display_mode == DEFAULT || display_mode == WALK || display_mode == FERRISWHEEL)
		{
			phi = home_phi;
			theta = home_theta;
			dist = home_dist;
				
			x_at = home_x;
			y_at = home_y;
		}
		break;
	case FL_Left:
		dx = -5;
		break;
	case FL_Up:
		dy = -5;
		break;
	case FL_Right:
		dx = +5;
		break;
	case FL_Down:
		dy = +5;
		break;
	}

	if (dx != 0 || dy != 0)
	{
			float x_axis[2],y_axis[2];
			x_axis[0] = -(float)sin(theta * M_PI / 180.0);
			x_axis[1] = (float)cos(theta * M_PI / 180.0);
			y_axis[0] = x_axis[1];
			y_axis[1] = -x_axis[0];

			x_at = x_at + 100.0f * ( x_axis[0] * dx / (float)w()
				    + y_axis[0] * dy / (float)h() );
			y_at = y_at + 100.0f * ( x_axis[1] * dx / (float)w()
				    + y_axis[1] * dy / (float)h() );

		}
}
int
WorldWindow::handle(int event)
{
    // Event handling routine. Only looks at mouse events.
    // Stores a bunch of values when the mouse goes down and keeps track
    // of where the mouse is and what mouse button is down, if any.
	
	float	x_axis[2];
	float	y_axis[2];
	if (display_mode == WALK)
	{
			// Right mouse button moves the look-at point around, so the world
	// appears to move under the viewer.

	x_axis[0] = -(float)sin(theta * M_PI / 180.0);
	x_axis[1] = (float)cos(theta * M_PI / 180.0);
	y_axis[0] = x_axis[1];
	y_axis[1] = -x_axis[0];

	}


    switch ( event )
    {
	  case FL_KEYDOWN:	
	  //case FL_KEYUP:
	  {
		  int key = Fl::event_key();
		  switch(key)
		  {
		  case FL_Tab:
			display_mode = (display_mode + 1) % MAX_DISPLAY_MODES;
			if (display_mode == DEFAULT)
			{
				home_phi = phi = 45.0f;
				home_theta = theta = 0.0f;
				home_dist = dist = 100.0f;
				home_x = x_at = 0.0f;
				home_y = y_at = 0.0f;
			}

			if (display_mode == WALK)
			{
				home_phi = phi;
				home_theta = theta;
				home_dist = dist;
				home_x = x_at;
				home_y = y_at;
			}
			if (display_mode == FERRISWHEEL)
			{
				home_phi = 10.0f;
				home_theta = -100.0f;
				home_dist = 106.5f;
				home_x = -10.6072f;
				home_y = 94.9089f;
				KeyMove(FL_Home);
			}
			break;
		  case FL_F + 1:
			{

			fl_message(HELPmsg);
			//MessageBoxA(NULL, msg, "Help Window", 0);
			}
			break;
		  default:
			KeyMove(key);
			break;
		  }

		
	  }
	  break;
      case FL_PUSH:
		  if (display_mode) break;
        button = Fl::event_button();
	x_last = x_down = Fl::event_x();
	y_last = y_down = Fl::event_y();
	phi_down = phi;
	theta_down = theta;
	dist_down = dist;
	x_at_down = x_at;
	y_at_down = y_at;
	return 1;
      case FL_DRAG:
		  if (display_mode) break;
		x_last = Fl::event_x();
		y_last = Fl::event_y();
	return 1;
      case FL_RELEASE:
        button = -1;
	return 1;
    }
	

    // Pass any other event types on the superclass.
    return Fl_Gl_Window::handle(event);
}
