#pragma once
#include <iostream>

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
};

