
#ifndef CELL_H_INCLUDED
#define CELL_H_INCLUDED

#include <tuple>
using std::tuple;

class Cell
{
public:
	//these are currently public so that functions to set/retrieve
	//each aren't necessary unless you have another idea.
	
	bool squarehover = false; //whether the mouse is over the cell

	bool isOccupied();
	bool isHead();
	void setOccupied();
	void setHead();
	tuple<float,float,float,float> getBounds();
	void setBounds(float,float,float,float);
	bool getSquareHover();


private:
	bool isHead_;
	bool isOccupied_;
	float bottomBound_;
	float topBound_;
	float leftBound_;
	float rightBound_;

//-------------------------------Constrcutors---------------------------\\

public:
	//Default ctor
	//Cell is neither ccupied nor a head by default 
	Cell():isOccupied_(false),isHead_(false){};
};
#endif