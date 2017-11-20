/*
 * NSquareSolver.h
 *
 *  Created on: Nov 12, 2017
 *      Author: jim
 */

#ifndef NSQUARESOLVER_H_
#define NSQUARESOLVER_H_

#include "NSquare.h"
#include <deque>
#include <unordered_set>

namespace std
{
  template<>
    struct hash<NSquare>
    {
      size_t
      operator()(const NSquare & obj) const
      {
        return obj.hash();
      }
    };
}
class NSquareSolver {
public:
	NSquareSolver();
	virtual ~NSquareSolver();
	void graphSearch(NSquare initial, std::deque<NSquare::Action> &actions);

private:
	struct Node {
		NSquare state;
		Node *parent;
		NSquare::Action action;
	};
	NSquare goalState;

	void createResult(std::deque<NSquare::Action> &result, Node *node);
	void printPath(Node *node);
	bool inFrontier(std::deque<Node*> &frontier, NSquare &next);
};


#endif /* NSQUARESOLVER_H_ */
