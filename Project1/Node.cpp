#include "Node.h"
#include <string>


// General constructor, no parameters.
Node::Node() {
	_value = "";
	_level = -1;
	_isLast = false;
}
// Constructor with only value and no level.
Node::Node(string value) {
	_value = value;
	_level = -1;
	_isLast = false;
}
// Constructor with value and level.
Node::Node(string value, int level) {
	_value = value;
	_level = level;
	_isLast = false;
}
// Constructor with value and is last.
Node::Node(string value, bool isLast) {
	_value = value;
	_level = -1;
	_isLast = isLast;
}
// Constructor with all the things, value, level and is last.
Node::Node(string value, int level, bool isLast) {
	_value = value;
	_level = level;
	_isLast = isLast;
}

string Node::toString() {
	return "(" + to_string(_level) + ") " + _value;
}

Node::~Node()
{
}
