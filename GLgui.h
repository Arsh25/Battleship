/*
Tristan Craddick
Core Gui  Header

For CS 372 Battleship Game
*/


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

#include "gui_Board.h"
#include "gui_Globals.h"
#include "gui_Buttons.h"


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



//****************Display, Idle, Reshape Functions*****************

/*myDisplay
  The glut display function
Pre: None
Post: draws the information text for the player, the player's board
	on the right, and if both players still needs to place ships, 
	then ship buttons in the bottom left for which ship to place. If
	the ships have all been placed, then displays the player's board
	in the bottom left and their targeting board on the right.
*/
void myDisplay()
{
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	BitmapPrinter text(0.0, 0.0, 0.1);
	BitmapPrinter player(0.0, 0.0, 0.1);
	BitmapPrinter button(0.0, 0.0, 0.1);

	glLoadIdentity();
	glColor3d(0.4, 0.4, 0.4); //color for the cell borders



	if (game_start == false)
	{
		//Large grid on the right
		if (p1turn == true)
		{
			glPushMatrix();
			glTranslated(l_gridstart_x, l_gridstart_y, 0.0);
			glScaled(0.8, 0.8, 0.0);
			drawLargeGrid(player1Home);
			glPopMatrix();
		}
		else
		{
			glPushMatrix();
			glTranslated(l_gridstart_x, l_gridstart_y, 0.0);
			glScaled(0.8, 0.8, 0.0);
			drawLargeGrid(player2Home);
			glPopMatrix();
		}

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
		glPushMatrix();
		boxWords();
		glPopMatrix();
	}
	else //game_start == true, so secondary board is displayed.
	{
		//Large grid on the right
		if (p1turn == true)
		{
			glPushMatrix();
			glTranslated(l_gridstart_x, l_gridstart_y, 0.0);
			glScaled(0.8, 0.8, 0.0);
			drawLargeGrid(player1Target);
			glPopMatrix();
		}
		else
		{
			glPushMatrix();
			glTranslated(l_gridstart_x, l_gridstart_y, 0.0);
			glScaled(0.8, 0.8, 0.0);
			drawLargeGrid(player2Target);
			glPopMatrix();
		}


		if (p1turn == true)
		{
			glPushMatrix();
			glTranslated(s_gridstart_x, s_gridstart_y, 0.0);
			glScaled(0.8, 0.8, 0.0);
			drawSmallBoard(player1Home);
			glPopMatrix();
		}
		else
		{
			glPushMatrix();
			glTranslated(s_gridstart_x, s_gridstart_y, 0.0);
			glScaled(0.8, 0.8, 0.0);
			drawSmallBoard(player2Home);

			glPopMatrix();
		}
	}





	//'Finished' Button
	//all ships have been placed for a player or the player has fired
	if (ships_placed == 5 || has_fired == true) 
	{
		glPushMatrix();
		glColor3d(finishcol[0], finishcol[1], finishcol[2]);
		glTranslated(finish_x, finish_y, 0.0);
		glScaled(0.15, 0.15, 0.0);
		drawCirc();

		glColor3d(0., 0., 0.); // Black text
		glTranslated(finish_x + 0.25, finish_y - 0.35, 0.0); // x + 0.45, y - 0.1

		glScaled(0.75, 0.75, 0.0); //used for 800x600 aspect ratio 

		button.print("Finished!");
		glPopMatrix();
	}


	



	//Instruction Text
	glPushMatrix();
	glColor3d(0., 0., 0.);        // Black text
	glTranslated(-1.25, 0.95, 0.0); //modify to change text position
	glScaled(0.5, 0.45, 0.0); //used for 800x600 aspect ratio.


	if (game_start == false)
	{
		text.print("Welcome to Battleship");
		text.print("Please use the mouse to place ships");
		text.print("on the board by clicking a grid square,");
		text.print("then choosing a direction by clicking");
		text.print("the next square over. Click the");
		text.print("'finished' button when you are done to ");
		text.print("pass it to the next player.");
		text.print("");

		switch (curr_ship)
		{
		case 0:
			text.print("Ship Selected: Airship Carrier");
			break;
		case 1:
			text.print("Ship Selected: Battleship");
			break;
		case 2:
			text.print("Ship Selected: Submarine");
			break;
		case 3:
			text.print("Ship Selected: Destroyer");
			break;
		case 4:
			text.print("Ship Selected: Patrol Boat");
			break;
		}
	}
	else
	{
		text.print("Click on a grid cell to fire a shot.");
		text.print("The first to sink all of the opponent's");
		text.print("ships is the winner!");
		text.print("");
		text.print("Ship Cells Remaining:");

		if (p1turn == true)
		{
			text.print("Aircraft Carrier: " + std::to_string(player1Home.ship_cells[0]));
			text.print("Battleship: " + std::to_string(player1Home.ship_cells[1]));
			text.print("Submarine: " + std::to_string(player1Home.ship_cells[2]));
			text.print("Destroyer: " + std::to_string(player1Home.ship_cells[3]));
			text.print("Patrol Boat: " + std::to_string(player1Home.ship_cells[4]));
		}
		else
		{
			text.print("Aircraft Carrier: " + std::to_string(player2Home.ship_cells[0]));
			text.print("Battleship: " + std::to_string(player2Home.ship_cells[1]));
			text.print("Submarine: " + std::to_string(player2Home.ship_cells[2]));
			text.print("Destroyer: " + std::to_string(player2Home.ship_cells[3]));
			text.print("Patrol Boat: " + std::to_string(player2Home.ship_cells[4]));
		}

	}

	glPopMatrix();                // Restore prev projection


	//Text in upper right showing whose turn it is.
	glPushMatrix();
	glColor3d(0., 0., 0.);        // Black text
	glTranslated(0.5, 0.875, 0.0); //modify to change text position
	glScaled(0.5, 0.45, 0.0); //used for 800x600 aspect ratio.

	if (p1turn == true)
	{
		player.print("It is player 1's turn");
	}
	else
	{
		player.print("It is player 2's turn");
	}


	glPopMatrix();



	glMatrixMode(GL_MODELVIEW);
	glutSwapBuffers();
}


