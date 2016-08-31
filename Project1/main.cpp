#include <iostream>
#include <string>

#include "PostFix.h"

using namespace std;

int main(string Args[]) 
{
	// Some test variables...
	string testChain;

	// Ask the user to set the chain...
	cout << "Ingrese su cadena:\n";
	cin >> testChain;

	// After the user set the chain we bauild the postFix...
	PostFix postFix(testChain);
	cout << " ________The input: ________\n";
	// Then we print the vector...
	for (int i = 0; i < postFix.getTokenVector().size(); i++) {
		cout << "Element " << i + 1 << " is: " << postFix.getTokenVector()[i] << endl;
	}
	// Generate postfix...
	postFix.generatePostFix();
	// Then we print the output vector...
	string chain = "";
	cout << "\n\n ________The resulting postfix string: ________\n";
	for (int i = 0; i < postFix.getOutputVector().size(); i++) {
		cout << postFix.getOutputVector()[i];
		chain += postFix.getOutputVector()[i];
	}
	cout << "\n\n\n";

	cout << "Is the chain valid? \n";
	if (postFix.isValid(chain)) {
		cout << "YES!!!\n\n";
	}
	else
	{
		cout << "no...\n\n";
	}

	system("PAUSE");
	return 0;
}