
/*
Tristan Craddick
Board Gui  Header

For CS 372 Battleship Game
*/

#ifndef GUI_BOARD_H_INCLUDED
#define GUI_BOARD_H_INCLUDED

#include "gui_Globals.h"

//-----------------Drawing Functions---------------

//drawSquare
/*
Pre: None
Post: Draws an unmodified, filled square.
*/
void drawSquare()
{
	glBegin(GL_POLYGON);
	glVertex2d(-1., -1.);
	glVertex2d(1., -1.);
	glVertex2d(1., 1.);
	glVertex2d(-1., 1.);
	glEnd();

}

// Draws a outlined square
/*
Pre: None
Post: An unmodified, blank square is drawn on the screen.
*/
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

//shipCheck()
//when a shot fired is a confirmed hit, takes the id of the ship 
//in the cell and decrements the appropriate counter.
/*
Pre: None
Post: When a shot was detected as a hit upon a cell, detects which
	ship the cell was a part of based upon the appropriate ID,
	and decrements the board based counter to determine how many
	cells of the ship are left.
*/
void shipCheck(Board& player, int ID)
{
	switch (ID)
	{
	case 0:
		player.ship_cells[0]--;
		break;

	case 1:
		player.ship_cells[1]--;
		break;

	case 2:
		player.ship_cells[2]--;
		break;

	case 3:
		player.ship_cells[3]--;
		break;

	case 4:
		player.ship_cells[4]--;
		break;




	}
}

//drawLargeGrid()
//draws the Large Grid for placing ships and when the gae starts,
//for firing upon.
/*
Pre: None
Post: draws the large grid on the right side of the screen based upon
	which board is passed into the function to check which cells are
	occupied/hit/missed/etc.
*/
void drawLargeGrid(Board& player)
{

	for (int i = 0; i < player.getSize(); i++)
	{
		for (int j = 0; j < player.getSize(); j++)
		{
			glColor3d(0.4, 0.4, 0.4);
			float x = (0.2*i);
			float y = -(0.2*j);

			glPushMatrix();
			glColor3d(0.4, 0.4, 0.4);
			glTranslated(x, y, 0.0);
			glScaled(0.1, 0.1, 0.0);
			drawEmpSquare();

			if (player.board_[i][j].getSquareHover() == true)
			{
				glColor3d(0.8, 0.8, 0.0); //yellow
				drawSquare();
			}

			
			//These alternate x and y values are used to take into accound linethickness
			// for the boundaries of the squares.
			float ax = i*0.16;
			float ay = -(j*0.16);

			float leftBound = ax - 0.075 + l_gridstart_x ;
			float rightBound = ax + 0.075 + l_gridstart_x ;

			float bottomBound = ay - 0.075 + l_gridstart_y;
			float topBound = ay + 0.075 + l_gridstart_y ;


			player.board_[i][j].setBounds(topBound,bottomBound,leftBound,rightBound); 

			if (player.board_[i][j].isHead())
			{
				glColor3d(0.4, 0.4, 0.9); //darkish blue
				drawSquare();
			}
			if (player.board_[i][j].isOccupied() == true && player.board_[i][j].isHead() == false)
			{
				glColor3d(0.3, 0.7, 0.7); //light blue
				drawSquare();
			}
			if (player.board_[i][j].isMiss() == true)
			{
				glColor3d(0.7, 0.3, 0.3); //red
				drawSquare();

			}
			if (player.board_[i][j].isHit() == true)
			{
				glColor3d(0.3, 0.7, 0.3); //green
				drawSquare();

			}
			
			
			glPopMatrix();

		}
	}

	

}

