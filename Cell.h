
#ifndef CELL_H_INCLUDED
#define CELL_H_INCLUDED

#include <tuple>
using std::tuple;

class Cell
{
public:
	//these are currently public so that functions to set/retrieve
	//each aren't necessary unless you have another idea.

	bool isOccupied();
	bool isHead();
	void setOccupied();
	void setHead();
	void removeHead();

	void setMiss(); //if a spot that isn't occupied is hit
	void setHit(); //if a spot that is occupied is hit

	tuple<float,float,float,float> getBounds();
	void setBounds(float,float,float,float);
	bool getSquareHover();
	void setSquareHover(bool);


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

//-------------------------------Constrcutors---------------------------\\

public:
	//Default ctor
	//Cell is neither ccupied nor a head by default 
	Cell():isHead_(false),isOccupied_(false),squareHover_(false){};
};
#endif