#pragma once
#include <iostream>
#include <list>
#include <string>

#include "BinTree.h"
#include "State.h"

using namespace std;

/*
<CLASS DESCRIPTION!>
Summary:
- Graph class with bi a graph handler with some usefull algorithms.

Description:
- Graph class is a graph handler that will include:
-- Thompson's construction algorith for NFA.
-- Subsets construction for NFA to AFD.
-- AST to AFD.

Private Variables:
- Start state: The start state for the graph.
- End states: A Stack of end Nodes, just in case.
- States: A list with states.
- Simbols: A list with simbols.
- Transitions: A stack of transitions.
*/

class Graph
{
public:
	// General constructor.
	Graph();

	// General destructor.
	~Graph();

	// Setters...
	void setStates(list<State> states) { _states = states; };
	void setSimbols(list<char> simbols) { _simbols = simbols; };
	void setTransitions(list<State::Transition> transitions) { _transitions = transitions; };
	void setStart(State start) { _startState = start; };
	void setEnds(list<State> endStates) { _endStates = endStates; };

	// Getters...
	list<State> getStates() { return _states; };
	list<char> getSimbols() { return _simbols; };
	list<State::Transition> getTransitions() { return _transitions; };
	State getStart() { return _startState; };
	list<State> getEnds() { return _endStates; };

	// Main functions to be called from main program.
	// Make an NFA with Thompson's contrusction.
	Graph makeNFA(string expression);



private:
	// List of all states.
	list<State> _states;
	// List of all simbols.
	list<char> _simbols;
	// A list for all the transitions.
	list<State::Transition> _transitions;
	// The first state.
	State _startState;
	// List of all end states.
	list<State> _endStates;

};

