/*
 * NSquare.cpp
 *
 *  Created on: Nov 11, 2017
 *      Author: jim
 */

#include "NSquare.h"
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string.h>

const char *NSquare::ACTIONS[5] = {
		"UP",
		"DOWN",
		"LEFT",
		"RIGHT",
		"NONE"
	};

int NSquare::constructs = 0;
int NSquare::destructs = 0;

NSquare::NSquare() {
	constructs++;
	nsquare[0][0] = -1;
	int value = 1;
	for (int i=0; i<size; i++) {
		for (int j=0; j<size; j++) {
			if (!(j==0&&i==0)) {
				nsquare[i][j] = value++;
			}
		}
	}
}

NSquare::NSquare(const NSquare &init) {
//	std::cout << "NSquare::NSquare(&init)" << std::endl;
	for (int i=0; i<size; i++) {
		for (int j=0; j<size; j++) {
			nsquare[i][j] = init.nsquare[i][j];
		}
	}
	lx = init.lx;
	ly = init.ly;

	constructs++;
}

NSquare::~NSquare() {
	NSquare::destructs++;
}

void NSquare::printState() {
	printf("******\n");
	for (int i=0; i<size; i++) {
		for (int j=0; j<size; j++) {
			std::cout << nsquare[i][j];
			if (j<size-1) {
				std::cout << ",";
			}
		}
		std::cout << std::endl;
//		printf("%d,%d,%d\n", nsquare[i][0], nsquare[i][1], nsquare[i][2]);
	}
}

/*
 * Move the blank square in the specified direction (if possible).
 */
void NSquare::applyMove(Action action) {
	if (UP==action) {
		if (ly>0) {
			nsquare[ly][lx] = nsquare[ly-1][lx];
			nsquare[ly-1][lx] = -1;
			ly -= 1;
		}
	}
	else if (DOWN == action) {
		if (ly<size-1) {
			nsquare[ly][lx] = nsquare[ly+1][lx];
			nsquare[ly+1][lx] = -1;
			ly += 1;
		}
	}
	else if (LEFT == action) {
		if (lx>0) {
			nsquare[ly][lx] = nsquare[ly][lx-1];
			nsquare[ly][lx-1] = -1;
			lx -= 1;
		}
	}
	else if (RIGHT == action) {
		if (lx<size-1) {
			nsquare[ly][lx] = nsquare[ly][lx+1];
			nsquare[ly][lx+1] = -1;
			lx += 1;
		}
	}
}

/*
 * Given a list of actions, randomly choose one, but don't go back the way you came.
 */
NSquare::Action NSquare::chooseAction(Action *actions, int count, Action previous) {
	int random = rand();
	Action newa = *(actions+(random % count));
	// if this new action would take us back, then take the "next" one...
	// (there will always be at least 2 possible options)
	if ((UP==previous) && (DOWN==newa)) {
		return *(actions+((random+1)%count));
	} else if ((DOWN==previous) && (UP==newa)) {
		return *(actions+((random+1)%count));
	} else if ((LEFT==previous) && (RIGHT==newa)) {
		return *(actions+((random+1)%count));
	} else if ((RIGHT==previous) && (LEFT==newa)) {
		return *(actions+((random+1)%count));
	} else {
		return newa;
	}

}

/*
 * Randomize the puzzle by making n random moves.
 */
void NSquare::randomize(int n) {
	Action actions[4];
	int count;
	Action previous = NONE;

	for (int i=0; i<n; i++) {
		validActions(count, actions);
		previous = chooseAction(actions, count, previous);
		applyMove(previous);
	}
}

/*
 * Find the currently valid actions for the puzzle...
 */
void NSquare::validActions(int &count, Action *actions) {
	count=0;
	if (ly>0) {
		count++;
		*actions = UP;
		actions++;
	}
	if (ly<size-1) {
		count++;
		*actions = DOWN;
		actions++;
	}
	if (lx>0) {
		count++;
		*actions = LEFT;
		actions++;
	}
	if (lx<size-1) {
		count++;
		*actions = RIGHT;
		actions++;
	}
}

bool NSquare::operator == (const NSquare &ns2) const {
//	std::cout << "NSquare::operator == (const NSquare &ns2) const" << std::endl;
	for (int i=0; i<size; i++) {
		for (int j=0; j<size; j++) {
			if (nsquare[i][j] != ns2.nsquare[i][j]) {
				return false;
			}
		}
	}
	return true;
}

void NSquare::operator = (const NSquare &ns2)  {
//	std::cout << "NSquare::operator = (const NSquare &ns2)" << std::endl;
	for (int i=0; i<size; i++) {
		for (int j=0; j<size; j++) {
			nsquare[i][j] = ns2.nsquare[i][j];
		}
	}
	lx = ns2.lx;
	ly = ns2.ly;
}

/*
 * Make a hash function.
 */
std::size_t NSquare::hash() const {
//	std::cout << "NSquare::hash() const" << std::endl;
	int h = 0;
	for (int i=0; i<size; i++) {
		for (int j=0; j<size; j++) {
			h = (h*10) + nsquare[i][j];
		}
	}
	return std::hash<int>{}(h);
}

