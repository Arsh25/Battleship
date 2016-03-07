
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



//drawLargeGrid()
//draws the Large Grid for placing ships and when the gae starts,
//for firing upon.
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
			
			
			glPopMatrix();

		}
	}

	

}

//drawSmallBoard()
//draws the small board in the lower left.
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


			glPopMatrix();

		}
	}

}


//boardPlace()
//Upon first click on the large grid for the passed board, places the head of a ship,
//and then, following the selection of the ship, when the mouse is within the bounds of
//the four directions moving out from the head, places the body of 
//the ship in said direction.
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


						if (isClicking == false)
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
	}


	//By looking at where the mouse is relative to the previously placed head, 
	//this loop set will place the body of the ship in the correct orientation
	//using the mouse position and the current ship that was last selected for
	//the size of the body.
	if (isClicking)
	{
		tuple<float, float, float, float> cellBounds = player.board_[outeri][outerj].getBounds();
		float bottomside = std::get<0>(cellBounds);
		float topside = std::get<1>(cellBounds);
		float leftside = std::get<2>(cellBounds);
		float rightside = std::get<3>(cellBounds);

		float xp = (0.16*outeri) + l_gridstart_x;
		float yp = -(0.16*outerj) + l_gridstart_y;

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
						curr_ship = -1;
						ships_placed++;
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
						curr_ship = -1;
						ships_placed++;
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
						curr_ship = -1;
						ships_placed++;
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


#endif