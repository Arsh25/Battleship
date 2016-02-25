/*
	Arsh Chauhan
	2/24/2016
	Source files for header Cell 
*/

#include "Cell.h"

/*
	isOccupied
	Pre: None
	Post: Returns true if cell is occupied 
*/
bool Cell::isOccupied()
{
	return isOccupied_;
}

/*
	isHead
	Pre: None
	Post: Returns true if cell is the head of ship  
*/
bool Cell::isHead()
{
	return isHead_;
}

/*
	setOccupied
	Pre: None
	Post: Sets cell to occupied state 
*/
void Cell::setOccupied()
{
	isOccupied_ = true;
}

/*
	setHead
	Pre: None
	Post: Cell is now a head of some ship 
*/
void Cell::setHead() 
{
	isHead_ = true;
}