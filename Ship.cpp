#include "Ship.h"
#include <utility>
using std::pair;

int Ship::totalShips_ = 0;

/*
  2-param Ctor
  Pre: None
  Post: Creates a new ship with
  			type_ = type 
  			length_ = length 
  			Increments totalShips_ by 1
*/
Ship::Ship(string type, int length):type_(type),length_(length),destroyed_(false)
{
	++totalShips_;

}

/*
  placeShip
  Pre: head mus be a valid and occupied cell. 
  			orientiation must be 'N','S','W','E'
  Post: Places a ship on the board whose head is at cell in location head facing in the direction of orientation
  			Sets all cells on which the ship resides to occupied 
*/
void Ship::placeShip(Board &myBoard,pair<double,double> head, char orientation)
{
	//TO DO: Implement to satisfy post conditions
}