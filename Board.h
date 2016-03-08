// Board.h  
// Tristan J Craddick and Arsh Chauhan
// For CS 372 Battleship Game

#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include "Cell.h"
#include <vector>
using std::vector;
#include <cstddef>
using std::size_t;


/*****************Prototypes********************/

class Board
{
public:
	bool isOccupied(int,int);
	bool isPrimary();
	int getSize();
	void setSize(int size);

/*****************functions to act on our board's cells********************/
	int totalCells();
	void setHead(int,int);
	void setOccupied(int,int);
	bool isHead(int,int);

	vector<vector<Cell>> board_; //Collection of cells 
	
 private:
	int boardSize_;
	int totalCells_;
	bool squareOccupied_;
	bool isPrimary_;
	

public:

/*****************Constructors********************/

Board (int size, bool isPrimary):boardSize_(size),totalCells_(size*size),isPrimary_(isPrimary)
{  
	board_.resize(boardSize_); 
	for (int i = 0; i < boardSize_; i++)
	{
		board_[i].resize(boardSize_);
	}
}

};


#endif
