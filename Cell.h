/*
Arsh Chauhan and Tristan Craddick
Cell Header
*/


#ifndef CELL_H_INCLUDED
#define CELL_H_INCLUDED

#include <tuple>
using std::tuple;

class Cell
{
public:

	bool isOccupied();
	bool isHead();
	bool isHit();
	bool isMiss();

	void setOccupied();
	void setHead();
	void removeHead();
	void removeOccupied();

	void setMiss(); //if a spot that isn't occupied is hit
	void setHit(); //if a spot that is occupied is hit

	tuple<float,float,float,float> getBounds();
	void setBounds(float,float,float,float);
	bool getSquareHover();
	void setSquareHover(bool);

	int getID();
	void setID(int num);


private:
	bool isHead_;
	bool isOccupied_;

	bool isHit_;
	bool isMiss_;

	bool squareHover_; //whether the mouse is over the cell
	float bottomBound_;
	float topBound_;
	float leftBound_;
	float rightBound_;

	int ship_ID;


/********************************Constructors**************************/

public:
	//Default ctor
	//Cell is neither ccupied nor a head by default 
	Cell():isHead_(false),isOccupied_(false),squareHover_(false),isHit_(false),isMiss_(false){};
};


#endif

