#include "Node.h"
#include <string>


// General constructor, no parameters.
Node::Node() {
	_value = ' ';
	_level = -1;
	_isLast = false;
}
// Constructor with only value and no level.
Node::Node(char value) {
	_value = value;
	_level = -1;
	_isLast = false;
}
// Constructor with value and level.
Node::Node(char value, int level) {
	_value = value;
	_level = level;
	_isLast = false;
}
// Constructor with value and is last.
Node::Node(char value, bool isLast) {
	_value = value;
	_level = -1;
	_isLast = isLast;
}
// Constructor with all the things, value, level and is last.
Node::Node(char value, int level, bool isLast) {
	_value = value;
	_level = level;
	_isLast = isLast;
}

string Node::toString() {
	return "Value: " + string(1, _value) + "\nLevel: " + to_string(_level) + "\n";
}

Node::~Node()
{
}
