#pragma once
#include <iostream>
#include <string>
#include <stack>
#include <vector>

#include "BinTree.h"
#include "Node.h"

using namespace std;

/*
<CLASS DESCRIPTION!>
Summary:
- AST class is a class to build an Abstract Syntax Tree base on a Postfix entry.

Description:
- AST class will build a binary tree based on a correct postfix entry, this class
  is always asuming that you give it a CORRECT postfix, there're no validations 
  for any other posible case.

Private Variables:
- Input vector: A string to hold the postfix chain.
- As tree: a Stack of BinTrees to hold the tree's while building them.
*/

class AST
{
public:

    // AST with an input postfix string.
    AST(string postfix);
	// The AST tree builder.
	BinTree doASTree();
private:
	// The input list.
	string _inputVector;
    // We need a stack to hold the nodes that we will generate.
	stack<BinTree> _asTree;
};