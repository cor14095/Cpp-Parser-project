#pragma once
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include "Node.h"

using namespace std;

class AST
{
public:

	// Constructor with input vector.
	AST(vector<char> inputVector);
    // AST with an input postfix string.
    AST(string postfix);
	// The AST tree builder.
	stack<Node> doASTree();
private:
	// The input list.
	vector<char> _inputVector;
    // We need a stack to hold the nodes that we will generate.
	stack<Node> _asTree;
};