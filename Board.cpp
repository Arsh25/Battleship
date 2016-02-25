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
	return board_.size();
	
}

void Board::setHead(int cell)
{
	board_[cell].setHead();
}

void Board::setOccupied(int cell)
{
	board_[10].setOccupied();
}

bool Board::isHead(int cell)
{
	return board_[10].isHead();
}

bool Board::isOccupied(int cell)
{
	return board_[10].isOccupied();
}