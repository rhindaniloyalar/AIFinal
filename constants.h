// constants.h:	Needed constants for Dao game.
// Author:		Michael R. Scheessele
// Date:		02/25/12
// Microsoft Visual C++
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <fstream>
using namespace std;

const unsigned short XYDIM = 4;
const unsigned short EMPTY = 0;
const unsigned short PLAYER1 = 1;
const unsigned short PLAYER2 = 2;

struct Move
{
	unsigned short player;
	unsigned short src_x;
	unsigned short src_y;
	unsigned short dst_x;
	unsigned short dst_y;
};

#endif