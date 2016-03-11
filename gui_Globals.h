/*
Tristan Craddick and Arsh Chauhan
Gui Header for Globals
02/19/16
Last Updated: 03/10/16
For CS 372 Battleship Game
*/

#ifndef GUI_GLOBALS_H_INCLUDED
#define GUI_GLOBALS_H_INCLUDED

#include <string.h>
using std::string;

//-------------Initial Gui set-up variable for test case----------

//File is include properly
bool gui_Include = true;

// Variables are initiated properly (Init function called)
bool gui_Init = false;

// Variable displayed if the large board is properly displayed 
bool gui_L_Board = false;

//variable for if the small board is properly displayed
bool gui_S_Board = false;

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


//*************Battleship Grids************

Board player1Home(10, true);
Board player1Target(10, false);
Board player2Home(10, true);
Board player2Target(10, false);

float l_gridstart_x = -0.225;
float l_gridstart_y = 0.60;

float s_gridstart_x = -1.2;
float s_gridstart_y = 0.05;


//-----------Misc Variables---------------

double savetime;    // Time of previous movement (sec)

bool game_start;

int turn_count; // A variable that is incremented each time a player ends their turn

int ships_placed; //number of ships a player has placed in their initial turn.
bool has_fired; //if the player has fired in their turn or not.


bool p1turn = true;
bool p2turn = false;

string winner;

bool showdisplay = true; //shows the text display
bool finbuttonhover = false; //if mouse is over the finished button

//variables for the 'finished' button
float finish_x = -1.;
float finish_y = 0.3;


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

bool game_pause;

double cam_mousex, cam_mousey; // Mouse pos in cam coords

bool isClicking = false;
int outeri = 0;
int outerj = 0;


//----------------Function Prototypes-------------------
//Display Screens
void myDisplay();
void winDisplay();
void pauseScreen();

//Core OpenGl/Glut Functions
void myIdle();
void myReshape(int w, int h);
void myKeyboard(unsigned char key, int x, int y);
void saveMouse(int x, int y);
void myMouse(int button, int state, int x, int y);
void myMotion(int x, int y);
void myPassiveMotion(int x, int y);
void init();
void winCheck();

//Board-based functions
void drawSquare();
void drawEmpSquare();
void shipCheck(Board& player, int ID);
void drawLargeGrid(Board& player);
void drawSmallBoard(Board& player);
void boardPlace(Board& player);
void boardHover(Board& player);
void boardFire(Board& player, Board& opponent);
void sunkCheck(Board& player, Board& opponent);

//Button-based functions
void drawCirc();
void finishClick();
void boxButton();
void boxButtonHover();
void boxButtonClick();
void boxWords();




#endif