// For CS 372 Battleship Game

#ifndef GLgui_h_included
#define GLgui_h_included


#if defined(_WIN32) || defined (__WIN32__) || defined(__WINDOWS__)
# include <Windows.h>
#endif
#include <cstdlib> 
using std::exit;
#ifndef __APPLE__
# include <GL/glut.h>
#else
# include <GLUT/glut.h> 
#endif

//For random double generator
#include <random>

// Other includes
#include "lib381/bitmapprinter.h"
#include "Board.h"


// For class BitmapPrinter
#include <sstream>
using std::ostringstream;
#include <iostream>
using std::cerr;
using std::endl;
#include <cstdlib>
using std::exit;
#include <iomanip>
using std::fixed;
using std::setprecision;
#include <vector>
using std::vector;


//-------------Initial Gui set-up variable for test case----------

//File is include properly
bool gui_Include = true; 

// Variables are initiated properly (Init function called)
bool gui_Init = false; 

// Variable displayed if board is properly displayed 
bool gui_Board = false;

//-----------------Window and Display variables-----------------

// Global variables
// Keyboard
const int ESCKEY = 27;         // ASCII value of Escape

// Window/viewport
const int startwinwd = 1200;    // Window width, height (pixels)
const int startwinht = 800;
const int startwinposx = 100;   // Window top-left corner x, y (pixels)
const int startwinposy = 25;
const double vxmin = -1.;      // Viewport bdaries in world (cam coords)
const double vxmax = 1.;
const double vymin = -1.;
const double vymax = 1.;
int winw = 1, winh = 1;        // Window width, height (pixels)

							   
// Viewport bdaries in world (cam coords)
double cam_xmin, cam_xmax, cam_ymin, cam_ymax;


//------------Battleship Grids------------\\

void GridDraw(); //Drawing function for the board.
void Labeler();

Board player1Home(10,true);
Board player1Target(10,false);
Board player2Home(10,true);
Board player2Target(10,false);



//-----------Misc Variables---------------

double savetime;    // Time of previous movement (sec)



bool p1turn = true;
bool p2turn = false;
bool showdisplay = true; //shows the text display
bool finbuttonhover = false; //if mouse is over the finished button


//-----------------Mouse Based Variables----------------

bool leftmousedown;     // true if left mouse button is down
bool rightmousedown;

double cam_mousex, cam_mousey; // Mouse pos in cam coords



//-----------------Drawing Functions---------------

//drawSquare
//draws the square target if it hasn't been targeted.
void drawSquare()
{
		glBegin(GL_POLYGON);
		glVertex2d(-1., -1.);
		glVertex2d(1., -1.);
		glVertex2d(1., 1.);
		glVertex2d(-1., 1.);
		glEnd();

}

// Draws a outlined square, using current GL states,
//  in the x,y plane, centered at the origin, aligned w/ x,y axes,
void drawEmpSquare()
{
	glBegin(GL_LINES);
	glColor3d(0.0, 0.0, 0.0);

	glVertex2d(-1., -1.);
	glVertex2d(1., -1.);

	glVertex2d(1., -1.);
	glVertex2d(1., 1.);

	glVertex2d(1., 1.);
	glVertex2d(-1., 1.);

	glVertex2d(-1., 1.);
	glVertex2d(-1., -1.);

	glEnd();
}

// drawCircle
// Draws a filled Circle
void drawCirc()
{
	glBegin(GL_POLYGON);
	for (int i = 0; i <= 300; i++) {
		double angle = 2 * 3.14 * i / 300;
		double x = cos(angle);
		double y = sin(angle);
		glVertex2d(x, y);
	}
	glEnd();
}

//drawHome1
//draws the home grid for player 1 
void drawHome1()
{
	
	for (int i = 0; i < player1Home.getSize(); i++)
	{
		for (int j = 0; j < player1Home.getSize(); j++)
		{
			glPushMatrix();
			glTranslated(-0.875 + (0.2*i), 0.875 - (0.2*j), 0.0);
			glScaled(0.1, 0.1, 0.0);
			drawEmpSquare();
			glPopMatrix();
		}
	}

	

}



//---------------Display, Idle, Reshape Functions-----------------\\

