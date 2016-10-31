#pragma once

#include <iostream>
#include <string>

using namespace std;

/*
<CLASS DESCRIPTION!>
Summary:
- reader class is for the solid purpose of reading the .

Description:
- AST class will build a binary tree based on a correct postfix entry, this class
is always asuming that you give it a CORRECT postfix, there're no validations
for any other posible case.

Private Variables:
- Input vector: A string to hold the postfix chain.
- As tree: a Stack of BinTrees to hold the tree's while building them.
*/

class reader
{
public:
	// General constructor.
	reader();
	

private:
	map <string, string> tokens;
};
