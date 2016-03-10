/*
	Arsh Chauhan and Tristan Craddick
	2/24/2016
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
Post: Returns true if cell is the head of ship
*/
bool Cell::isHit()
{
	return isHit_;
}

/*
isMiss
Pre: None
Post: Returns true if cell is the head of ship
*/
bool Cell::isMiss()
{
	return isMiss_;
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
Post: Cell is now a head of some ship
*/
void Cell::setHit()
{
	isHit_ = true;
}

/*
setMiss
Pre: None
Post: Cell is now a head of some ship
*/
void Cell::setMiss()
{
	isMiss_ = true;
}




void Cell::removeHead()
{
	isHead_ = false;
	isOccupied_ = false;
	ship_ID = -1;
}

void Cell::removeOccupied()
{
	isOccupied_ = false;
	ship_ID = -1;
}

tuple<float,float,float,float> Cell::getBounds()
{
	return make_tuple <float&,float&,float&,float&> (bottomBound_,topBound_,leftBound_,rightBound_);
}

void Cell::setBounds(float topBound, float bottomBound, float leftBound, float rightBound)
{
	topBound_ = topBound;
	bottomBound_ = bottomBound;
	leftBound_ = leftBound;
	rightBound_ = rightBound;
}

void Cell::setSquareHover(bool mouseOver)
{
	squareHover_ = mouseOver;

}

bool Cell::getSquareHover()
{
	return squareHover_;
}


int Cell::getID()
{
	return ship_ID;
}

void Cell::setID(int num)
{
	ship_ID = num;
}