//myDisplay
//The glut display function
void myDisplay()
{
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	BitmapPrinter p(-0.9, 0.9, 0.1);

	// Initial transformation
	glLoadIdentity();

	glColor3d(0.4, 0.4, 0.4);

	//player1Home Grid
	glPushMatrix();
	glTranslated(0.45,-0.2,0.0);
	glScaled(0.75, 1.0, 0.0); //0.75 used for screen scale
	drawHome1();
	glPopMatrix();



	//'Finished' Button
	glPushMatrix();
	glColor3d(0.2, 0.7, 0.4);
	glTranslated(-0.75, 0.0, 0.0);
	glScaled(0.15*0.75, 0.15, 0.0);
	drawCirc();

	glColor3d(0., 0., 0.); // Black text
	glTranslated(0.5*.75, -1.0, 0.0);
	p.print("Finished!");
	glPopMatrix();


	//Instruction Text
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();

	glColor3d(0., 0., 0.);        // Black text

	//glTranslated(0.0, -0.5, 0.0); //modify to change text position
	if (showdisplay == true)
	{
		p.print("Welcome to Battleship");
		p.print("Please use the mouse to place ships");
		p.print("on the board by clicking a grid square,");
		p.print("then choosing a direction. Click the");
		p.print("'finished' button when you are done to ");
		p.print("pass it to the next player.");


	}
	glPopMatrix();                // Restore prev projection
	glMatrixMode(GL_MODELVIEW);
	glutSwapBuffers();
}


//myIdle
//Basic glut idle function
void myIdle()
{
	// Print OpenGL errors, if there are any (for debugging)
	static int error_count = 0;
	if (GLenum err = glGetError())
	{
		++error_count;
		cerr << "OpenGL ERROR " << error_count << ": "
			<< gluErrorString(err) << endl;
	}

	// Compute elapsed time since last movement
	double currtime = glutGet(GLUT_ELAPSED_TIME) / 1000.;
	double elapsedtime = currtime - savetime;
	savetime = currtime;
	if (elapsedtime > 0.1)
		elapsedtime = 0.1;

	//glutPostRedisplay();
}

// myReshape
// The GLUT reshape function
void myReshape(int w, int h)
{
	// Set viewport & save window dimensions in globals
	glViewport(0, 0, w, h);
	winw = w;
	winh = h;

	// Set up projection
	// Save max/min x/y coords in globals
	// Projection is orthographic. Aspect ratio is correct,
	// and region -1..1 in x, y always just fits in viewport.
	if (w > h)
	{
		cam_xmin = -double(w) / h;
		cam_xmax = double(w) / h;
		cam_ymin = -1.;
		cam_ymax = 1.;
	}
	else
	{
		cam_xmin = -1.;
		cam_xmax = 1.;
		cam_ymin = -double(h) / w;
		cam_ymax = double(h) / w;
	}
}



//-------------Mouse and Keyboard Functions-------------

// myKeyboard
// The GLUT keyboard function
void myKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case ESCKEY:  // Escape: quit
		exit(0);
		break;

	}
	glutPostRedisplay();
}

// saveMouse
// Given mouse pos in GLUT format; computes mouse pos in cam coords,
//  saves it in globals cam_mousex, cam_mousey.
// Uses globals winw, winh, cam_xmin, cam_xmax, cam_ymin, cam_ymax.
void saveMouse(int x, int y)
{
	double t;  // Intermediate value of lirping

	t = double(x) / winw;
	cam_mousex = cam_xmin + t * (cam_xmax - cam_xmin);

	t = double(y) / winh;
	cam_mousey = cam_ymax + t * (cam_ymin - cam_ymax);
}

// myMouse
// The GLUT mouse function
void myMouse(int button, int state, int x, int y)
{
	// Save old mouse pos, for relative mouse-movement computation
	double old_cam_mousex = cam_mousex;
	double old_cam_mousey = cam_mousey;
	// Find mouse pos in cam coords (saved in cam_mousex, cam_mousey)
	saveMouse(x, y);

	if (button == GLUT_LEFT_BUTTON)
	{
		leftmousedown = (state == GLUT_DOWN);


	}

	if (button == GLUT_RIGHT_BUTTON)
	{
		rightmousedown = (state == GLUT_DOWN);
		

	}
	glutPostRedisplay();
}

// myMotion
// The GLUT motion function
void myMotion(int x, int y)
{
	// Save old mouse pos, for relative mouse-movement computation
	double old_cam_mousex = cam_mousex;
	double old_cam_mousey = cam_mousey;

	// Find mouse pos in cam coords (saved in cam_mousex, cam_mousey)
	saveMouse(x, y);

	if (cam_mousex >= 0.0
		&& cam_mousex <= 0.0
		&& cam_mousey >= 0.0
		&& cam_mousey <= 0.0)
	{

	}


	glutPostRedisplay();
}

// myPassiveMotion
// The GLUT passiveMotion function
void myPassiveMotion(int x, int y)
{
	saveMouse(x, y);
	glutPostRedisplay();
}



//----------------Initialization and Main-----------------


// init
// Initialize GL states & global data
// Called by main after window creation
void init()
{
	//Initializes the seed for the random number generator
	std::srand(std::time(NULL));

	// Objects
	savetime = glutGet(GLUT_ELAPSED_TIME) / 1000.;

	gui_Init = true;

	//mouse
	cam_mousex = 0.0;
	cam_mousey = 0.0;

	// OpenGL Stuff
	glLineWidth(5.0);
	showdisplay = true;
}





#endif
