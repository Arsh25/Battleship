// Board.h  
// Tristan J Craddick
// For CS 372 Battleship Game

#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include "Cell.h"
#include <vector>
using std::vector;
#include <cstddef>
using std::size_t;


//------------------Prototypes-----------------------\\

class Board
{
public:
	bool isOccupied();
	bool isPrimary();
	int getSize();
	void setSize(int size);

//--------functions to act on our board's cells--------//
	int totalCells();
	void setHead(int);
	void setOccupied(int); 
	bool isHead(int);
	bool isOccupied(int);

	vector<vector<Cell>> board_;
private:
	int boardSize_;
	bool squareOccupied_;
	bool isPrimary_;
	//vector<Cell> board_; // Represents the individual cells 
	

public:

//-----------------Constructors----------------------//

Board (int size, bool isPrimary):boardSize_(size),isPrimary_(isPrimary)
{  
	board_.resize(boardSize_); 
	for (int i = 0; i < boardSize_; i++)
	{
		board_[i].resize(boardSize_);
	}
}

};


#endif
