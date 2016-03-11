// Battleship_test.cpp
//
// For CS 372 Spring 2016
// Unit tests for Battleship Project
// Uses the "Catch" C++ Unit-Testing Framework

#define CATCH_CONFIG_MAIN  // We want Catch to write function main
#include "catch.hpp"       // For the "Catch" unit-testing framework

#include "Board.h"
#include "Cell.h"

#include <vector>
using std::vector;
#include <algorithm>
using std::equal;
#include <cstddef>
using std::size_t;
#include <functional>
using std::function;
using std::bind;
using namespace std::placeholders;
#include <tuple>
using std::tuple;
using std::make_tuple;
// For _1, used with std::bind




// ***** Test Cases *****


TEST_CASE("2 param  Constructor", "[Board]")
{
	const int SIZE = 10;
	const int CELLS = SIZE*SIZE;
	Board primary(SIZE,true);

	REQUIRE(primary.getSize() == SIZE);
	REQUIRE(primary.isPrimary() == true);

	Board target(SIZE,false); //Testing Target board construction
	REQUIRE(target.getSize() == SIZE);
	REQUIRE(target.isPrimary() == false);

}

TEST_CASE(" Testing manipulating cells from board","[BOARD]")
{
	const int SIZE = 10;
	const int CELLS = SIZE*SIZE;
	Board cellTest(SIZE,true);
	
	REQUIRE(cellTest.isPrimary() == true);
	REQUIRE(cellTest.totalCells() == CELLS);
	cellTest.setHead(9,9);
	REQUIRE(cellTest.isHead(9,9) == true);
	cellTest.setOccupied(9,4);
	REQUIRE(cellTest.isOccupied(9,4) == true);

}

//Tests to see if cell properties are correctly returned
TEST_CASE("Setting Cell Properties", "[CELL]")
{
	Cell cell1;
	REQUIRE(cell1.isOccupied() == false);
	cell1.setOccupied();
	REQUIRE(cell1.isOccupied() == true);

	REQUIRE(cell1.isHead() == false);
	cell1.setHead();
	REQUIRE(cell1.isHead() == true);


	Cell target;
	REQUIRE(target.isMiss() == false);
	target.setMiss();
	REQUIRE(target.isMiss() == true);

	Cell target2;
	REQUIRE(target2.isHit() == false);
	target2.setHit();
	REQUIRE(target2.isHit() == true);
}

//Tests to see if cell properties are correctly returned
TEST_CASE("Detecting if cell counts are properly decremented", "[CELL]")
{
	const int SIZE = 10;
	Board ship_self(SIZE, true);
	Board ship_opponent(SIZE, true);
	ship_opponent.board_[0][0].setOccupied();
	ship_opponent.board_[0][0].setID(0);
	ship_opponent.ship_cells[0] = 1;

	//simulating a shot
	if (ship_opponent.board_[0][0].isOccupied() == true)
	{
		ship_self.board_[0][0].setHit();
		shipCheck(ship_opponent, ship_opponent.board_[0][0].getID());
		ship_opponent.board_[0][0].removeOccupied();
	}

	REQUIRE(ship_self.board_[0][0].isHit() == true);
	REQUIRE(ship_opponent.ship_cells[0] == 0); //simulating a call to winCheck
	REQUIRE(ship_opponent.board_[0][0].isOccupied() == false);

}

TEST_CASE("Testing Cell Bounds", "[CELL]")
{
	Cell cell1;
	cell1.setBounds(1,2,3,4);
	tuple <float,float,float,float> correctBounds = make_tuple(2,1,3,4);
	auto recvdAnswer=cell1.getBounds();
	REQUIRE(recvdAnswer == correctBounds);
	cell1.setBounds(2.33,-4.55,23,45.55);
	correctBounds = make_tuple(-4.55,2.33,23,45.55);
	recvdAnswer = cell1.getBounds();
	REQUIRE(recvdAnswer == correctBounds);
	cell1.setBounds(-2.33,-4.55,-23,-45.55);
	correctBounds = make_tuple(-4.55,-2.33,-23,-45.55);
	recvdAnswer = cell1.getBounds();
	REQUIRE(recvdAnswer == correctBounds);

}


TEST_CASE("GUI Set-up Tests", "[GUI]")
{
	REQUIRE(gui_Include);
	REQUIRE(gui_Init);

}



