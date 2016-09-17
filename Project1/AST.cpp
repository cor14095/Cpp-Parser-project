#include "AST.h"

#include <iostream>
#include <string>
#include <stack>
#include <vector>

#include "BinTree.h"
#include "Node.h"

using namespace std;

// Constructor with input vector.
AST::AST(vector<char> inputVector) {
	_inputVector = inputVector;
}
// AST with an input postfix string.
AST::AST(string postfix) {
	// Make the string a vector, not a big deal BRO.
	for (int i = 0; i < postfix.size(); i++) {
		_inputVector.push_back(postfix[i]);
	}
}
// The AST tree builder.
BinTree AST::doASTree() {
	// since we know that the chain is valid because postFix is really OverPower...
	Node temp1("");
	Node temp2("");
	BinTree tempTree1(Node(""));
	BinTree tempTree2(Node(""));
	BinTree tempTree(Node(""));
	for (int i = 0; i < _inputVector.size(); i++) {
		// We need a switch statement to check every character in the input vector.
		switch (_inputVector[i])
		{
		case '*':
			temp1 = Node("*");
			tempTree = BinTree(temp1, 'l', &_asTree.top());
			_asTree.pop();

			_asTree.push(tempTree);
			break;
		case '+':
			temp1 = Node("+");
			tempTree = BinTree(temp1, 'l', &_asTree.top());
			_asTree.pop();

			_asTree.push(tempTree);
			break;
		case '|':
			temp1 = Node("|");

			tempTree1 = _asTree.top();
			_asTree.pop();

			tempTree2 = _asTree.top();
			_asTree.pop();

			tempTree = BinTree(temp1, &tempTree1, &tempTree2);
			_asTree.push(tempTree);
			break;
		case '.':
			temp1 = Node(".");

			tempTree1 = _asTree.top();
			_asTree.pop();

			tempTree2 = _asTree.top();
			_asTree.pop();

			tempTree = BinTree(temp1, &tempTree1, &tempTree2);
			_asTree.push(tempTree);
			break;
		case 'E':
			// Change E for epsilon.
			temp1 = Node(to_string('ε'), true);
			tempTree = BinTree(temp1);
			_asTree.push(tempTree);
			break;
		default:
			// Default means that I have a Character.
			temp1 = Node(to_string(_inputVector[i]), true);
			tempTree = BinTree( temp1 );
			_asTree.push(tempTree);
			break;
		}
	}

	return tempTree;
}