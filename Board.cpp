/*
	Arsh Chauhan and Tristan Craddick
	02/24/2016
	Source for header Board.h
*/

#include "Board.h"

/*getSize
  Pre: None 
  Post: Returns the size of the board
*/
int Board::getSize()
{
	return boardSize_;
	
}

/*setSize
  Pre: None 
  Post: Sets the size of the board
*/
void Board::setSize(int size)
{
	boardSize_ = size;
}

/*isPrimary
  Pre: None 
  Post: returns 
  		   true: If board is targeting board
  		   false: If board is home board  
*/
bool Board::isPrimary()
{
	return isPrimary_;
}

//*********Functions that perform work on cells*********

/*totalCells
  Pre: None 
  Post: returns total cells in a board
*/
int Board::totalCells()
{
	return totalCells_;
	
}

/*setHead
  Pre: row and column must represent a valid cell 
  Post: Sets the cell at location [row][column] as a ship's Head
*/
void Board::setHead(int row, int column)
{
	board_[row][column].setHead();
}

/*isHead
  Pre: row and column must represent a valid cell 
  Post: Retuns
  			true: If cell at location [row][column] is a ship's head
  			false: If cell at location [row][column] is not a ship's head 
*/
bool Board::isHead(int row, int column)
{
	return board_[row][column].isHead();
}

/*setOccupied
  Pre: row and column must represent a valid cell 
  Post: Sets the cell at location [row][column] as occupied
*/
void Board::setOccupied(int row, int column)
{
	board_[row][column].setOccupied();
}

/*isOccupied
  Pre: row and column must represent a valid cell 
  Post: Retuns
  			true: If cell at location [row][column] is occupied
  			false: If cell at location [row][column] is occupied  
*/
bool Board::isOccupied(int row, int column)
{
	return board_[row][column].isOccupied();
}


