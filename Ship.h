#ifndef SHIP_H_INCLUDED
#define SHIP_H_INCLUDED

#include <string>
using std::string;
#include <utility>
using std::pair;
#include "Board.h"

class Ship
{
	string type_;
	int length_;
	char orientation_;
	bool destroyed_;
	static int totalShips_; // TO DO: totalShips_ should be linked to player or board

public:
/*********************Constructors********************/
	Ship() = delete;
	Ship(string type, int length);

/*********************Make Ships un-copiable***********/
	Ship(const Ship &) = delete;

/*********************Member Functions****************/
	void placeShip(Board &myBoard,pair<double,double> head, char orientation);


};







#endif