#include "BinTree.h"
#include <string>
#include <iostream>

#include "Node.h"


// General constructor...
BinTree::BinTree() {
	_mainNode = *new Node();
	BinTree *_leftNode = NULL;
	BinTree *_rightNode = NULL;
	_size = 0;
}

// Constructor with main node and no left or right
BinTree::BinTree(Node main) {
	_mainNode = main;
	BinTree *_leftNode = NULL;
	BinTree *_rightNode = NULL;
}

// Contructor with main and left or right node
BinTree::BinTree(Node main, char side, BinTree *node) {
	_mainNode = main;

	switch (tolower(side))
	{
	case 'r':
		_rightNode = node;
		_leftNode = NULL;
		break;
	case 'l':
		_leftNode = node;
		_rightNode = NULL;
		break;
	default:
		cout << "Incorrect input for side, (l)eft or (r)ight.";
		break;
	}
	_size = 0;
}

// Constructor with all parameters.
BinTree::BinTree(Node main, BinTree *left, BinTree *right) {
	_mainNode = main;
	_leftNode = left;
	_rightNode = right;
	_size = 0;
}

// Constructor with main node and no left or right
BinTree::BinTree(Node *main) {
	_mainNode = *main;
	BinTree *_leftNode = NULL;
	BinTree *_rightNode = NULL;
	_size = 0;
}

// Contructor with main and left or right node
BinTree::BinTree(Node *main, char side, BinTree *node) {
	_mainNode = *main;

	switch (tolower(side))
	{
	case 'r':
		_rightNode = node;
		_leftNode = NULL;
		break;
	case 'l':
		_leftNode = node;
		_rightNode = NULL;
		break;
	default:
		cout << "Incorrect input for side, (l)eft or (r)ight.";
		break;
	}
	_size = 0;
}

// Constructor with all parameters.
BinTree::BinTree(Node *main, BinTree *left, BinTree *right) {
	_mainNode = *main;
	_leftNode = left;
	_rightNode = right;
	_size = 0;
}

// Constructor with all parameters.
BinTree::BinTree(Node main, BinTree left, BinTree right) {
	_mainNode = main;
	_leftNode = &left;
	_rightNode = &right;
	_size = 0;
}

// To string...
string BinTree::printTree(string &chain) {
	if (_mainNode.getValue() == '#') {
		chain += '#';
		return chain;
	}
	else {
		if (_leftNode != NULL) {
			_leftNode->printTree(chain);
		}
		chain += _mainNode.getValue();
		if (_rightNode != NULL) {
			_rightNode -> printTree(chain);
		}
		
		return chain;
	}
}

BinTree::~BinTree()
{
}
