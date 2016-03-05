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
#include <math.h>

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
#include <tuple>
using std::tuple;

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

// (1024x768) vs 960x720 vs vs 900x675 vs  800 x 600

const int startwinwd = 800;    // Window width, height (pixels)
const int startwinht = 600;
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

Board player1Home(10, true);
Board player1Target(10, false);
Board player2Home(10, true);
Board player2Target(10, false);

float gridstartx = -0.2;
float gridstarty = 0.65;


//-----------Misc Variables---------------

double savetime;    // Time of previous movement (sec)



bool p1turn = true;
bool p2turn = false;
bool showdisplay = true; //shows the text display
bool finbuttonhover = false; //if mouse is over the finished button

//variables for the 'finished' button
float finish_x = -1.;
float finish_y = 0.3; //0.0


float finishcol[3] = { 0.2, 0.7, 0.4 };
float finish_base[3] = { 0.2,0.7,0.4 };
float finish_hover[3] = { 0.5, 1.0, 0.7 };
float finish_clicked[3] = { 0.1, 0.5, 0.2 };

//color variables for the box function
//An array of 5 ships with the second array being the color and size
float boxcol[5][4];

float box_base[3] = { 0.3,0.5,0.7 };
float box_hover[3] = { 0.5, 0.7, 1.0 };
float box_clicked[3] = { 0.1, 0.2, 0.5 };

bool box_used[5]; //if one of the ship buttons has been used.

int curr_ship = -1; //set to arbitrary value outside of # of ships.



//-----------------Mouse Based Variables----------------

bool leftmousedown;     // true if left mouse button is down
bool rightmousedown;

double cam_mousex, cam_mousey; // Mouse pos in cam coords

bool isClicking = false;
int outeri = 0;
int outerj = 0;

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

//boxButton()
//Draws a box for the ship buttons
void boxButton()
{
	glPushMatrix();
	glScaled(0.25, 0.05, 0.0);
	drawSquare();
	glPopMatrix();

}

//boxButtonHover()
//
void boxButtonHover()
{
	for (int i = 0; i < 5; i++)
	{
		if (cam_mousex <= -0.75
			&& cam_mousex >= -1.25
			&& cam_mousey <= (-0.28 + (-0.125 * i) + 0.05)
			&& cam_mousey >= (-0.28 + (-0.125 * i) - 0.05) )
		{
			boxcol[i][0] = box_hover[0];
			boxcol[i][1] = box_hover[1];
			boxcol[i][2] = box_hover[2];
		}
		else
		{
			boxcol[i][0] = box_base[0];
			boxcol[i][1] = box_base[1];
			boxcol[i][2] = box_base[2];
		}
	}
}

//boxButtonClic()
//
void boxButtonClick()
{
	for (int i = 0; i < 5; i++)
	{
		if (cam_mousex <= -0.75
			&& cam_mousex >= -1.25
			&& cam_mousey <= (-0.28 + (-0.125 * i) + 0.05)
			&& cam_mousey >= (-0.28 + (-0.125 * i) - 0.05))
		{
			boxcol[i][0] = box_clicked[0];
			boxcol[i][1] = box_clicked[1];
			boxcol[i][2] = box_clicked[2];
			curr_ship = i;
		}
	}
}



//boxWords()
//
void boxWords()
{
	glColor3d(0.0, 0.0, 0.0);
	BitmapPrinter button(0.0, 0.0, 0.1);


	glPushMatrix();
	glTranslated(-1.24, -0.3, 0.0);
	if (box_used[0] == false)
	{
		button.print("Aircraft Carrier");
	}
	glPopMatrix();

	glPushMatrix();
	glTranslated(-1.24, -0.41, 0.0);
	if (box_used[1] == false)
	{
		button.print("Battleship");
	}
	glPopMatrix();

	/*

	//glPushMatrix();
	glTranslated(-1.24, -0.34, 0.0);
	if (box_used[2] == false)
	{
		button.print("Submarine");
	}
	//glPopMatrix();

	//glPushMatrix();
	glTranslated(-1.24, -0.37, 0.0);
	if (box_used[3] == false)
	{
		button.print("Destroyer");
	}
	//glPopMatrix();

	//glPushMatrix();
	glTranslated(-1.24, -0.39, 0.0);
	if (box_used[4] == false)
	{
		button.print("Patrol Boat");
	}
	//glPopMatrix();
	*/

}

