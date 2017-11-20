//============================================================================
// Name        : helloworld.cpp
// Author      : Jim Majure
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <string.h>
#include "NSquare.h"
#include "NSquareSolver.h"

using namespace std;

int assert(int test, const char *message) {
	if (!test) {
		printf("Error: %s\n", message);
	}
	return 0;
}

void testNSquare() {
	NSquare::Action validActions[4];
	int count;

	NSquare ns;
	ns.printState();
	ns.validActions(count, validActions);
	cout << "Count: " << count << endl;
	for (int i=0; i<count; i++) {
		cout << "\tDirection: " << validActions[i] << endl;
	}

	ns.applyMove(NSquare::RIGHT);
	ns.printState();
	ns.validActions(count, validActions);
	cout << "Count: " << count << endl;
	for (int i=0; i<count; i++) {
		cout << "\tDirection: " << validActions[i] << endl;
	}

	ns.applyMove(NSquare::RIGHT);
	ns.printState();
	ns.validActions(count, validActions);
	cout << "Count: " << count << endl;
	for (int i=0; i<count; i++) {
		cout << "\tDirection: " << validActions[i] << endl;
	}

	ns.applyMove(NSquare::DOWN);
	ns.printState();
	ns.validActions(count, validActions);
	cout << "Count: " << count << endl;
	for (int i=0; i<count; i++) {
		cout << "\tDirection: " << validActions[i] << endl;
	}

	ns.applyMove(NSquare::LEFT);
	ns.printState();
	ns.validActions(count, validActions);
	cout << "Count: " << count << endl;
	for (int i=0; i<count; i++) {
		cout << "\tDirection: " << validActions[i] << endl;
	}

	srand(time(NULL));
	ns.randomize(1);
	ns.printState();

	ns.randomize(2);
	ns.printState();

	ns.randomize(3);
	ns.printState();

	NSquare ns2;
	ns2.randomize(7);
}

void testSolver() {
	srand(time(NULL));

	NSquare ns;
	ns.randomize(10);
	NSquareSolver solver;
	std::deque<NSquare::Action> result;
	solver.graphSearch(ns, result);

	ns.printState();

	cout << "Solution: " << endl;
	for (NSquare::Action a : result) {
		cout << NSquare::ACTIONS[a] << ":";
		ns.applyMove(a);
	}
	cout << endl;
	ns.printState();
}

int main(int argc, char *argv[]) {

//	testStack();
	cout << "Constructs: " << NSquare::constructs << endl;
	cout << "Destructs: " << NSquare::destructs << endl;
	{
		testSolver();
	}
	cout << "Constructs: " << NSquare::constructs << endl;
	cout << "Destructs: " << NSquare::destructs << endl;

	return 0;
}
