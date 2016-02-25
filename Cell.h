
#ifndef CELL_H_INCLUDED
#define CELL_H_INCLUDED

class Cell
{
public:
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