//drawHome1
//draws the home grid for player 1 
void drawHome1()
{
	for (int i = 0; i < player1Home.getSize(); i++)
	{
		for (int j = 0; j < player1Home.getSize(); j++)
		{
			glColor3d(0.4, 0.4, 0.4);
			float x = (0.2*i);
			float y = -(0.2*j);

			glPushMatrix();
			glColor3d(0.4, 0.4, 0.4);
			glTranslated(x, y, 0.0);
			glScaled(0.1, 0.1, 0.0);
			drawEmpSquare();

			if (player1Home.board_[i][j].getSquareHover() == true)
			{
				glColor3d(0.8, 0.8, 0.0);
				drawSquare();
			}

			
			float ax = i*0.16;
			float ay = -(j*0.16);

			glPushMatrix();
			glScaled(0.05, 0.05, 0.0);
			glTranslated(gridstartx + ax, gridstarty + ay, 0.0);

			//drawCirc();

			glPopMatrix();

			//This needs to be fixed to take into account the linethickness
			//between each square.
			float leftBound = ax - 0.075 + gridstartx ;
			float rightBound = ax + 0.075 + gridstartx ;

			float bottomBound = ay - 0.075 + gridstarty;
			float topBound = ay + 0.075 + gridstarty ;

			
			player1Home.board_[i][j].setBounds(topBound,bottomBound,leftBound,rightBound); 
			

			if (player1Home.board_[i][j].isHead())
			{
				glColor3d(0.4, 0.4, 0.9);
				drawSquare();
			}
			if (player1Home.board_[i][j].isOccupied() == true && player1Home.board_[i][j].isHead() == false)
			{
				glColor3d(0.3, 0.7, 0.7);
				drawSquare();
			}
			
			
			glPopMatrix();

		}
	}

	

}

