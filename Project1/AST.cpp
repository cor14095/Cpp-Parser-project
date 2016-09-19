#include "AST.h"

#include <iostream>
#include <string>
#include <stack>
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
	stack<BinTree*> treesStack;
	BinTree *tempTree1 = new BinTree();
	BinTree *tempTree2 = new BinTree();

	// since we know that the chain is valid because postFix is really OverPower...
	for (size_t i = 0; i < _inputVector.size(); i++) {
		// We need a switch statement to check every character in the input vector.
		switch (_inputVector[i])
		{
		case '*':
			// Since it's a binary operator, we just need 1 top...
			tempTree1 = new BinTree(treesStack.top()->getMain()
				, treesStack.top()->getLeft()
				, treesStack.top()->getRight());
			treesStack.pop();

			treesStack.push(&*new BinTree());
			treesStack.top()->setMain(*new Node('*'));
			treesStack.top()->setLeft(tempTree1);
			break;
		case '+':
			// Since it's a binary operator, we just need 1 top...
			tempTree1 = new BinTree(treesStack.top()->getMain()
				, treesStack.top()->getLeft()
				, treesStack.top()->getRight());
			treesStack.pop();

			treesStack.push(&*new BinTree());
			treesStack.top()->setMain(*new Node('+'));
			treesStack.top()->setLeft(tempTree1);
			break;
		case '|':
			// Since it's a binary operator, we just need 1 top...
			tempTree1 = new BinTree(treesStack.top()->getMain()
				, treesStack.top()->getLeft()
				, treesStack.top()->getRight());
			treesStack.pop();

			tempTree2 = new BinTree(treesStack.top()->getMain()
				, treesStack.top()->getLeft()
				, treesStack.top()->getRight());
			treesStack.pop();

			treesStack.push(&*new BinTree());
			treesStack.top()->setMain(*new Node('|'));
			treesStack.top()->setLeft(tempTree1);
			treesStack.top()->setRight(tempTree2);
			break;
		case '.':
			// Since it's a binary operator, we just need 1 top...
			tempTree1 = new BinTree(treesStack.top()->getMain()
				, treesStack.top()->getLeft()
				, treesStack.top()->getRight());
			treesStack.pop();

			tempTree2 = new BinTree(treesStack.top()->getMain()
				, treesStack.top()->getLeft()
				, treesStack.top()->getRight());
			treesStack.pop();

			treesStack.push(&*new BinTree());
			treesStack.top()->setMain(*new Node('.'));
			treesStack.top()->setLeft(tempTree1);
			treesStack.top()->setRight(tempTree2);
			break;
		default:
			// Default means that I have a Character.
			treesStack.push(&*new BinTree(*new Node(_inputVector[i], true)));
			break;
		}

	}


	return *treesStack.top();
}