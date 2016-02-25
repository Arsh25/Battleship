/*
	Arsh Chauhan
	02/24/2016
	Source for header Board.h
*/

#include "Board.h"

int Board::getSize()
{
	return boardSize_;
	
}

void Board::setSize(int size)
{
	boardSize_ = size;
}

bool Board::isPrimary()
{
	return isPrimary_;
}

//Functions that perfomrs work on cells

int Board::totalCells()
{
	return totalCells_;
	
}

void Board::setHead(int row, int column)
{
	board_[row][column].setHead();
}

void Board::setOccupied(int row, int column)
{
	board_[row][column].setOccupied();
}

bool Board::isHead(int row, int column)
{
	return board_[row][column].isHead();
}

bool Board::isOccupied(int row, int column)
{
	return board_[row][column].isOccupied();
}