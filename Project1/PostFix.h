//#pragma once
#include <string>
#include <stack> 
#include <vector>

using namespace std;

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

