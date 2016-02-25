
#ifndef CELL_H_INCLUDED
#define CELL_H_INCLUDED

class Cell
{
public:
	//these are currently public so that functions to set/retrieve
	//each aren't necessary unless you have another idea.
	float bottombound;
	float topbound;
	float leftbound;
	float rightbound;
	bool squarehover = false; //whether the mouse is over the cell

	bool isOccupied();
	bool isHead();
	void setOccupied();
	void setHead();

private:
	bool isHead_;
	bool isOccupied_;

//-------------------------------Constrcutors---------------------------\\

public:
	//Default ctor
	//Cell is neither ccupied nor a head by default 
	Cell():isOccupied_(false),isHead_(false){};
};
#endif