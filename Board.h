// fa2.h  
// Tristan J Craddick
// For CS 372 Battleship Game

#ifndef Board_h_included
#define Board_h_included

#include <vector>
using std::vector;
#include <cstddef>
using std::size_t;



//------------------Prototypes-----------------------\\

class Board
{
public:
	bool isOccupied();
	int getSize();
	void setSize(int size);


private:
	int boardSize;
	bool squareOccupied;

};

//-------------------Function Definitions------------\\


int Board::getSize()
{
	return 0;
	
}

void Board::setSize(int size)
{
	
}

#endif