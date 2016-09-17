#include "BinTree.h"
#include <string>

#include "Node.h"


// General constructor...
BinTree::BinTree() {
	_mainNode = Node("");
	BinTree *_leftNode;
	BinTree *_rightNode;
}

// Constructor with main node and no left or right
BinTree::BinTree(Node main) {
	_mainNode = main;
	BinTree *_leftNode;
	BinTree *_rightNode;
}

// Contructor with main and left or right node
BinTree::BinTree(Node main, char side, BinTree *node) {
	_mainNode = main;

	switch (tolower(side))
	{
	case 'r':
		_rightNode = node;
		break;
	case 'l':
		_leftNode = node;
		break;
	default:
		cout << "Incorrect input for side, (l)eft or (r)ight.";
		break;
	}
}

// Constructor with all parameters.
BinTree::BinTree(Node main, BinTree *left, BinTree *right) {
	_mainNode = main;
	_leftNode = left;
	_rightNode = right;
}

// To string...
string BinTree::toString() {
	return "(M)" + _mainNode.toString();
}

BinTree::~BinTree()
{
}
