#pragma once
#include <iostream>
#include <string>

using namespace std;

class Node
{
public:
	// General constructor, no parameters.
	Node();
	// Constructor with only value.
	Node(string value);
	// Constructor with value and one pointer.
	Node(string value, Node* point);
	// Constructor with all.
	Node(string value, Node* left, Node* right);

	// General destructor.
	~Node();

	// toString
	string toString();

	// Setters and getters for the node pointers...
	void setValue(string value) { _value = value; };
	void setLeft(Node* left) { _left = left; };
	void setRight(Node* right) { _right = right; };

	string getValue() { return _value; };
	Node *getLeft() { return _left; };
	Node *getRight() { return _right; };

private:
	string _value;
	Node* _left;
	Node* _right;
};

