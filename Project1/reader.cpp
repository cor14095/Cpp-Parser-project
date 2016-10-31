#include "reader.h"
#include <iostream>
#include <string>
#include <map>
#include <fstream>

using namespace std;

// This function returns a percentage of similarity for 2 strings base on a simple algorithm.
float compareStrings(string word, string compareTo) {
	float percentage = 0;

	if (size(word) <= size(compareTo)) {
		for (size_t i = 0; i < size(word); i++) {
			if (word[i] == compareTo[i]) {
				percentage++;
			}
		}

		percentage = (percentage * 100) / size(compareTo);

	}
	else {
		for (size_t i = 0; i < size(compareTo); i++) {
			if (word[i] == compareTo[i]) {
				percentage++;
			}
		}

		percentage = (percentage * 100) / size(word);

	}

	return percentage;

}

reader::reader() 
{
	// First we create the map.
	tokens["letter"] = "a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z";

	// Then we make some usefull variable...
	string line;
	string ident, expression;
	char buffer[20];
	ifstream myFile ("read.txt");
	ofstream outFile;
	int lineCount = 0;

	// Validating the file open.
	if (myFile.is_open()) {
		// Reading the file line by line
		while (getline(myFile, line)) {
			// we read a line.
			lineCount++;
			ident = "";
			expression = "";

			// The first line must be "COMPILER [name]"
			if (lineCount == 1) {
				// First we get the COMPILER word.
				size_t length = line.copy(buffer, 8, 0);
				for (size_t i = 0; i < length; i++) {
					ident += line[i];
				}
				// Then we get the [name].
				for (size_t i = length + 1; i < size(line); i++) {
					expression += line[i];
				}
				// Now we have to check if they are both correct.
				if (compareStrings(ident, "COMPILER") == 100) {
					outFile.open(expression + ".txt");
				}
				else {
					cout << "WARNING: You might wanna check your syntax on line: " << lineCount << endl;
					outFile.open(expression + ".txt");
				}
			}

		}
	}

}