#include <iostream>
#include <list>
#include <string>

#include "State.h"
#include "Graph.h"

// General constructor.
Graph::Graph()
{
	list<State> _states;
	list<char> _simbols;
	list<State::Transition> _transitions;
	State _startState;
	list<State> _endStates;
}

// General destructor.
Graph::~Graph()
{

}

// This function will build a NFA based on a regular expresion
// using Thompson's construction algorithm.
Graph Graph::makeNFA(string expression) {
	// Some useful variables.
	Graph NFA;
	// From the postFix we made, we know that the expression is valid.
	for (size_t i = 0; expression.size(); i++) {

	}

	return NFA;
}
