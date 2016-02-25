// fa2.h  
// Tristan J Craddick
// For CS 372 Battleship Game

#ifndef Board_h_included
#define Board_h_included

#include <vector>
using std::vector;
#include <cstddef>
using std::size_t;

class Cell
{
public:
	bool isOccupied();
	bool isHead();
	void setOccupied();
	void setHead();

	bool occupied;
};

//------------------Prototypes-----------------------\\

class Board
{
public:
	bool isOccupied();
	bool isPrimary();
	int getSize();
	void setSize(int size);




private:
	int boardSize_;
	bool squareOccupied_;
	bool isPrimary_;

public:
//	Cell * board = new Cell[boardSize_][boardSize_];

	vector<Cell> board_;


//-----------------Constructors----------------------\\

Board (int size, bool isPrimary):boardSize_(size),isPrimary_(isPrimary){  board_.resize(boardSize_); }

};

//-------------------Function Definitions------------\\


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

#endif
