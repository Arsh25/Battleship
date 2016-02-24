// Battleship_test.cpp
//
// For CS 372 Spring 2016
// Unit tests for Battleship Project
// Uses the "Catch" C++ Unit-Testing Framework

#define CATCH_CONFIG_MAIN  // We want Catch to write function main
#include "catch.hpp"       // For the "Catch" unit-testing framework

#include "Board.h"

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
// For _1, used with std::bind




// ***** Test Cases *****


TEST_CASE("2 param  Constructor", "[Board]")
{
	Board primary(10,true);

	REQUIRE(primary.getSize() == 10);
	REQUIRE(primary.isPrimary() == true);

	Board target(10,false); //Testing Target board construction
	REQUIRE(target.getSize() == 10);
	REQUIRE(target.isPrimary() == false);


}


TEST_CASE("GUI Set-up Tests", "[ex b]")
{
	REQUIRE(gui_Include);
	REQUIRE(gui_Init);
	REQUIRE(gui_Board);

}


