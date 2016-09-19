#pragma once
#include <iostream>
#include <vector>
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
	//This makles a graph.
	Graph(int name, char simbol);
	// Constructor with all parameters.
	Graph(vector<State*> states, vector<char*> simbols, vector<State::Transition*> transitions, State *startState, State *_endStates);

	// General destructor.
	~Graph();

	// Setters...
	void setStates(vector<State*> states) { _states = states; };
	void setSimbols(vector<char*> simbols) { _simbols = simbols; };
	void setTransitions(vector<State::Transition*> transitions) { _transitions = transitions; };
	void setStart(State *start) { _startState = start; };
	void setEnd(State *endStates) { _endState = endStates; };

	// Getters...
	vector<State*> getStates() { return _states; };
	vector<char*> getSimbols() { return _simbols; };
	vector<State::Transition*> getTransitions() { return _transitions; };
	State *getStart() { return _startState; };
	State *getEnd() { return _endState; };

	// Main functions to be called from main program.
	void addState(State *state) { _states.push_back(state); };
	// Make an NFA with Thompson's contrusction.
	Graph makeNFA(string expression);

private:
	// List of all states.
	vector<State*> _states;
	// List of all simbols.
	vector<char*> _simbols;
	// A list for all the transitions.
	vector<State::Transition*> _transitions;
	// The first state.
	State *_startState;
	// List of all end states.
	State *_endState;

};