//myIdle
//Basic glut idle function
/*
Pre: None
Post: A consistently updating function used for any variables
	that should be constantly checked or updated.
*/
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

	//Both players have placed their ships, and the actual targeting game begins.
	if (turn_count >= 2)
	{
		game_start = true;
	}
}

// myReshape
// The GLUT reshape function
/*
Pre: None
Post: Appropriately scales the drawn screen based upon the size 
	of the window whenever it is adjusted. Currently set so that
	window will always be readjusted to 800x600 ratio.
*/
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


	//if the window is resized, resets it back to the following amount.
	if (w != startwinwd || h != startwinht)
	{
		glutReshapeWindow(800, 600);
	}
	
}



//-------------Mouse and Keyboard Functions-------------

// myKeyboard
// The GLUT keyboard function
/*
Pre: None
Post: Detects keypresses and preforms operations based upon
	which key is pressed.
*/
void myKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case ESCKEY:  // Escape: quit
		exit(0);
		break;
	case ' ':
		if (game_pause == true)
		{
			game_pause = false;
			glutDisplayFunc(myDisplay);
		}
		break;

	}
	glutPostRedisplay();
}

// saveMouse
/*
Pre: None
Post:  Given mouse pos in GLUT format; computes mouse pos in cam coords,
	saves it in globals cam_mousex, cam_mousey.
	 Uses globals winw, winh, cam_xmin, cam_xmax, cam_ymin, cam_ymax.
*/

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
/*
Pre: None
Post: Updates variables when the mouse buttons are clicked.
*/
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

		if (ships_placed == 5 || has_fired == true)
		{
			finishClick();
		}


		if (game_start == false)
		{

			if (curr_ship != -1)
			{
				if (p1turn == true)
				{
					boardPlace(player1Home);
				}
				else
				{
					boardPlace(player2Home);
				}
			}


			boxButtonClick();
		}
		else //game has started, and targeting begins.
		{
			if (has_fired == false)
			{
				if (p1turn == true)
				{
					boardFire(player1Target, player2Home);
					sunkCheck(player1Target, player2Home);
				}
				else
				{
					boardFire(player2Target, player1Home);
					sunkCheck(player2Target, player1Home);
				}
			}
		}




	}

	if (button == GLUT_RIGHT_BUTTON)
	{
		rightmousedown = (state == GLUT_DOWN);
		
		if (isClicking)
		{
			isClicking = false;
			if (p1turn)
			{
				player1Home.board_[outeri][outerj].removeHead();
			}
			else
			{
				player2Home.board_[outeri][outerj].removeHead();
			}


		}


	}
	glutPostRedisplay();
}

// myMotion
// The GLUT motion function
/*
Pre: None
Post: Updates the mouse position when the mouse is moved.
*/
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
/*
Pre: None
Post: Updates variables, generally for the button detection
	when the mouse moves.
*/
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

	if (game_start == false)
	{
		if (p1turn == true)
		{
			boardHover(player1Home);
		}
		else
		{
			boardHover(player2Home);
		}
	}
	else
	{
		if (p1turn == true)
		{
			boardHover(player1Target);
		}
		else
		{
			boardHover(player2Target);
		}
	}





	boxButtonHover();


	glutPostRedisplay();
}



