/*
Tristan Craddick and Arsh Chauhan
Button Gui  Header
02/19/16
Last Updated: 03/10/16
For CS 372 Battleship Game
*/

#ifndef GUI_BUTTONS_H_INCLUDED
#define GUI_BUTTONS_H_INCLUDED

#include "gui_Globals.h"

// drawCircle
// Draws a filled Circle
/*
Pre: None
Post: draws a Circle with no other paramaters
*/
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





//finishClick()
//detects whether the player has clicked on the finish button
/*
Pre: none
Post: Detects whether mouse is within bounds of the circle button.
	if it is, then it checks for a player victory. If no player has
	won, then it resets the appropriate variables for switching turns,
	switches the turn, and switches display to the pause screen.
*/
void finishClick()
{
	float xdist = pow(cam_mousex - finish_x, 2);
	float ydist = pow(cam_mousey - finish_y, 2);



	if (sqrt(xdist + ydist) < 0.15 && leftmousedown)
	{
		finishcol[0] = finish_clicked[0];
		finishcol[1] = finish_clicked[1];
		finishcol[2] = finish_clicked[2];

		if (game_start == true)
		{
			winCheck();
		}
		else
		{
			game_pause = true;
			glutDisplayFunc(pauseScreen);
		}
		//winCheck(); //use to test winning redisplay

		for (int i = 0; i < 5; i++)
		{
			box_used[i] = false;

		}

		if (p1turn == true)
		{
			p1turn = false;
			p2turn = true;
		}
		else
		{
			p1turn = true;
			p2turn = false;
		}
		turn_count++;
		ships_placed = 0;
		has_fired = false;
	}
}

//boxButton()
//Draws a box for the ship buttons
/*
Pre: None
Post: Draws a scaled box for use as a button
*/
void boxButton()
{
	glPushMatrix();
	glScaled(0.25, 0.05, 0.0);
	drawSquare();
	glPopMatrix();

}

//boxButtonHover()
//highlights the ship boxes if the mouse is over them
/*
Pre: None
Post: If the mouse is within the bounds of the box, highlights
	the box. Resets the color if the mouse is not over it.
*/
void boxButtonHover()
{
	for (int i = 0; i < 5; i++)
	{
		if (cam_mousex <= -0.75
			&& cam_mousex >= -1.25
			&& cam_mousey <= (-0.28 + (-0.125 * i) + 0.05)
			&& cam_mousey >= (-0.28 + (-0.125 * i) - 0.05))
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

//boxButtonClick()
//darkens the boxes if they are clicked and sets the selected ship
//based off of which one was clicked.
/*
Pre: None
Post: Detects based off of the current mouse position whether the
	mouse has clicked within the bounds of the box. If it has, then
	it darkens the color of the box and sets the current ship
	variable based upon which button was selected.
*/
void boxButtonClick()
{
	for (int i = 0; i < 5; i++)
	{
		if (cam_mousex <= -0.75
			&& cam_mousex >= -1.25
			&& cam_mousey <= (-0.28 + (-0.125 * i) + 0.05)
			&& cam_mousey >= (-0.28 + (-0.125 * i) - 0.05))
		{
			if (box_used[i] == false)
			{
				boxcol[i][0] = box_clicked[0];
				boxcol[i][1] = box_clicked[1];
				boxcol[i][2] = box_clicked[2];
				curr_ship = i;
			}
		}
	}
}



//boxWords()
/*
Pre: None
Post: Displays the text for each of the five ship
	based buttons.
*/
void boxWords()
{
	glColor3d(0.0, 0.0, 0.0);

	BitmapPrinter button1(0.0, 0.0, 0.1);
	BitmapPrinter button2(0.0, 0.0, 0.1);
	BitmapPrinter button3(0.0, 0.0, 0.1);
	BitmapPrinter button4(0.0, 0.0, 0.1);
	BitmapPrinter button5(0.0, 0.0, 0.1);


	glPushMatrix();
	glTranslated(-1.24, -0.3, 0.0);
	if (box_used[0] == false)
	{
		button1.print("Aircraft Carrier");
	}
	glPopMatrix();

	glPushMatrix();
	glTranslated(-1.24, -0.41, 0.0);
	if (box_used[1] == false)
	{
		button2.print("Battleship");
	}
	glPopMatrix();



	glPushMatrix();
	glTranslated(-1.24, -0.54, 0.0);
	if (box_used[2] == false)
	{
		button3.print("Submarine");
	}
	glPopMatrix();

	glPushMatrix();
	glTranslated(-1.24, -0.665, 0.0);
	if (box_used[3] == false)
	{
		button4.print("Destroyer");
	}
	glPopMatrix();

	glPushMatrix();
	glTranslated(-1.24, -0.79, 0.0);
	if (box_used[4] == false)
	{
		button5.print("Patrol Boat");
	}
	glPopMatrix();


}




#endif