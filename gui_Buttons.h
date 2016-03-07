
#ifndef GUI_BUTTONS_H_INCLUDED
#define GUI_BUTTONS_H_INCLUDED

#include "gui_Globals.h"

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

//finishClick()
//detects whether the player has clicked on the finish button
void finishClick()
{
	float xdist = pow(cam_mousex - finish_x, 2);
	float ydist = pow(cam_mousey - finish_y, 2);



	if (sqrt(xdist + ydist) < 0.15 && leftmousedown)
	{
		finishcol[0] = finish_clicked[0];
		finishcol[1] = finish_clicked[1];
		finishcol[2] = finish_clicked[2];

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
void boxButton()
{
	glPushMatrix();
	glScaled(0.25, 0.05, 0.0);
	drawSquare();
	glPopMatrix();

}

//boxButtonHover()
//highlights the ship boxes if the mouse is over them
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
//
void boxWords()
{
	glColor3d(0.0, 0.0, 0.0);

	//need to figure out how to roll these into 1 declaration
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