//----------------Initialization and Main-----------------


// init
// Initialize GL states & global data
// Called by main after window creation
/*
Pre: None
Post: Function called at the beginning of the program
	that properly sets all uninitialized variables.
*/
void init()
{
	// Objects
	savetime = glutGet(GLUT_ELAPSED_TIME) / 1000.;

	gui_Init = true;

	//mouse
	cam_mousex = 0.0;
	cam_mousey = 0.0;

	//sets colors for the array of box buttons and sets their 'used'
	//variable to false.
	for (int i = 0; i < 5; i++)
	{
		boxcol[i][0] = 0.3;
		boxcol[i][1] = 0.5;
		boxcol[i][2] = 0.7;

		box_used[i] = false;
	}

	//sets the sizes of the respective ships.
	boxcol[0][3] = 5; //Aircraft Carrier
	boxcol[1][3] = 4; //Battleship
	boxcol[2][3] = 3; //Destroyer
	boxcol[3][3] = 3; //Submarine
	boxcol[4][3] = 2; //Patrol Boat

	game_start = false;
	turn_count = 0;
	ships_placed = 0;
	has_fired = false;

	// OpenGL Stuff
	glLineWidth(5.0);
	showdisplay = true;
}

//pauseScreen
/*
Pre: None
Post: A seperately drawn screen that displays the pause
	screen with a message so that players can switch
	between boards without risk of cheating.
*/
void pauseScreen()
{
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	BitmapPrinter player(-0.5, 0.0, 0.1);

	glPushMatrix();
	player.print("Please pass to the next player");
	player.print("press space to continue");
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glutSwapBuffers();
}

/*
Pre: None
Post: The screen drawn if it is detected that a player has won.
*/
void winDisplay()
{ 
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	BitmapPrinter player(-0.2, 0.0, 0.1);

	glPushMatrix();
	player.print(winner + " wins!");
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glutSwapBuffers();
}

/*
Pre: None
Post: checks to see if a player has won based upon whose turn it was
	and whether or not all occupied cells on the opposing player's 
	board have been hit.
*/
void winCheck()
{
		if (p1turn)
		{
			if (player2Home.ship_cells[0] == 0
				&& player2Home.ship_cells[1] == 0
				&& player2Home.ship_cells[2] == 0
				&& player2Home.ship_cells[3] == 0
				&& player2Home.ship_cells[4] == 0)
			{
				winner = "Player 1";
				glutDisplayFunc(winDisplay);
			}
			else
			{
				game_pause = true;
				glutDisplayFunc(pauseScreen);
			}

		}
		else
		{
			if (player1Home.ship_cells[0] == 0
				&& player1Home.ship_cells[1] == 0
				&& player1Home.ship_cells[2] == 0
				&& player1Home.ship_cells[3] == 0
				&& player1Home.ship_cells[4] == 0)
			{
				winner = "Player 2";
				glutDisplayFunc(winDisplay);
			}
			else
			{
				game_pause = true;
				glutDisplayFunc(pauseScreen);
			}
		}

}

/*
Pre: None
Post: checks to see if ship is fully sunk
*/
void sunkCheck(Board& player,Board& opponent)
{


	for (int i = 0; i < player.getSize(); i++)
	{
		for (int j = 0; j < player.getSize(); j++)
		{
			if (opponent.ship_cells[0] == 0)
			{
				if (opponent.board_[i][j].getID() == 0)
				{
					opponent.board_[i][j].setSunk();
					player.board_[i][j].setTarSunk();
				}
			}
			if (opponent.ship_cells[1] == 0)
			{
				if (opponent.board_[i][j].getID() == 1)
				{
					opponent.board_[i][j].setSunk();
					player.board_[i][j].setTarSunk();
				}
			}
			if (opponent.ship_cells[2] == 0)
			{
				if (opponent.board_[i][j].getID() == 2)
				{
					opponent.board_[i][j].setSunk();
					player.board_[i][j].setTarSunk();
				}
			}
			if (opponent.ship_cells[3] == 0)
			{
				if (opponent.board_[i][j].getID() == 3)
				{
					opponent.board_[i][j].setSunk();
					player.board_[i][j].setTarSunk();
				}
			}
			if (opponent.ship_cells[4] == 0)
			{
				if (opponent.board_[i][j].getID() == 4)
				{
					opponent.board_[i][j].setSunk();
					player.board_[i][j].setTarSunk();
				}
			}


		}
	}
}



#endif