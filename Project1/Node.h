#pragma once
#include <iostream>
#include <string>

using namespace std;

/*
<CLASS DESCRIPTION!>
Summary:
- Node class is just a container with some useful parameter

Description:
- Node is a class that will contain a string value, a level for the graph and tree
  and a flag to know if it's final or a leaf in respective cases. So it's just a 
  simple yet really useful class for BinTree, AST and any graph made.

Private Variables:
- Value: This is a string to store the token. If value is "" then it's NULL
- Level: This is a integer to store the level of the tree or the graph level. Return -1 if none is given or calculated.
- Is Last: This is a boolean to store if the node is a leaf or a final node in a graph. Set to false as default.
*/

class Node
{
public:
	// General constructor, no parameters.
	Node();
	// Constructor with only value and no level.
	Node(char value);
	// Constructor with value and level.
	Node(char value, int level);
	// Constructor with value and is last.
	Node(char value, bool isLast);
	// Constructor with all the things, value, level and is last.
	Node(char value, int level, bool isLast);

	// General destructor.
	~Node();

	//Setters...
	void setValue(char value) { _value = value; };
	void setLevel(int level) { _level = level; };

	// Getters...
	char getValue() { return _value; };

	// toString
	string toString();


private:
	// The value in the node
	char _value;
	// The level of the node
	int _level;
	// A flag to know if this node is last or not.
	bool _isLast;
};

