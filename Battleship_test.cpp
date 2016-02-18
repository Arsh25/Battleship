// fa2_test.cpp
// Glenn G. Chappell
// 12 Feb 2016
//
// For CS 372 Spring 2016
// Unit tests for Assignment 2, Exercises A, B, C
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


// ***** Helper Functions ****





// ***** Test Cases *****


TEST_CASE("Exercise A: Returned vectors have correct size", "[ex a]")
{
	Board test;
	
	
	REQUIRE(test.getSize() == 1000);

}



