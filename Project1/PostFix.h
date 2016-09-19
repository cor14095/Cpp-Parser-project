#pragma once
#include <string>
#include <stack> 
#include <vector>

using namespace std;

/*
<CLASS DESCRIPTION!>
Summary:
- Postfix class recibe a string and converts it to postfix order.

Description:
- Postfix class wil ONLY WORK for regular expresion following this:
-- * : Klin Operator.
-- + : Klin without 0.
-- . : AND.
-- | : OR.
-- ? : Epsilon or any character(a|E).
-- E : Epsilon.
-- Any alphanumeric character as valid characters, only 1 digit numbers.

Private Variables:
- Operator stack: Is a stack to hold the operators.
- Chain: Input argumet for expresion.
- Token vector: A vector to hold the input chain as a vector.
- Output vector: The vector with the chain in postfix order.
- Error flag: Flag to point if there was an error in the postfix.
*/

class PostFix
{
public:
	
	// Basic constructor
	PostFix();
	// Constructor to get a string
	PostFix(string chain);

	// Basic destructor
	~PostFix();

	// Setters...
	void setOperatorStack(stack<char> operatorStack);
	void setChain(string chain);
	void setTokenVector(vector<char> tokenList);
	void setoutputVector(vector<char> outputList);
	void setErrorFlag(bool errorFlag);

	// Getters...
	stack<char> getOperatorStack();
	string getChain();
	vector<char> getTokenVector();
	vector<char> getOutputVector();
	bool getErrorFlag();

	// This function is intended to give hierarchy to the operators
	int giveHierarchy(char symbol);

	// This function will insert the operator correctly
	void insertOperator(char op);

	// Let's do some magic kids!
	void generatePostFix();

	// Here we just evaluate that the expresion is fully correct.
	bool isValid(string postFix);

private:
	
	// The stack used to hold the operators
	stack<char> _operatorStack;
	// The main input argument
	string _chain;
	// The list to read
	vector<char> _tokenVector;
	// The output list
	vector<char> _outputVector;
	// Error flag, just in case useIsDumb == true
	bool _errorFlag;
};