//drawSmallBoard()
//draws the small board in the lower left.
/*
Pre: None
Post: draws a board in the lower left of the screen based upon which
	board was passed into the function like the drawLargeBoard 
	function.
*/
void drawSmallBoard(Board& player)
{
	for (int i = 0; i < player.getSize(); i++)
	{
		for (int j = 0; j < player.getSize(); j++)
		{
			glColor3d(0.4, 0.4, 0.4);
			float x = (0.1*i);
			float y = -(0.1*j);

			glPushMatrix();
			glColor3d(0.4, 0.4, 0.4);
			glTranslated(x, y, 0.0);
			glScaled(0.05, 0.05, 0.0);

			drawEmpSquare();


																//the following needs to be edited to show the player board, along with hits/misses
			if (player.board_[i][j].getSquareHover() == true)
			{
				glColor3d(0.8, 0.8, 0.0); //yellow
				drawSquare();
			}


			if (player.board_[i][j].isHead())
			{
				glColor3d(0.4, 0.4, 0.9); //darkish blue
				drawSquare();
			}
			if (player.board_[i][j].isOccupied() == true && player.board_[i][j].isHead() == false)
			{
				glColor3d(0.3, 0.7, 0.7); //light blue
				drawSquare();
			}
			if (player.board_[i][j].isMiss() == true)
			{
				glColor3d(0.7, 0.3, 0.3); //red
				drawSquare();

			}


			glPopMatrix();

		}
	}

}


