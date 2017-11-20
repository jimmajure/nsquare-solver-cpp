/*
 * NSquare.h
 *
 *  Created on: Nov 11, 2017
 *      Author: jim
 *
 * 	A puzzle game that populates n**2-1 squares in a n**2 square grid, shuffles them.
 * 	The blank square can be moved to any contiguous square, swapping it's value. The
 * 	goal is to return to the initial state.
 */

#include <iostream>

#ifndef NSQUARE_H_
#define NSQUARE_H_

const int size = 4;

class NSquare {
public:
	enum Action {UP, DOWN, LEFT, RIGHT, NONE};

	const static char *ACTIONS[5];
	static int constructs;
	static int destructs;

private:
	int nsquare[size][size];
	int lx = 0;
	int ly = 0;

	Action chooseAction(Action *actions, int count, Action previous);

public:
	NSquare();
	NSquare(const NSquare &init);
	virtual ~NSquare();
	void printState();
	void applyMove(Action action);
	void validActions(int &count, Action *actions);
	void randomize(int n);
	bool operator == (const NSquare &ns2) const;
	void operator = (const NSquare &ns2);
	std::size_t hash() const;
};

#endif /* NSQUARE_H_ */
