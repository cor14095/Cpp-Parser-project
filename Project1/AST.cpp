#include "AST.h"

#include <iostream>
#include <string>
#include <list>
#include <vector>

#include "BinTree.h"
#include "Node.h"

using namespace std;

// AST with an input postfix string.
AST::AST(string postfix) {
	// Make the string a vector, not a big deal BRO.
	_inputVector = postfix;
}
// The AST tree builder.
BinTree AST::doASTree() {
	// Some variables...
	list<BinTree*> treesStack;
	BinTree *tempTree1 = new BinTree();
	BinTree *tempTree2 = new BinTree();
	Node tempNode = *new Node();

	// since we know that the chain is valid because postFix is really OverPower...
	for (size_t i = 0; i < _inputVector.size(); i++) {
		// We need a switch statement to check every character in the input vector.
		switch (_inputVector[i])
		{
		case '*':
			// Since it's a binary operator, we just need 1 top...
			tempTree1 = new BinTree(treesStack.front()->getMain()
				, treesStack.front()->getLeft()
				, treesStack.front()->getRight());
			treesStack.pop_front();

			treesStack.push_front(&*new BinTree());
			tempNode = *new Node('*');
			treesStack.front()->setMain(tempNode);
			treesStack.front()->setLeft(tempTree1);
			break;
		case '+':
			tempTree1 = new BinTree(treesStack.front()->getMain()
				, treesStack.front()->getLeft()
				, treesStack.front()->getRight());
			treesStack.pop_front();

			treesStack.push_front(&*new BinTree());
			tempNode = *new Node('+');
			treesStack.front()->setMain(tempNode);
			treesStack.front()->setLeft(tempTree1);
			break;
		case '|':
			// Since it's a binary operator, we just need 1 top...
			tempTree1 = new BinTree(treesStack.front()->getMain()
				, treesStack.front()->getLeft()
				, treesStack.front()->getRight());
			treesStack.pop_front();

			tempTree2 = new BinTree(treesStack.front()->getMain()
				, treesStack.front()->getLeft()
				, treesStack.front()->getRight());
			treesStack.pop_front();

			treesStack.push_front(&*new BinTree());
			tempNode = *new Node('|');
			treesStack.front()->setMain(tempNode);
			treesStack.front()->setLeft(tempTree1);
			treesStack.front()->setRight(tempTree2);
			break;
		case '.':
			// Since it's a binary operator, we just need 1 top...
			tempTree1 = new BinTree(treesStack.front()->getMain()
				, treesStack.front()->getLeft()
				, treesStack.front()->getRight());
			treesStack.pop_front();

			tempTree2 = new BinTree(treesStack.front()->getMain()
				, treesStack.front()->getLeft()
				, treesStack.front()->getRight());
			treesStack.pop_front();

			treesStack.push_front(&*new BinTree());
			tempNode = *new Node('.');
			treesStack.front()->setMain(tempNode);
			treesStack.front()->setLeft(tempTree1);
			treesStack.front()->setRight(tempTree2);
			break;
		default:
			// Default means that I have a Character.
			tempNode = *new Node(_inputVector[i], true);
			treesStack.push_back(&*new BinTree());
			treesStack.back()->setMain(tempNode);
			break;
		}

	}

	// I need to add the stop simbol.
	// Since it's a binary operator, we just need 1 top...
	tempTree1 = new BinTree(treesStack.front()->getMain()
		, treesStack.front()->getLeft()
		, treesStack.front()->getRight());
	treesStack.pop_front();

	tempNode = *new Node('#', true);
	tempTree2 = new BinTree();
	tempTree2->setMain(tempNode);

	treesStack.push_front(&*new BinTree());
	tempNode = *new Node('.');
	treesStack.front()->setMain(tempNode);
	treesStack.front()->setLeft(tempTree1);
	treesStack.front()->setRight(tempTree2);
	
	return *treesStack.front();
}