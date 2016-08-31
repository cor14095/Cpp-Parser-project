#include "PostFix.h"
#include <stack>
#include <list>
#include <string>
#include <iterator>
#include <iostream>


// Basic constructor for PostFix class.
PostFix::PostFix()
{
	// Just set some values
	_chain = "";
	_errorFlag = false;
}

// Constructor with chain as parameter
PostFix::PostFix(string chain)
{
	// First we recive our chain to make postfix
	_chain = chain;
	// This falg is to check if user did something wrong...
	_errorFlag = false;
	// We need to split our chain and store it in a vector.
	for (int i = 0; i < _chain.size(); i++) {
		_tokenVector.push_back(_chain.at(i));
	}

	// Now we're ready to go...
}

// Basic destructor for PostFix class.
PostFix::~PostFix()
{

}

// Setters...
void PostFix::setOperatorStack(stack<char> operatorStack) {
	_operatorStack = operatorStack;
}
void PostFix::setChain(string chain) {
	_chain = chain;
}
void PostFix::setTokenVector(vector<char> tokenList) {
	_tokenVector = tokenList;
}
void PostFix::setoutputVector(vector<char> outputList) {
	_outputVector = outputList;
}
void PostFix::setErrorFlag(bool errorFlag) {
	_errorFlag = errorFlag;
}

// Getters...
stack<char> PostFix::getOperatorStack() {
	return _operatorStack;
}
string PostFix::getChain() {
	return _chain;
}
vector<char> PostFix::getTokenVector() {
	return _tokenVector;
}
vector<char> PostFix::getOutputVector() {
	return _outputVector;
}
bool PostFix::getErrorFlag() {
	return _errorFlag;
}

// This function is intended to give hierarchy to the operators
int PostFix::giveHierarchy(char symbol) {
	string symbolsOrder = "|&(+*";

	// This function return the hierarchy for given symbols
	return symbolsOrder.find(symbol);
}

// This function will insert the operator correctly
void PostFix::insertOperator(char op) {
	try {
		while ( (!_operatorStack.empty()) && (giveHierarchy('*') > giveHierarchy(_operatorStack.top())) ) {
			_outputVector.push_back(_operatorStack.top());	// Add the operator to the outputVector
			_operatorStack.pop();							// Remove the operator from the operatorStack
		}
		_operatorStack.push(op);
	}
	catch (int e) {
		cout << "Error using operators.\n";
		_errorFlag = true;
	}
}

// The trick happens here...
void PostFix::generatePostFix() {
	bool signo = false;		// This variable will tell me when 2 tokens have an implicit '&'
	// Main for loop to get all the stuff made...
	for (int i = 0; i < _tokenVector.size(); i++) {
		// We need to move inside the vector from left to right...
		
		switch (_tokenVector[i]) {
		case '(' :
			if (signo) {
				insertOperator('&');
				signo = false;
			}
			_operatorStack.push(_tokenVector[i]);
			break;
		case ')':
			try {
				while ( (!_operatorStack.empty()) && (_operatorStack.top() != '(')) {
					_outputVector.push_back(_operatorStack.top());	// Add the operator to the outputVector
					_operatorStack.pop();							// Remove the operator from the operatorStack
				}
				_operatorStack.pop();
			}
			catch (int e) {
				cout << "Error using parenthesis.\n";
				_errorFlag = true;
			}
			break;
		case '*':
			if (signo) {
				// Sign is needed here...
				_operatorStack.push('*');
				signo = false;
			}
			else {
				_errorFlag = true;
				cout << "Error in the string. Char : " << i << endl;
			}
			break;
		case '+':
			if (signo) {
				// Sign is needed here...
				_operatorStack.push('+');
				signo = false;
			}
			else {
				_errorFlag = true;
				cout << "Error in the string. Char : " << i << endl;
			}
			break;
		case '|':
			if (signo) {
				// Sign is needed here...
				_operatorStack.push('|');
				signo = false;
			}
			else {
				_errorFlag = true;
				cout << "Error in the string. Char : " << i << endl;
			}
			break;
		case '&':
			if (signo) {
				// Sign is needed here...
				_operatorStack.push('&');
				signo = false;
			}
			else {
				_errorFlag = true;
				cout << "Error in the string. Char : " << i << endl;
			}
			break;
		case ' ':
			// Weeeeeeeeee...!!
			break;
		default:
			// Check for alhabetic tokens...
			if ( isalpha(_tokenVector[i]) ) {
				// if it's an alphabetic token then we check some more stuff...
				if (signo) {
					insertOperator('&');
				}
				_outputVector.push_back(_tokenVector[i]);
				signo = true;
			}
			else {
				cout << "Invalid token at: " << i << endl;
				_errorFlag = true;
			}
		}

		// Error checker
		if (_errorFlag) {
			return;
		}

	}

	// Clean the operatorStack at the end!
	while (!_operatorStack.empty()) {
		_outputVector.push_back(_operatorStack.top());
		_operatorStack.pop();
	}

}