//boardPlace()
/*
Pre: None
Post: Upon first click on the large grid for the passed board, places the head of a ship,
	and then, following the selection of the ship, when the mouse is within the bounds of
	the four directions moving out from the head, places the body of 
	the ship in said direction.
*/
void boardPlace(Board& player)
{

	//this loop set involves the placement of the head of the ship on the board,
	//it sets the isClicking variable to true which tells the program that the
	//next loop set will be used for determining the orientation of the ship.
	for (int i = 0; i < player.getSize(); i++)
	{
		for (int j = 0; j < player.getSize(); j++)
		{

			//Placing the ships
			if (isClicking == false)
			{
				if (player.board_[i][j].getSquareHover() == true)
				{
					if (player.board_[i][j].isOccupied() == false)
					{


							player.board_[i][j].setHead();
							player.board_[i][j].setOccupied();
							isClicking = true;
							outeri = i;
							outerj = j;
						

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
		float xp = (0.16*outeri) + l_gridstart_x;
		float yp = -(0.16*outerj) + l_gridstart_y;



		//facing up
		if (cam_mousex >= xp - 0.073
			&& cam_mousex <= xp + 0.073
			&& cam_mousey >= yp + 0.073
			&& cam_mousey <= yp + 0.233)
		{

			switch (curr_ship)
			{
			case 0: //ship size = 5
				if (outerj > 3)
				{
					if (player.board_[outeri][outerj - 1].isOccupied() == false
						&& player.board_[outeri][outerj - 2].isOccupied() == false
						&& player.board_[outeri][outerj - 3].isOccupied() == false
						&& player.board_[outeri][outerj - 4].isOccupied() == false)
					{
						player.board_[outeri][outerj - 1].setOccupied();
						player.board_[outeri][outerj - 2].setOccupied();
						player.board_[outeri][outerj - 3].setOccupied();
						player.board_[outeri][outerj - 4].setOccupied();
						isClicking = false;
						box_used[0] = true;
						player.ship_cells[0] = 5;
						player.board_[outeri][outerj].setID(curr_ship);
						player.board_[outeri][outerj-1].setID(curr_ship);
						player.board_[outeri][outerj-2].setID(curr_ship);
						player.board_[outeri][outerj-3].setID(curr_ship);
						player.board_[outeri][outerj-4].setID(curr_ship);
						curr_ship = -1;
						ships_placed++;
						return;
					}
				}
				break;
			case 1: //ship size = 4
				if (outerj > 2)
				{
					if (player.board_[outeri][outerj - 1].isOccupied() == false
						&& player.board_[outeri][outerj - 2].isOccupied() == false
						&& player.board_[outeri][outerj - 3].isOccupied() == false)
					{
						player.board_[outeri][outerj - 1].setOccupied();
						player.board_[outeri][outerj - 2].setOccupied();
						player.board_[outeri][outerj - 3].setOccupied();
						isClicking = false;
						box_used[1] = true;
						player.ship_cells[1] = 4;
						player.board_[outeri][outerj].setID(curr_ship);
						player.board_[outeri][outerj - 1].setID(curr_ship);
						player.board_[outeri][outerj - 2].setID(curr_ship);
						player.board_[outeri][outerj - 3].setID(curr_ship);
						curr_ship = -1;
						ships_placed++;
						return;
					}
				}
				break;
			case 2: //ship size = 3
				if (outerj > 1)
				{
					if (player.board_[outeri][outerj - 1].isOccupied() == false
						&& player.board_[outeri][outerj - 2].isOccupied() == false)
					{
						player.board_[outeri][outerj - 1].setOccupied();
						player.board_[outeri][outerj - 2].setOccupied();
						isClicking = false;
						box_used[2] = true;
						player.ship_cells[2] = 3;
						player.board_[outeri][outerj].setID(curr_ship);
						player.board_[outeri][outerj - 1].setID(curr_ship);
						player.board_[outeri][outerj - 2].setID(curr_ship);
						curr_ship = -1;
						ships_placed++;
						return;
					}
				}
				break;
			case 3: //ship size = 3
				if (outerj > 1)
				{
					if (player.board_[outeri][outerj - 1].isOccupied() == false
						&& player.board_[outeri][outerj - 2].isOccupied() == false)
					{
						player.board_[outeri][outerj - 1].setOccupied();
						player.board_[outeri][outerj - 2].setOccupied();
						isClicking = false;
						box_used[3] = true;
						player.ship_cells[3] = 3;
						player.board_[outeri][outerj].setID(curr_ship);
						player.board_[outeri][outerj - 1].setID(curr_ship);
						player.board_[outeri][outerj - 2].setID(curr_ship);
						curr_ship = -1;
						ships_placed++;
						return;
					}
				}
				break;
			case 4: //ship size = 2
				if (outerj > 0)
				{
					if (player.board_[outeri][outerj - 1].isOccupied() == false)
					{
						player.board_[outeri][outerj - 1].setOccupied();
						isClicking = false;
						box_used[4] = true;
						player.ship_cells[4] = 2;
						player.board_[outeri][outerj].setID(curr_ship);
						player.board_[outeri][outerj - 1].setID(curr_ship);
						curr_ship = -1;
						ships_placed++;
						return;
					}
				}
				break;
			}



		}


		//facing down
		if (cam_mousex >= xp - 0.073
			&& cam_mousex <= xp + 0.073
			&& cam_mousey <= yp - 0.073
			&& cam_mousey >= yp - 0.233)
		{

			switch (curr_ship)
			{
			case 0: //ship size = 5
				if (outerj < 6)
				{
					if (player.board_[outeri][outerj + 1].isOccupied() == false
						&& player.board_[outeri][outerj + 2].isOccupied() == false
						&& player.board_[outeri][outerj + 3].isOccupied() == false
						&& player.board_[outeri][outerj + 4].isOccupied() == false)
					{
						player.board_[outeri][outerj + 1].setOccupied();
						player.board_[outeri][outerj + 2].setOccupied();
						player.board_[outeri][outerj + 3].setOccupied();
						player.board_[outeri][outerj + 4].setOccupied();
						isClicking = false;
						box_used[0] = true;
						player.ship_cells[0] = 5;
						player.board_[outeri][outerj].setID(curr_ship);
						player.board_[outeri][outerj + 1].setID(curr_ship);
						player.board_[outeri][outerj + 2].setID(curr_ship);
						player.board_[outeri][outerj + 3].setID(curr_ship);
						player.board_[outeri][outerj + 4].setID(curr_ship);
						curr_ship = -1;
						ships_placed++;
						return;
					}
				}
				break;
			case 1: //ship size = 4
				if (outerj < 7)
				{
					if (player.board_[outeri][outerj + 1].isOccupied() == false
						&& player.board_[outeri][outerj + 2].isOccupied() == false
						&& player.board_[outeri][outerj + 3].isOccupied() == false)
					{
						player.board_[outeri][outerj + 1].setOccupied();
						player.board_[outeri][outerj + 2].setOccupied();
						player.board_[outeri][outerj + 3].setOccupied();
						isClicking = false;
						box_used[1] = true;
						player.ship_cells[1] = 4;
						player.board_[outeri][outerj].setID(curr_ship);
						player.board_[outeri][outerj + 1].setID(curr_ship);
						player.board_[outeri][outerj + 2].setID(curr_ship);
						player.board_[outeri][outerj + 3].setID(curr_ship);
						curr_ship = -1;
						ships_placed++;
						return;
					}
				}
				break;
			case 2: //ship size = 3
				if (outerj < 8)
				{
					if (player.board_[outeri][outerj + 1].isOccupied() == false
						&& player.board_[outeri][outerj + 2].isOccupied() == false)
					{
						player.board_[outeri][outerj + 1].setOccupied();
						player.board_[outeri][outerj + 2].setOccupied();
						isClicking = false;
						box_used[2] = true;
						player.ship_cells[2] = 3;
						player.board_[outeri][outerj].setID(curr_ship);
						player.board_[outeri][outerj + 1].setID(curr_ship);
						player.board_[outeri][outerj + 2].setID(curr_ship);
						curr_ship = -1;
						ships_placed++;
						return;
					}
				}
				break;
			case 3: //ship size = 3
				if (outerj < 8)
				{
					if (player.board_[outeri][outerj + 1].isOccupied() == false
						&& player.board_[outeri][outerj + 2].isOccupied() == false)
					{
						player.board_[outeri][outerj + 1].setOccupied();
						player.board_[outeri][outerj + 2].setOccupied();
						isClicking = false;
						box_used[3] = true;
						player.ship_cells[3] = 3;
						player.board_[outeri][outerj].setID(curr_ship);
						player.board_[outeri][outerj + 1].setID(curr_ship);
						player.board_[outeri][outerj + 2].setID(curr_ship);
						curr_ship = -1;
						ships_placed++;
						return;
					}
				}
				break;
			case 4: //ship size = 2
				if (outerj < 9)
				{
					if (player.board_[outeri][outerj + 1].isOccupied() == false)
					{
						player.board_[outeri][outerj + 1].setOccupied();
						isClicking = false;
						box_used[4] = true;
						player.ship_cells[4] = 2;
						player.board_[outeri][outerj].setID(curr_ship);
						player.board_[outeri][outerj + 1].setID(curr_ship);
						curr_ship = -1;
						ships_placed++;
						return;
					}
				}
				break;
			}


		}

		//facing left
		if (cam_mousey >= yp - 0.073
			&& cam_mousey <= yp + 0.073
			&& cam_mousex <= xp - 0.073
			&& cam_mousex >= xp - 0.233)
		{

			switch (curr_ship)
			{
			case 0: //ship size = 5
				if (outeri > 3)
				{
					if (player.board_[outeri - 1][outerj].isOccupied() == false
						&& player.board_[outeri - 2][outerj].isOccupied() == false
						&& player.board_[outeri - 3][outerj].isOccupied() == false
						&& player.board_[outeri - 4][outerj].isOccupied() == false)
					{
						player.board_[outeri - 1][outerj].setOccupied();
						player.board_[outeri - 2][outerj].setOccupied();
						player.board_[outeri - 3][outerj].setOccupied();
						player.board_[outeri - 4][outerj].setOccupied();
						isClicking = false;
						box_used[0] = true;
						player.ship_cells[0] = 5;
						player.board_[outeri][outerj].setID(curr_ship);
						player.board_[outeri - 1][outerj].setID(curr_ship);
						player.board_[outeri - 2][outerj].setID(curr_ship);
						player.board_[outeri - 3][outerj].setID(curr_ship);
						player.board_[outeri - 4][outerj].setID(curr_ship);
						curr_ship = -1;
						ships_placed++;
						return;
					}
				}
				break;
			case 1: //ship size = 4
				if (outeri > 2)
				{
					if (player.board_[outeri - 1][outerj].isOccupied() == false
						&& player.board_[outeri - 2][outerj].isOccupied() == false
						&& player.board_[outeri - 3][outerj].isOccupied() == false)
					{
						player.board_[outeri - 1][outerj].setOccupied();
						player.board_[outeri - 2][outerj].setOccupied();
						player.board_[outeri - 3][outerj].setOccupied();
						isClicking = false;
						box_used[1] = true;
						player.ship_cells[1] = 4;
						player.board_[outeri][outerj].setID(curr_ship);
						player.board_[outeri - 1][outerj].setID(curr_ship);
						player.board_[outeri - 2][outerj].setID(curr_ship);
						player.board_[outeri - 3][outerj].setID(curr_ship);
						curr_ship = -1;
						ships_placed++;
						return;
					}
				}
				break;
			case 2: //ship size = 3
				if (outeri > 1)
				{
					if (player.board_[outeri - 1][outerj].isOccupied() == false
						&& player.board_[outeri - 2][outerj].isOccupied() == false)
					{
						player.board_[outeri - 1][outerj].setOccupied();
						player.board_[outeri - 2][outerj].setOccupied();
						isClicking = false;
						box_used[2] = true;
						player.ship_cells[2] = 3;
						player.board_[outeri][outerj].setID(curr_ship);
						player.board_[outeri - 1][outerj].setID(curr_ship);
						player.board_[outeri - 2][outerj].setID(curr_ship);
						curr_ship = -1;
						ships_placed++;
						return;
					}
				}
				break;
			case 3: //ship size = 3
				if (outeri > 1)
				{
					if (player.board_[outeri - 1][outerj].isOccupied() == false
						&& player.board_[outeri - 2][outerj].isOccupied() == false)
					{
						player.board_[outeri - 1][outerj].setOccupied();
						player.board_[outeri - 2][outerj].setOccupied();
						isClicking = false;
						box_used[3] = true;
						player.ship_cells[3] = 3;
						player.board_[outeri][outerj].setID(curr_ship);
						player.board_[outeri - 1][outerj].setID(curr_ship);
						player.board_[outeri - 2][outerj].setID(curr_ship);
						curr_ship = -1;
						ships_placed++;
						return;
					}
				}
				break;
			case 4: //ship size = 2
				if (outeri > 0)
				{
					if (player.board_[outeri - 1][outerj].isOccupied() == false)
					{
						player.board_[outeri - 1][outerj].setOccupied();
						isClicking = false;
						box_used[4] = true;
						player.ship_cells[4] = 2;
						player.board_[outeri][outerj].setID(curr_ship);
						player.board_[outeri - 1][outerj].setID(curr_ship);
						curr_ship = -1;
						ships_placed++;
						return;
					}
				}
				break;
			}


		}

		//facing right
		if (cam_mousey >= yp - 0.073
			&& cam_mousey <= yp + 0.073
			&& cam_mousex >= xp + 0.073
			&& cam_mousex <= xp + 0.233)
		{

			switch (curr_ship)
			{
			case 0: //ship size = 5
				if (outeri < 6)
				{
					if (player.board_[outeri + 1][outerj].isOccupied() == false
						&& player.board_[outeri + 2][outerj].isOccupied() == false
						&& player.board_[outeri + 3][outerj].isOccupied() == false
						&& player.board_[outeri + 4][outerj].isOccupied() == false)
					{
						player.board_[outeri + 1][outerj].setOccupied();
						player.board_[outeri + 2][outerj].setOccupied();
						player.board_[outeri + 3][outerj].setOccupied();
						player.board_[outeri + 4][outerj].setOccupied();
						isClicking = false;
						box_used[0] = true;
						player.ship_cells[0] = 5;
						player.board_[outeri][outerj].setID(curr_ship);
						player.board_[outeri + 1][outerj].setID(curr_ship);
						player.board_[outeri + 2][outerj].setID(curr_ship);
						player.board_[outeri + 3][outerj].setID(curr_ship);
						player.board_[outeri + 4][outerj].setID(curr_ship);
						curr_ship = -1;
						ships_placed++;
						return;
					}
				}
				break;
			case 1: //ship size = 4
				if (outeri < 7)
				{
					if (player.board_[outeri + 1][outerj].isOccupied() == false
						&& player.board_[outeri + 2][outerj].isOccupied() == false
						&& player.board_[outeri + 3][outerj].isOccupied() == false)
					{
						player.board_[outeri + 1][outerj].setOccupied();
						player.board_[outeri + 2][outerj].setOccupied();
						player.board_[outeri + 3][outerj].setOccupied();
						isClicking = false;
						box_used[1] = true;
						player.ship_cells[1] = 4;
						player.board_[outeri][outerj].setID(curr_ship);
						player.board_[outeri + 1][outerj].setID(curr_ship);
						player.board_[outeri + 2][outerj].setID(curr_ship);
						player.board_[outeri + 3][outerj].setID(curr_ship);
						curr_ship = -1;
						ships_placed++;
						return;
					}
				}
				break;
			case 2: //ship size = 3
				if (outeri < 8)
				{
					if (player.board_[outeri + 1][outerj].isOccupied() == false
						&& player.board_[outeri + 2][outerj].isOccupied() == false)
					{
						player.board_[outeri + 1][outerj].setOccupied();
						player.board_[outeri + 2][outerj].setOccupied();
						isClicking = false;
						box_used[2] = true;
						player.ship_cells[2] = 3;
						player.board_[outeri][outerj].setID(curr_ship);
						player.board_[outeri + 1][outerj].setID(curr_ship);
						player.board_[outeri + 2][outerj].setID(curr_ship);
						curr_ship = -1;
						ships_placed++;
						return;
					}
				}
				break;
			case 3: //ship size = 3
				if (outeri < 8)
				{
					if (player.board_[outeri + 1][outerj].isOccupied() == false
						&& player.board_[outeri + 2][outerj].isOccupied() == false)
					{
						player.board_[outeri + 1][outerj].setOccupied();
						player.board_[outeri + 2][outerj].setOccupied();
						isClicking = false;
						box_used[3] = true;
						player.ship_cells[3] = 3;
						player.board_[outeri][outerj].setID(curr_ship);
						player.board_[outeri + 1][outerj].setID(curr_ship);
						player.board_[outeri + 2][outerj].setID(curr_ship);
						curr_ship = -1;
						ships_placed++;
						return;
					}
				}
				break;
			case 4: //ship size = 2
				if (outeri < 9)
				{
					if (player.board_[outeri + 1][outerj].isOccupied() == false)
					{
						player.board_[outeri + 1][outerj].setOccupied();
						isClicking = false;
						box_used[4] = true;
						player.ship_cells[4] = 2;
						player.board_[outeri][outerj].setID(curr_ship);
						player.board_[outeri + 1][outerj].setID(curr_ship);
						curr_ship = -1;
						ships_placed++;
						return;
					}
				}
				break;
			}


		}


	}

}

//boardHover()
//Detects whether the mouse is over a cell in the large grid for the passed board.
/*
Pre: None
Post: using a tuple created from the bounds of a cell, checks to
	see if the mouse is within the bounds of a cell, if it is,
	then sets the cell variable for hovering to true, so that the square would
	be highlighted. If the mouse is not within bounds, sets the highlight var
	to false.
*/
void boardHover(Board& player)
{
	for (int i = 0; i < player.getSize(); i++)
	{
		for (int j = 0; j < player.getSize(); j++)
		{
			tuple<float, float, float, float> cellBounds = player.board_[i][j].getBounds();
			if (cam_mousex >= std::get<2>(cellBounds) //left side of the cell
				&& cam_mousex <= std::get<3>(cellBounds) //right side
				&& cam_mousey >= std::get<0>(cellBounds) //bottom side
				&& cam_mousey <= std::get<1>(cellBounds)) //top side
			{
				player.board_[i][j].setSquareHover(true); 

			}
			else
			{
				player.board_[i][j].setSquareHover(false); 
			}
		}
	}
}


//boardFire()
//Fires a shot at a cell on the board, determining if there is a hit or miss.
/*
Pre: None
Post: Checks which cell of the passed player board was clicked, and checks
	whether the associated cell on the opponents board is occupied. If it is
	then modifies the cell of the opposing player's board, and decrements
	the appropriate ship variable on their board, while setting the cell
	of the player board to a 'hit'. Otherwise just sets the cell of
	the player board to 'miss'.
*/
void boardFire(Board& player, Board& opponent)
{

	for (int i = 0; i < opponent.getSize(); i++)
	{
		for (int j = 0; j < opponent.getSize(); j++)
		{

			if (player.board_[i][j].getSquareHover() == true)
			{
				if (player.board_[i][j].isHit() == false && player.board_[i][j].isMiss() == false)
				{

					if (opponent.board_[i][j].isOccupied() == false)
					{
						//Misses
						player.board_[i][j].setMiss();
						has_fired = true;
					}
					else
					{
						//Hits

						//sets cells/ships to unoccupied or destroyed
						shipCheck(opponent, opponent.board_[i][j].getID());

						///////////////////////////////////////////////
						//change this section likely if sprites are used.
						if (opponent.board_[i][j].isHead())
						{
							opponent.board_[i][j].removeHead();
						}
						else
						{
							opponent.board_[i][j].removeOccupied();
						}
						opponent.board_[i][j].setMiss();
						////////////////////////////////////////////

						player.board_[i][j].setHit();

						has_fired = true;
					}
				}



			}
			

		}
	}

}





#endif