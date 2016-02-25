/*
	Arsh Chauhan
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