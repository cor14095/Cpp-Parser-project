#include <iostream>
#include <string>

#include "PostFix.h"
#include "AST.h"
#include "BinTree.h"
#include "Graph.h"

using namespace std;

int main() 
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
	for (size_t i = 0; i < postFix.getTokenVector().size(); i++) {
		cout << "Element " << i + 1 << " is: " << postFix.getTokenVector()[i] << endl;
	}
	// Generate postfix...
	postFix.generatePostFix();
	// Then we print the output vector...
	string chain = "";
	cout << "\n\n ________The resulting postfix string: ________\n";
	for (size_t i = 0; i < postFix.getOutputVector().size(); i++) {
		cout << postFix.getOutputVector()[i];
		chain += postFix.getOutputVector()[i];
	}
	cout << "\n\n\n";

	cout << "Is the chain valid? \n";
	if (postFix.isValid(chain)) {
		cout << "YES!!!\n\n";
		cout << "\n\nGenerate the AST:" << endl;
		AST myAST(chain);

		BinTree asTree = myAST.doASTree();
		string chain2 = " ";
		//chain2 = asTree.printTree(chain2);
		//reverse(chain2.begin(), chain2.end());

		cout << "Chain is: " << chain2 << endl;

		Graph *nfa = new Graph();
		string nameNFA = "NFA";
		nfa = nfa->makeNFA(chain);
		nfa->asFile(*nfa, nameNFA, 0);
		cout << "\n\nEl archivo del NFA se creo con exito!\n\nProbemos el AFN:\n" << endl;

		string simulation = "Perry";
		while (true) {
			cout << "Ingrese la cadena que desea probar, 'Salir' para terminar\n" << endl;
			cin >> simulation;

			if (simulation.compare("Salir") == 0) {
				break;
			}

			if (nfa->simulateNFA(nfa, simulation)) {
				cout << "La cadena es valida.\n" << endl;
			}
			else {
				cout << "La cadena no es valida.\n" << endl;
			}
		}

		Graph *DFA = new Graph();
		DFA = nfa->NFAtoDFA(nfa);
		string nameDFA = "DFA";
		DFA->asFile(*DFA, nameDFA, 1);
		cout << "\n\nEl archivo del AFD se creo con exito!\n\nProbemos el AFD:\n" << endl;
		simulation = "Perry";
		while (true) {
			cout << "Ingrese la cadena que desea probar, 'Salir' para terminar\n" << endl;
			cin >> simulation;

			if (simulation.compare("Salir") == 0) {
				break;
			}

			if (DFA->simulateDFA(DFA, simulation)) {
				cout << "La cadena es valida.\n" << endl;
			}
			else {
				cout << "La cadena no es valida.\n" << endl;
			}
		}
	}
	else
	{
		cout << "no...\n\n";
	}
	return 0;
}