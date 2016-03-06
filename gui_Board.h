
#ifndef GUI_BOARD_H_INCLUDED
#define GUI_BOARD_H_INCLUDED

#include "gui_Globals.h"

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

//p1BoardHover
//Detects whether the mouse is over p1's board.
void p1BoardHover()
{
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
}


//drawHome1
//draws the home grid for player 1 
void drawHome2()
{
	for (int i = 0; i < player2Home.getSize(); i++)
	{
		for (int j = 0; j < player2Home.getSize(); j++)
		{
			glColor3d(0.4, 0.4, 0.4);
			float x = (0.2*i);
			float y = -(0.2*j);

			glPushMatrix();
			glColor3d(0.4, 0.4, 0.4);
			glTranslated(x, y, 0.0);
			glScaled(0.1, 0.1, 0.0);
			drawEmpSquare();

			if (player2Home.board_[i][j].getSquareHover() == true)
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
			float leftBound = ax - 0.075 + gridstartx;
			float rightBound = ax + 0.075 + gridstartx;

			float bottomBound = ay - 0.075 + gridstarty;
			float topBound = ay + 0.075 + gridstarty;


			player2Home.board_[i][j].setBounds(topBound, bottomBound, leftBound, rightBound);


			if (player2Home.board_[i][j].isHead())
			{
				glColor3d(0.4, 0.4, 0.9);
				drawSquare();
			}
			if (player2Home.board_[i][j].isOccupied() == true && player2Home.board_[i][j].isHead() == false)
			{
				glColor3d(0.3, 0.7, 0.7);
				drawSquare();
			}


			glPopMatrix();

		}
	}



}


