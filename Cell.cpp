/*
	Arsh Chauhan and Tristan Craddick
	2/24/2016
	Last Edited: 03/10/2016
	Source files for header Cell 
*/

#include "Cell.h"

#include <tuple>
using std::tuple;
using std::make_tuple;

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
isHit
Pre: None
Post: Returns true if cell is a 'hit'
*/
bool Cell::isHit()
{
	return isHit_;
}

/*
isMiss
Pre: None
Post: Returns true if cell is a 'miss'
*/
bool Cell::isMiss()
{
	return isMiss_;
}

/*
isSunk
Pre: None
Post: Returns true if cell is part of a sunken ship
*/
bool Cell::isSunk()
{
	return isSunk_;
}

/*
isTarSunk
Pre: None
Post: Returns true if target cell is of a sunken ship.
*/
bool Cell::isTarSunk()
{
	return isTarSunk_;
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

/*
setHit
Pre: None
Post: Cell is now a 'hit'
*/
void Cell::setHit()
{
	isHit_ = true;
}

/*
setMiss
Pre: None
Post: Cell is now a 'miss'
*/
void Cell::setMiss()
{
	isMiss_ = true;
}

/*
setSunk
Pre: None
Post: Cell is now a part of a sunken ship
*/
void Cell::setSunk()
{
	isSunk_ = true;
}

/*
setSunk
Pre: None
Post: Cell is now a part of a sunken ship.
*/
void Cell::setTarSunk()
{
	isTarSunk_ = true;
}



/*
removeHead
Pre: None
Post: The cell is now longer the head, or occupied
*/
void Cell::removeHead()
{
	isHead_ = false;
	isOccupied_ = false;
}

/*
removeOccupied
Pre: None
Post: Cell is no longer occupied
*/
void Cell::removeOccupied()
{
	isOccupied_ = false;
}

/*
getBounds
Pre: None
Post: returns a tuple containing the 4 bounds of a cell.
*/
tuple<float,float,float,float> Cell::getBounds()
{
	return make_tuple <float&,float&,float&,float&> (bottomBound_,topBound_,leftBound_,rightBound_);
}

/*
setBounds
Pre: None
Post: sets the 4 bound-variables of a cell to the passed in bounds.
*/
void Cell::setBounds(float topBound, float bottomBound, float leftBound, float rightBound)
{
	topBound_ = topBound;
	bottomBound_ = bottomBound;
	leftBound_ = leftBound;
	rightBound_ = rightBound;
}

/*
setSquareHover
Pre: None
Post: sets the variable for the mouse hovering over the square to true
*/
void Cell::setSquareHover(bool mouseOver)
{
	squareHover_ = mouseOver;

}

/*
getSquareHover
Pre: None
Post: returns whether or not the square is currently being hovered over
*/
bool Cell::getSquareHover()
{
	return squareHover_;
}

/*
getID
Pre: None
Post: returns the ship ID associated with the cell
*/
int Cell::getID()
{
	return ship_ID;
}

/*
setMiss
Pre: None
Post: sets the ship ID associated with the cell.
*/
void Cell::setID(int num)
{
	ship_ID = num;
}
