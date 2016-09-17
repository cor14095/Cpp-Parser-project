#include "Node.h"


// General constructor...
Node::Node()
{
	_value = "";
	Node *_left;
	Node *_right;
}
// Constructor with only value.
Node::Node(string value) {
	_value = value;
	Node *_left;
	Node *_right;
}
// Constructor with value and one pointer.
Node::Node(string value, Node* point) {
	_value = value;
	_left = point;
	Node *_right;
}

// Constructor with all.
Node::Node(string value, Node* left, Node* right) {
	_value = value;
	_left = left;
	_right = right;
}

// My toString for node
string Node::toString() {
	string chain = " ";	
	chain += '(' + _value + ')';
	chain += '\n';
	return chain;
}

Node::~Node()
{
}
