/*
 * NSquareSolver.cpp
 *
 * A class to solve the n-square puzzy using a breadth-first search algorithm
 * as described in Artificial Intelligence, A Modern Approach.
 *
 *  Created on: Nov 12, 2017
 *      Author: jim
 */

#include "NSquareSolver.h"

NSquareSolver::NSquareSolver() {
}

NSquareSolver::~NSquareSolver() {
}

/*
 * Create a list of Actions that solve the puzzle by putting the tiles into the
 * goal state.
 */
void NSquareSolver::createResult(std::deque<NSquare::Action> &result, Node *node) {
	while (node->parent != NULL) {
		result.push_front(node->action);
		node = node->parent;
	}
}

/*
 * Given a tree node, print the path represented by the node.
 */
void NSquareSolver::printPath(Node *node) {
	while (node->parent != NULL) {
		std::cout << NSquare::ACTIONS[node->action] << ":";
		node = node->parent;
	}
	std::cout << std::endl;
}

/*
 * Check to see if the frontier contains a specific state of the puzzle.
 */
bool NSquareSolver::inFrontier(std::deque<Node*> &frontier, NSquare &next) {
	for (unsigned int i=0; i<frontier.size(); i++) {
		if (frontier[i]->state == next) {
			return true;
		}
	}
	return false;
}

/*
 * Solve a given puzzle by searching the solution space for a valid solution.
 */
void NSquareSolver::graphSearch(NSquare initial, std::deque<NSquare::Action> &actions) {

	std::deque<Node*> frontier;
	std::unordered_set<NSquare> explored;
	std::deque<Node*> allNodes;

	NSquare::Action validActions[4];
	int count;

	Node *n = new Node;
	n->action = NSquare::NONE;
	n->state  = initial;
	n->parent = NULL;

	allNodes.push_front(n);

	frontier.push_front(n);
	while(true) {
		if (frontier.size()==0) {
			// we didn't find a solution. Shouldn't happen.
			return;
		}
		Node *n2 = frontier.back();
		frontier.pop_back();
//		printPath(n2);
		if (n2->state == goalState) {
			createResult(actions, n2);
			// Make sure all tree memory is deallocated.
			for (Node *n : allNodes) {
				delete n;
			}
			return;
		} else {
			explored.insert(n2->state);
			n2->state.validActions(count, validActions);
			for (int i=0; i<count; i++) {
				NSquare next(n2->state);
				next.applyMove(validActions[i]);
				bool in_explored = explored.find(next)!=explored.end();
				if (!(in_explored && inFrontier(frontier, next))) {
					Node *newNode = new Node;
					newNode->action = validActions[i];
					newNode->state  = next;
					newNode->parent = n2;
					allNodes.push_front(newNode);
					frontier.push_front(newNode);
				}
			}
		}
	}
}
