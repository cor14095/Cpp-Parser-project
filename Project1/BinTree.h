#pragma once
#include <iostream>
#include <string>

#include "Node.h"

/*
<CLASS DESCRIPTION!>
Summary:
- BinTree class is a class to simulate a binary tree with my Node class.

Description:
- BinTree is a class to simulate a binary tree with the Node class to have
  a binary tree well structured and been able to print the tree with a usefull
  toString method, this allow me to see if it's working.

Private Variables:
- Main Node: This is the principal node.
- Left Node: This is the Left node. Returns "" if null.
- Right Nodet: This is the Right node. Returns "" if null.
*/

class BinTree
{
public:
	// General constructor...
	BinTree();
	// Constructor with main node and no left or right
	BinTree(Node main);
	// Contructor with main and left or right node
	BinTree(Node main, char side, BinTree *node);
	// Constructor with all parameters.
	BinTree(Node main, BinTree *left, BinTree *right);

	// Setters...
	void setMain(Node main) { _mainNode = main; };
	void setLeft(BinTree *left) { _leftNode = left; };
	void setRight(BinTree *right) { _rightNode = right; };

	// Getters...
	Node getMain() { return _mainNode; };
	BinTree *getLeft() { return _leftNode; };
	BinTree *getRight() { return _rightNode; };

	// To string...
	string toString();

	~BinTree();
private:
	// Since it's a bin tree it'll have...
	// Main node.
	Node _mainNode;
	// Left node.
	BinTree* _leftNode;
	// Right node.
	BinTree* _rightNode;
};

