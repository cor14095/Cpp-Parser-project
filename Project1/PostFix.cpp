#include "PostFix.h"
#include <stack>
#include <list>
#include <string>
#include <iterator>
#include <iostream>

// TODO:
// - Add the ? and ε simbols to the postfix...
// - Add the ? and ε simbols to the isValid...
// - Add 1 digit numbers to the postfix and isValid...


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
	for (size_t i = 0; i < _chain.size(); i++) {
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
	string symbolsOrder = "(|.+*";

	// This function return the hierarchy for given symbols
	return symbolsOrder.find(symbol);
}

// This function will insert the operator correctly
void PostFix::insertOperator(char op) {
	try {
		while ( (!_operatorStack.empty()) && (giveHierarchy(op) < giveHierarchy(_operatorStack.top())) ) {
			_outputVector.push_back(_operatorStack.top());	// Add the operator to the outputVector
			_operatorStack.pop();							// Remove the operator from the operatorStack
		}
		_operatorStack.push(op);
	}
	catch (int e) {
		cout << "Error using operators.\nError code: " << e << endl;
		_errorFlag = true;
	}
}

// This function tells me if this character is the last one of the string.
bool isLast(string chain) {
	if (chain.size() <= 1) {
		return true;		// if it's the last character in the chain...
	}

	for (size_t i = 1 ; i < chain.size(); i++) {
		if ( (isalpha(chain.at(i))) || (chain.at(i)=='*') || (chain.at(i)=='+') ) {
			// If there is another aplhabetic character in the chain!
			return false;
		}
	}

	// There was no other alphabetic character in the chain
	return true;
}

// The trick happens here...
void PostFix::generatePostFix() {
	bool signo = false;		// This variable will tell me when 2 tokens have an implicit '&'
	// Test stuff...
	string testChain = "";
	string testStack = "";

	// Main for loop to get all the stuff made...
	for (size_t i = 0; i < _tokenVector.size(); i++) {
		// We need to move inside the vector from left to right...
		
		switch (_tokenVector[i]) {
		case '(' :
			if (signo) {
				insertOperator('.');
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
				if (!_operatorStack.empty()) {
					_operatorStack.pop();
					signo = true;									// Despues de sacar un parentesis, lo que queda es un caracter operado, por eso toca signo.
				}
				else
				{
					cout << "Error using parenthesis at: " << i << endl;
					_errorFlag = true;
				}
			}
			catch (int e) {
				cout << "Error using parenthesis at: " << i << "\n Error code: " << e << endl;
				_errorFlag = true;
			}
			break;
		case '*':
			if (signo) {
				// Sign is needed here...
				_outputVector.push_back('*');					// Just place it inside the string.
				signo = true;									// Since * is unary it produce a character so after it it needs a sign.
			}
			else {
				_errorFlag = true;
				cout << "Error in the string. Char : " << i << endl;
			}
			break;
		case '+':
			if (signo) {
				// Sign is needed here...
				_outputVector.push_back('+');					// Just place it inside the string.
				signo = true;									// Since * is unary it produce a character so after it it needs a sign.
			}
			else {
				_errorFlag = true;
				cout << "Error in the string. Char : " << i << endl;
			}
			break;
		case '|':
			if (signo) {
				// Sign is needed here...
				insertOperator('|');
				signo = false;
			}
			else {
				_errorFlag = true;
				cout << "Error in the string. Char : " << i << endl;
			}
			break;
		case '.':
			if (signo) {
				// Sign is needed here...
				insertOperator('.');
				signo = false;
			}
			else {
				_errorFlag = true;
				cout << "Error in the string. Char : " << i << endl;
			}
			break;
		case '?':
			// Sign is needed here...
			// first we need to push the epsilon to the output chain...
			_outputVector.push_back('E');
				//_outputVector.push_back('ε');
			// Then the | simbol...
			_outputVector.push_back('|');
			break;
		case ' ':
			// Weeeeeeeeee...!!
			break;

		default:
			// Check for alhabetic or digit tokens...
			// || (_tokenVector[i] == 'ε'
			if ( isalpha(_tokenVector[i]) || isdigit(_tokenVector[i])) {
				// if it's an alphabetic token then we check some more stuff...
				if (signo) {
					insertOperator('.');
					signo = false;
				}
				// Here we need to see if the user input a 'ε' or an E.
				// || _tokenVector[i] == 'ε'
				if (_tokenVector[i] == 'E') {
					_outputVector.push_back('E');
				}
				else {
					_outputVector.push_back(_tokenVector[i]);
				}
				if (!isLast(_chain.substr(i, _chain.size() - i))) {
					// If it's not a last letter then it need a sign.
					signo = true;
				}
				else
				{
					signo = false;
				}
			}
			else {
				cout << "Invalid token at: " << i << endl;
				_errorFlag = true;
			}
			break;
		}

		// Error checker
		if (_errorFlag) {
			return;
		}

		/*// Test stuff...													<-------------------------- Start of test stuff!
		testChain = "";
		testStack = ""; 
		for (int j = 0; j < _outputVector.size(); j++) {
			testChain += _outputVector[j];
		}
		for (stack<char> j = _operatorStack; !j.empty(); j.pop()) {
			testStack += "[";
			testStack += j.top();
			testStack += "], ";
		}
		cout << "output: " << testChain << endl;
		cout << "Stack: " << testStack << endl;
		// END TEST															<---------------------------- comment this after test!*/

	}

	// Clean the operatorStack at the end!
	while (!_operatorStack.empty()) {
		_outputVector.push_back(_operatorStack.top());
		_operatorStack.pop();
	}

}