//Used with the mouse function for detecting clicks on the home player board.
void p1BoardPlace()
{
	float xdist = pow(cam_mousex - finish_x, 2);
	float ydist = pow(cam_mousey - finish_y, 2);



	if (sqrt(xdist + ydist) < 0.15 && leftmousedown)
	{
		finishcol[0] = finish_clicked[0];
		finishcol[1] = finish_clicked[1];
		finishcol[2] = finish_clicked[2];
	}



	//this loop set involves the placement of the head of the ship on the board,
	//it sets the isClicking variable to true which tells the program that the
	//next loop set will be used for determining the orientation of the ship.
	for (int i = 0; i < player1Home.getSize(); i++)
	{
		for (int j = 0; j < player1Home.getSize(); j++)
		{

			//Placing the ships
			if (isClicking == false)
			{
				if (player1Home.board_[i][j].getSquareHover() == true)
				{
					if (player1Home.board_[i][j].isOccupied() == false)
					{


						if (isClicking == false)
						{
							player1Home.board_[i][j].setHead();
							player1Home.board_[i][j].setOccupied();
							isClicking = true;
							outeri = i;
							outerj = j;
						}

					}


				}
			}

		}
	}


	//By looking at where the mouse is relative to the previously placed head, 
	//this loop set will place the body of the ship in the correct orientation
	//using the mouse position and the current ship that was last selected for
	//the size of the body.
	if (isClicking)
	{
		tuple<float, float, float, float> cellBounds = player1Home.board_[outeri][outerj].getBounds();
		float bottomside = std::get<0>(cellBounds);
		float topside = std::get<1>(cellBounds);
		float leftside = std::get<2>(cellBounds);
		float rightside = std::get<3>(cellBounds);

		float xp = (0.16*outeri) + gridstartx;
		float yp = -(0.16*outerj) + gridstarty;

		float lxwall = xp - (abs(xp - leftside) / 2);
		float rxwall = xp + (abs(xp - rightside) / 2);

		float topywall = yp + (abs(yp - topside) / 2);
		float botywall = yp - (abs(yp - bottomside) / 2);



		//facing up
		if (cam_mousex >= xp - 0.1
			&& cam_mousex <= xp + 0.1
			&& cam_mousey >= yp + 0.1)
		{

			switch (curr_ship)
			{
			case 0: //ship size = 5
				if (outerj > 3)
				{
					if (player1Home.board_[outeri][outerj - 1].isOccupied() == false
						&& player1Home.board_[outeri][outerj - 2].isOccupied() == false
						&& player1Home.board_[outeri][outerj - 3].isOccupied() == false
						&& player1Home.board_[outeri][outerj - 4].isOccupied() == false)
					{
						player1Home.board_[outeri][outerj - 1].setOccupied();
						player1Home.board_[outeri][outerj - 2].setOccupied();
						player1Home.board_[outeri][outerj - 3].setOccupied();
						player1Home.board_[outeri][outerj - 4].setOccupied();
						isClicking = false;
						box_used[0] = true;
						curr_ship = -1;
						return;
					}
				}
				break;
			case 1: //ship size = 4
				if (outerj > 2)
				{
					if (player1Home.board_[outeri][outerj - 1].isOccupied() == false
						&& player1Home.board_[outeri][outerj - 2].isOccupied() == false
						&& player1Home.board_[outeri][outerj - 3].isOccupied() == false)
					{
						player1Home.board_[outeri][outerj - 1].setOccupied();
						player1Home.board_[outeri][outerj - 2].setOccupied();
						player1Home.board_[outeri][outerj - 3].setOccupied();
						isClicking = false;
						box_used[1] = true;
						curr_ship = -1;
						return;
					}
				}
				break;
			case 2: //ship size = 3
				if (outerj > 1)
				{
					if (player1Home.board_[outeri][outerj - 1].isOccupied() == false
						&& player1Home.board_[outeri][outerj - 2].isOccupied() == false)
					{
						player1Home.board_[outeri][outerj - 1].setOccupied();
						player1Home.board_[outeri][outerj - 2].setOccupied();
						isClicking = false;
						box_used[2] = true;
						curr_ship = -1;
						return;
					}
				}
				break;
			case 3: //ship size = 3
				if (outerj > 1)
				{
					if (player1Home.board_[outeri][outerj - 1].isOccupied() == false
						&& player1Home.board_[outeri][outerj - 2].isOccupied() == false)
					{
						player1Home.board_[outeri][outerj - 1].setOccupied();
						player1Home.board_[outeri][outerj - 2].setOccupied();
						isClicking = false;
						box_used[3] = true;
						curr_ship = -1;
						return;
					}
				}
				break;
			case 4: //ship size = 2
				if (outerj > 0)
				{
					if (player1Home.board_[outeri][outerj - 1].isOccupied() == false)
					{
						player1Home.board_[outeri][outerj - 1].setOccupied();
						isClicking = false;
						box_used[4] = true;
						curr_ship = -1;
						return;
					}
				}
				break;
			}



		}


		//facing down
		if (cam_mousex >= xp - 0.1
			&& cam_mousex <= xp + 0.1
			&& cam_mousey <= yp - 0.1)
		{

			switch (curr_ship)
			{
			case 0: //ship size = 5
				if (outerj < 6)
				{
					if (player1Home.board_[outeri][outerj + 1].isOccupied() == false
						&& player1Home.board_[outeri][outerj + 2].isOccupied() == false
						&& player1Home.board_[outeri][outerj + 3].isOccupied() == false
						&& player1Home.board_[outeri][outerj + 4].isOccupied() == false)
					{
						player1Home.board_[outeri][outerj + 1].setOccupied();
						player1Home.board_[outeri][outerj + 2].setOccupied();
						player1Home.board_[outeri][outerj + 3].setOccupied();
						player1Home.board_[outeri][outerj + 4].setOccupied();
						isClicking = false;
						box_used[0] = true;
						curr_ship = -1;
						return;
					}
				}
				break;
			case 1: //ship size = 4
				if (outerj < 7)
				{
					if (player1Home.board_[outeri][outerj + 1].isOccupied() == false
						&& player1Home.board_[outeri][outerj + 2].isOccupied() == false
						&& player1Home.board_[outeri][outerj + 3].isOccupied() == false)
					{
						player1Home.board_[outeri][outerj + 1].setOccupied();
						player1Home.board_[outeri][outerj + 2].setOccupied();
						player1Home.board_[outeri][outerj + 3].setOccupied();
						isClicking = false;
						box_used[1] = true;
						curr_ship = -1;
						return;
					}
				}
				break;
			case 2: //ship size = 3
				if (outerj < 8)
				{
					if (player1Home.board_[outeri][outerj + 1].isOccupied() == false
						&& player1Home.board_[outeri][outerj + 2].isOccupied() == false)
					{
						player1Home.board_[outeri][outerj + 1].setOccupied();
						player1Home.board_[outeri][outerj + 2].setOccupied();
						isClicking = false;
						box_used[2] = true;
						curr_ship = -1;
						return;
					}
				}
				break;
			case 3: //ship size = 3
				if (outerj < 8)
				{
					if (player1Home.board_[outeri][outerj + 1].isOccupied() == false
						&& player1Home.board_[outeri][outerj + 2].isOccupied() == false)
					{
						player1Home.board_[outeri][outerj + 1].setOccupied();
						player1Home.board_[outeri][outerj + 2].setOccupied();
						isClicking = false;
						box_used[3] = true;
						curr_ship = -1;
						return;
					}
				}
				break;
			case 4: //ship size = 2
				if (outerj < 9)
				{
					if (player1Home.board_[outeri][outerj + 1].isOccupied() == false)
					{
						player1Home.board_[outeri][outerj + 1].setOccupied();
						isClicking = false;
						box_used[4] = true;
						curr_ship = -1;
						return;
					}
				}
				break;
			}


		}

		//facing left
		if (cam_mousey >= yp - 0.1
			&& cam_mousey <= yp + 0.1
			&& cam_mousex <= xp - 0.1)
		{

			switch (curr_ship)
			{
			case 0: //ship size = 5
				if (outeri > 3)
				{
					if (player1Home.board_[outeri - 1][outerj].isOccupied() == false
						&& player1Home.board_[outeri - 2][outerj].isOccupied() == false
						&& player1Home.board_[outeri - 3][outerj].isOccupied() == false
						&& player1Home.board_[outeri - 4][outerj].isOccupied() == false)
					{
						player1Home.board_[outeri - 1][outerj].setOccupied();
						player1Home.board_[outeri - 2][outerj].setOccupied();
						player1Home.board_[outeri - 3][outerj].setOccupied();
						player1Home.board_[outeri - 4][outerj].setOccupied();
						isClicking = false;
						box_used[0] = true;
						curr_ship = -1;
						return;
					}
				}
				break;
			case 1: //ship size = 4
				if (outeri > 2)
				{
					if (player1Home.board_[outeri - 1][outerj].isOccupied() == false
						&& player1Home.board_[outeri - 2][outerj].isOccupied() == false
						&& player1Home.board_[outeri - 3][outerj].isOccupied() == false)
					{
						player1Home.board_[outeri - 1][outerj].setOccupied();
						player1Home.board_[outeri - 2][outerj].setOccupied();
						player1Home.board_[outeri - 3][outerj].setOccupied();
						isClicking = false;
						box_used[1] = true;
						curr_ship = -1;
						return;
					}
				}
				break;
			case 2: //ship size = 3
				if (outeri > 1)
				{
					if (player1Home.board_[outeri - 1][outerj].isOccupied() == false
						&& player1Home.board_[outeri - 2][outerj].isOccupied() == false)
					{
						player1Home.board_[outeri - 1][outerj].setOccupied();
						player1Home.board_[outeri - 2][outerj].setOccupied();
						isClicking = false;
						box_used[2] = true;
						curr_ship = -1;
						return;
					}
				}
				break;
			case 3: //ship size = 3
				if (outeri > 1)
				{
					if (player1Home.board_[outeri - 1][outerj].isOccupied() == false
						&& player1Home.board_[outeri - 2][outerj].isOccupied() == false)
					{
						player1Home.board_[outeri - 1][outerj].setOccupied();
						player1Home.board_[outeri - 2][outerj].setOccupied();
						isClicking = false;
						box_used[3] = true;
						curr_ship = -1;
						return;
					}
				}
				break;
			case 4: //ship size = 2
				if (outeri > 0)
				{
					if (player1Home.board_[outeri - 1][outerj].isOccupied() == false)
					{
						player1Home.board_[outeri - 1][outerj].setOccupied();
						isClicking = false;
						box_used[4] = true;
						curr_ship = -1;
						return;
					}
				}
				break;
			}


		}

		//facing right
		if (cam_mousey >= yp - 0.1
			&& cam_mousey <= yp + 0.1
			&& cam_mousex >= xp + 0.1)
		{

			switch (curr_ship)
			{
			case 0: //ship size = 5
				if (outeri < 6)
				{
					if (player1Home.board_[outeri + 1][outerj].isOccupied() == false
						&& player1Home.board_[outeri + 2][outerj].isOccupied() == false
						&& player1Home.board_[outeri + 3][outerj].isOccupied() == false
						&& player1Home.board_[outeri + 4][outerj].isOccupied() == false)
					{
						player1Home.board_[outeri + 1][outerj].setOccupied();
						player1Home.board_[outeri + 2][outerj].setOccupied();
						player1Home.board_[outeri + 3][outerj].setOccupied();
						player1Home.board_[outeri + 4][outerj].setOccupied();
						isClicking = false;
						box_used[0] = true;
						curr_ship = -1;
						return;
					}
				}
				break;
			case 1: //ship size = 4
				if (outeri < 7)
				{
					if (player1Home.board_[outeri + 1][outerj].isOccupied() == false
						&& player1Home.board_[outeri + 2][outerj].isOccupied() == false
						&& player1Home.board_[outeri + 3][outerj].isOccupied() == false)
					{
						player1Home.board_[outeri + 1][outerj].setOccupied();
						player1Home.board_[outeri + 2][outerj].setOccupied();
						player1Home.board_[outeri + 3][outerj].setOccupied();
						isClicking = false;
						box_used[1] = true;
						curr_ship = -1;
						return;
					}
				}
				break;
			case 2: //ship size = 3
				if (outeri < 8)
				{
					if (player1Home.board_[outeri + 1][outerj].isOccupied() == false
						&& player1Home.board_[outeri + 2][outerj].isOccupied() == false)
					{
						player1Home.board_[outeri + 1][outerj].setOccupied();
						player1Home.board_[outeri + 2][outerj].setOccupied();
						isClicking = false;
						box_used[2] = true;
						curr_ship = -1;
						return;
					}
				}
				break;
			case 3: //ship size = 3
				if (outeri < 8)
				{
					if (player1Home.board_[outeri + 1][outerj].isOccupied() == false
						&& player1Home.board_[outeri + 2][outerj].isOccupied() == false)
					{
						player1Home.board_[outeri + 1][outerj].setOccupied();
						player1Home.board_[outeri + 2][outerj].setOccupied();
						isClicking = false;
						box_used[3] = true;
						curr_ship = -1;
						return;
					}
				}
				break;
			case 4: //ship size = 2
				if (outeri < 9)
				{
					if (player1Home.board_[outeri + 1][outerj].isOccupied() == false)
					{
						player1Home.board_[outeri + 1][outerj].setOccupied();
						isClicking = false;
						box_used[4] = true;
						curr_ship = -1;
						return;
					}
				}
				break;
			}


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
	BitmapPrinter p(0.0, 0.0, 0.1);

	glLoadIdentity();

	

	glColor3d(0.4, 0.4, 0.4);

	//player1Home Grid
	glPushMatrix();
	glTranslated(gridstartx,gridstarty,0.0);
	glScaled(0.8, 0.8, 0.0); //0.75 used for screen scale
	drawHome1();
	glPopMatrix();


	//ship buttons
	glPushMatrix();
	glTranslated(-1.0, -0.15, 0.0);
	for (int i = 0; i < 5; i++)
	{
		glTranslated(0.0, -0.125, 0.0);
		glColor3d(boxcol[i][0], boxcol[i][1], boxcol[i][2]);
		if (box_used[i] == false)
		{
			boxButton();
		}
	
	}
	glPopMatrix();

	//adds words to the box buttons
	boxWords();



	//'Finished' Button
	glPushMatrix();
	glColor3d(finishcol[0],finishcol[1],finishcol[2]);
	glTranslated(finish_x, finish_y, 0.0);
	glScaled(0.15, 0.15, 0.0);
	drawCirc();

	glColor3d(0., 0., 0.); // Black text
	glTranslated(finish_x + 0.25, finish_y - 0.35, 0.0); // x + 0.45, y - 0.1

	glScaled(0.75, 0.75, 0.0); //used for 800x600 aspect ratio 

	p.print("Finished!");
	glPopMatrix();


	//Instruction Text
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();

	glColor3d(0., 0., 0.);        // Black text
	glTranslated(-1.25, 0.975, 0.0); //modify to change text position

	glScaled(0.5, 0.45, 0.0); //used for 800x600 aspect ratio.

	
	if (showdisplay == true)
	{
		p.print("Welcome to Battleship");
		p.print("Please use the mouse to place ships");
		p.print("on the board by clicking a grid square,");
		p.print("then choosing a direction. Click the");
		p.print("'finished' button when you are done to ");
		p.print("pass it to the next player.");
		p.print("");
		//p.print("");
		switch (curr_ship)
		{
		case 0:
			p.print("Ship Selected: Airship Carrier");
			break;
		case 1:
			p.print("Ship Selected: Battleship");
			break;
		case 2:
			p.print("Ship Selected: Submarine");
			break;
		case 3:
			p.print("Ship Selected: Destroyer");
			break;
		case 4:
			p.print("Ship Selected: Patrol Boat");
			break;
		}



		p.print("");
		

		p.print("mx: " + std::to_string(cam_mousex));
		p.print("my: " + std::to_string(cam_mousey));



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
	glViewport(0, 0, startwinwd, startwinht);
	winw = startwinwd;
	winh = startwinht;
	
	float aspect = startwinwd / startwinht;



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


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(cam_xmin, cam_xmax, cam_ymin, cam_ymax);

	glMatrixMode(GL_MODELVIEW);  // Always go back to model/view mode

	if (w != startwinwd || h != startwinht)
	{
		glutReshapeWindow(1024, 768);
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
	BitmapPrinter p(0.0, 0.0, 0.1);


	if (button == GLUT_LEFT_BUTTON)
	{
		leftmousedown = (state == GLUT_DOWN);

		p1BoardPlace();
		boxButtonClick();

	}

	if (button == GLUT_RIGHT_BUTTON)
	{
		rightmousedown = (state == GLUT_DOWN);
		
		if (isClicking)
		{
			isClicking = false;
			player1Home.board_[outeri][outerj].removeHead();

		}


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



glutPostRedisplay();
}

// myPassiveMotion
// The GLUT passiveMotion function
void myPassiveMotion(int x, int y)
{
	// Save old mouse pos, for relative mouse-movement computation
	double old_cam_mousex = cam_mousex;
	double old_cam_mousey = cam_mousey;

	saveMouse(x, y);


	float xdist = pow(cam_mousex - finish_x, 2);
	float ydist = pow(cam_mousey - finish_y, 2);

	if (sqrt(xdist + ydist) < 0.15 && !leftmousedown)
	{
		finishcol[0] = finish_hover[0];
		finishcol[1] = finish_hover[1];
		finishcol[2] = finish_hover[2];
	}
	else
	{
		finishcol[0] = finish_base[0];
		finishcol[1] = finish_base[1];
		finishcol[2] = finish_base[2];
	}



	for (int i = 0; i < player1Home.getSize(); i++)
	{
		for (int j = 0; j < player1Home.getSize(); j++)
		{
			tuple<float, float, float, float> cellBounds = player1Home.board_[i][j].getBounds();
			if (cam_mousex >= std::get<2>(cellBounds)
				&& cam_mousex <= std::get<3>(cellBounds)
				&& cam_mousey >= std::get<0>(cellBounds)
				&& cam_mousey <= std::get<1>(cellBounds))
			{
				player1Home.board_[i][j].setSquareHover(true);

			}
			else
			{
				player1Home.board_[i][j].setSquareHover(false);
			}
		}
	}



	boxButtonHover();


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

	//sets colors for the array of box buttons
	for (int i = 0; i < 5; i++)
	{
		boxcol[i][0] = 0.3;
		boxcol[i][1] = 0.5;
		boxcol[i][2] = 0.7;

		box_used[i] = false;
	}

	//sets the sizes of the respective ships.
	boxcol[0][3] = 5;
	boxcol[1][3] = 4;
	boxcol[2][3] = 3;
	boxcol[3][3] = 3;
	boxcol[4][3] = 2;



	// OpenGL Stuff
	glLineWidth(5.0);
	showdisplay = true;
}





#endif