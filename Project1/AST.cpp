#include "AST.h"

#include <iostream>
#include <string>
#include <stack>
#include <vector>

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
stack<Node> AST::doASTree() {
	// since we know that the chain is valid because postFix is really OverPower...
	Node temp1( " " );
	Node temp2( " " );
	for (int i = 0; i < _inputVector.size(); i++) {
		// We need a switch statement to check every character in the input vector.
		switch (_inputVector[i])
		{
		case '*':
			// For unary operators we first make a temporal node
			// With value of the operator, and pointing to the character it will afect.
			temp1 = Node(string(1, '*'), &_asTree.top());
			_asTree.pop();
			// After taking the element of the stack, we place the temp node in the stack as the new element.
			_asTree.push(temp1);
			break;
		case '+':
			// For unary operators we first make a temporal node
			// With value of the operator, and pointing to the character it will afect.
			temp1 = Node(string(1, '+'), &_asTree.top());
			_asTree.pop();
			// After taking the element of the stack, we place the temp node in the stack as the new element.
			_asTree.push(temp1);
			break;
		case '|':
			// For binary operators we first get the element at the top of the stack
			// and save it at temp1, then we take it out of the stack.
			temp1 = _asTree.top();
			_asTree.pop();
			// Then we create a new temp Node with both left and right pointers.
			// befor pushing temp2, we must clean the top.
			temp2 = Node(string(1, '|'), &temp1, &_asTree.top());
			_asTree.pop();
			// After taking the element of the stack, we place the new node temp2 at the top.
			_asTree.push(temp2);
			break;
		case '.':
			// For binary operators we first get the element at the top of the stack
			// and save it at temp1, then we take it out of the stack.
			temp1 = _asTree.top();
			_asTree.pop();
			// Then we create a new temp Node with both left and right pointers.
			// befor pushing temp2, we must clean the top.
			temp2 = Node(string(1, '.'), &temp1, &_asTree.top());
			_asTree.pop();
			// After taking the element of the stack, we place the new node temp2 at the top.
			_asTree.push(temp2);

			break;
		case 'E':
			// If we find an epsilon then we must change its symbol to the real epsilon...
			temp1 = Node(string(1, 'ε'));
			_asTree.push(temp1);
			break;
		default:
			// Default means that I have a Character.
			temp1 = Node( string(1, _inputVector[i]) );
			_asTree.push(temp1);
			break;
		}
	}

	return _asTree;
}