bool PostFix::isValid(string postFix) {
	// Some temp variables just to hold the results...
	stack<char> temp;
	char temp1 = ' ';
	char temp2 = ' ';

	for (size_t i = 0; i < _outputVector.size(); i++) {

		// The 'z' symbol is to represent a VALID expresion.
		switch (_outputVector[i])
		{
		case '*':
			if (!temp.empty()) {	// Check if temp is not empty for the values we need.
				temp1 = temp.top();
				temp.pop();
			}
			// || temp1 == 'ε'
			if (isalpha(temp1) || (isdigit(temp1)) ) {	// Check if temp1 is a valid character
				temp.push('z');
			}
			else					// We don't like error like the user...
			{
				_errorFlag = true;
				// Darn users...
			}
			break;
		case '+':
			if (!temp.empty()) {	// Check if temp is not empty for the values we need.
				temp1 = temp.top();
				temp.pop();
			}
			//|| temp1 == 'ε'
			if (isalpha(temp1) || (isdigit(temp1))) {	// Check if temp1 is a valid character
				temp.push('z');
			}
			else					// We don't like error like the user...
			{
				_errorFlag = true;
				// Darn users...
			}
			break;
		case '.':
			if (!temp.empty()) {	// Check if temp is not empty for the values we need.
				temp1 = temp.top();
				temp.pop();
			}
			if (!temp.empty()) {	// Check if temp is not empty for the values we need.
				temp2 = temp.top();
				temp.pop();
			}
			// || temp1 == 'ε' || temp2 == 'ε'
			if ( (isalpha(temp1) || (isdigit(temp1))) && (isalpha(temp2) || (isdigit(temp2))) ) {	// Check if temp1 and temp 2 are valid character
				temp.push('z');
			}
			else					// We don't like error like the user...
			{
				_errorFlag = true;
				// Darn users...
			}
			break;
		case '|':
			if (!temp.empty()) {	// Check if temp is not empty for the values we need.
				temp1 = temp.top();
				temp.pop();
			}
			if (!temp.empty()) {	// Check if temp is not empty for the values we need.
				temp2 = temp.top();
				temp.pop();
			}
			// || temp1 == 'ε' || temp2 == 'ε'
			if ((isalpha(temp1) || (isdigit(temp1))) && (isalpha(temp2) || (isdigit(temp2)))) {	// Check if temp1 and temp 2 are valid character
				temp.push('z');
			}
			else					// We don't like error like the user...
			{
				_errorFlag = true;
				// Darn users...
			}
			break;

			// NEED TO ADD a '?' check here, no we dont... dumb Perry!

		default:
			// If it's a character
			// Quick fix here, if we check the token vector then it might crash in some cases...
			// NEED TO ADD a 'ε' and numeric check here.
			//  || (_outputVector[i] == 'ε'
			if (isalpha(_outputVector[i]) || isdigit(_outputVector[i])) {
				temp.push(_outputVector[i]);
			}
			else	// If it's not one of the symbols or avalid character, then it's an error and we don't like errors...
			{
				_errorFlag = true;
			}
			break;
		}

		if (_errorFlag) {
			return false;
		}
	}

	if (temp.size() != 1) {
		// There was a mistake!
		return false;
	}
	else
	{
		return true;
	}
}