//Used with the mouse function for detecting clicks on the home player board.
void p2BoardPlace()
{
	//this loop set involves the placement of the head of the ship on the board,
	//it sets the isClicking variable to true which tells the program that the
	//next loop set will be used for determining the orientation of the ship.
	for (int i = 0; i < player2Home.getSize(); i++)
	{
		for (int j = 0; j < player2Home.getSize(); j++)
		{

			//Placing the ships
			if (isClicking == false)
			{
				if (player2Home.board_[i][j].getSquareHover() == true)
				{
					if (player2Home.board_[i][j].isOccupied() == false)
					{


						if (isClicking == false)
						{
							player2Home.board_[i][j].setHead();
							player2Home.board_[i][j].setOccupied();
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
		tuple<float, float, float, float> cellBounds = player2Home.board_[outeri][outerj].getBounds();
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
					if (player2Home.board_[outeri][outerj - 1].isOccupied() == false
						&& player2Home.board_[outeri][outerj - 2].isOccupied() == false
						&& player2Home.board_[outeri][outerj - 3].isOccupied() == false
						&& player2Home.board_[outeri][outerj - 4].isOccupied() == false)
					{
						player2Home.board_[outeri][outerj - 1].setOccupied();
						player2Home.board_[outeri][outerj - 2].setOccupied();
						player2Home.board_[outeri][outerj - 3].setOccupied();
						player2Home.board_[outeri][outerj - 4].setOccupied();
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
					if (player2Home.board_[outeri][outerj - 1].isOccupied() == false
						&& player2Home.board_[outeri][outerj - 2].isOccupied() == false
						&& player2Home.board_[outeri][outerj - 3].isOccupied() == false)
					{
						player2Home.board_[outeri][outerj - 1].setOccupied();
						player2Home.board_[outeri][outerj - 2].setOccupied();
						player2Home.board_[outeri][outerj - 3].setOccupied();
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
					if (player2Home.board_[outeri][outerj - 1].isOccupied() == false
						&& player2Home.board_[outeri][outerj - 2].isOccupied() == false)
					{
						player2Home.board_[outeri][outerj - 1].setOccupied();
						player2Home.board_[outeri][outerj - 2].setOccupied();
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
					if (player2Home.board_[outeri][outerj - 1].isOccupied() == false
						&& player2Home.board_[outeri][outerj - 2].isOccupied() == false)
					{
						player2Home.board_[outeri][outerj - 1].setOccupied();
						player2Home.board_[outeri][outerj - 2].setOccupied();
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
					if (player2Home.board_[outeri][outerj - 1].isOccupied() == false)
					{
						player2Home.board_[outeri][outerj - 1].setOccupied();
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
					if (player2Home.board_[outeri][outerj + 1].isOccupied() == false
						&& player2Home.board_[outeri][outerj + 2].isOccupied() == false
						&& player2Home.board_[outeri][outerj + 3].isOccupied() == false
						&& player2Home.board_[outeri][outerj + 4].isOccupied() == false)
					{
						player2Home.board_[outeri][outerj + 1].setOccupied();
						player2Home.board_[outeri][outerj + 2].setOccupied();
						player2Home.board_[outeri][outerj + 3].setOccupied();
						player2Home.board_[outeri][outerj + 4].setOccupied();
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
					if (player2Home.board_[outeri][outerj + 1].isOccupied() == false
						&& player2Home.board_[outeri][outerj + 2].isOccupied() == false
						&& player2Home.board_[outeri][outerj + 3].isOccupied() == false)
					{
						player2Home.board_[outeri][outerj + 1].setOccupied();
						player2Home.board_[outeri][outerj + 2].setOccupied();
						player2Home.board_[outeri][outerj + 3].setOccupied();
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
					if (player2Home.board_[outeri][outerj + 1].isOccupied() == false
						&& player2Home.board_[outeri][outerj + 2].isOccupied() == false)
					{
						player2Home.board_[outeri][outerj + 1].setOccupied();
						player2Home.board_[outeri][outerj + 2].setOccupied();
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
					if (player2Home.board_[outeri][outerj + 1].isOccupied() == false
						&& player2Home.board_[outeri][outerj + 2].isOccupied() == false)
					{
						player2Home.board_[outeri][outerj + 1].setOccupied();
						player2Home.board_[outeri][outerj + 2].setOccupied();
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
					if (player2Home.board_[outeri][outerj + 1].isOccupied() == false)
					{
						player2Home.board_[outeri][outerj + 1].setOccupied();
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
					if (player2Home.board_[outeri - 1][outerj].isOccupied() == false
						&& player2Home.board_[outeri - 2][outerj].isOccupied() == false
						&& player2Home.board_[outeri - 3][outerj].isOccupied() == false
						&& player2Home.board_[outeri - 4][outerj].isOccupied() == false)
					{
						player2Home.board_[outeri - 1][outerj].setOccupied();
						player2Home.board_[outeri - 2][outerj].setOccupied();
						player2Home.board_[outeri - 3][outerj].setOccupied();
						player2Home.board_[outeri - 4][outerj].setOccupied();
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
					if (player2Home.board_[outeri - 1][outerj].isOccupied() == false
						&& player2Home.board_[outeri - 2][outerj].isOccupied() == false
						&& player2Home.board_[outeri - 3][outerj].isOccupied() == false)
					{
						player2Home.board_[outeri - 1][outerj].setOccupied();
						player2Home.board_[outeri - 2][outerj].setOccupied();
						player2Home.board_[outeri - 3][outerj].setOccupied();
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
					if (player2Home.board_[outeri - 1][outerj].isOccupied() == false
						&& player2Home.board_[outeri - 2][outerj].isOccupied() == false)
					{
						player2Home.board_[outeri - 1][outerj].setOccupied();
						player2Home.board_[outeri - 2][outerj].setOccupied();
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
					if (player2Home.board_[outeri - 1][outerj].isOccupied() == false
						&& player2Home.board_[outeri - 2][outerj].isOccupied() == false)
					{
						player2Home.board_[outeri - 1][outerj].setOccupied();
						player2Home.board_[outeri - 2][outerj].setOccupied();
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
					if (player2Home.board_[outeri - 1][outerj].isOccupied() == false)
					{
						player2Home.board_[outeri - 1][outerj].setOccupied();
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
					if (player2Home.board_[outeri + 1][outerj].isOccupied() == false
						&& player2Home.board_[outeri + 2][outerj].isOccupied() == false
						&& player2Home.board_[outeri + 3][outerj].isOccupied() == false
						&& player2Home.board_[outeri + 4][outerj].isOccupied() == false)
					{
						player2Home.board_[outeri + 1][outerj].setOccupied();
						player2Home.board_[outeri + 2][outerj].setOccupied();
						player2Home.board_[outeri + 3][outerj].setOccupied();
						player2Home.board_[outeri + 4][outerj].setOccupied();
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
					if (player2Home.board_[outeri + 1][outerj].isOccupied() == false
						&& player2Home.board_[outeri + 2][outerj].isOccupied() == false
						&& player2Home.board_[outeri + 3][outerj].isOccupied() == false)
					{
						player2Home.board_[outeri + 1][outerj].setOccupied();
						player2Home.board_[outeri + 2][outerj].setOccupied();
						player2Home.board_[outeri + 3][outerj].setOccupied();
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
					if (player2Home.board_[outeri + 1][outerj].isOccupied() == false
						&& player2Home.board_[outeri + 2][outerj].isOccupied() == false)
					{
						player2Home.board_[outeri + 1][outerj].setOccupied();
						player2Home.board_[outeri + 2][outerj].setOccupied();
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
					if (player2Home.board_[outeri + 1][outerj].isOccupied() == false
						&& player2Home.board_[outeri + 2][outerj].isOccupied() == false)
					{
						player2Home.board_[outeri + 1][outerj].setOccupied();
						player2Home.board_[outeri + 2][outerj].setOccupied();
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
					if (player2Home.board_[outeri + 1][outerj].isOccupied() == false)
					{
						player2Home.board_[outeri + 1][outerj].setOccupied();
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

//p1BoardHover
//Detects whether the mouse is over p1's board.
void p2BoardHover()
{
	for (int i = 0; i < player2Home.getSize(); i++)
	{
		for (int j = 0; j < player2Home.getSize(); j++)
		{
			tuple<float, float, float, float> cellBounds = player2Home.board_[i][j].getBounds();
			if (cam_mousex >= std::get<2>(cellBounds)
				&& cam_mousex <= std::get<3>(cellBounds)
				&& cam_mousey >= std::get<0>(cellBounds)
				&& cam_mousey <= std::get<1>(cellBounds))
			{
				player2Home.board_[i][j].setSquareHover(true);

			}
			else
			{
				player2Home.board_[i][j].setSquareHover(false);
			}
		}
	}
}

#endif