#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <stack>
#include <array>
#include <string>

#include "State.h"
#include "Graph.h"

using namespace std;

// General constructor.
Graph::Graph() {
	vector<State*> _states = *new vector<State*>();
	vector<char*> _simbols = *new vector<char*>();
	vector<State::Transition*> _transitions = *new vector<State::Transition*>();
	State *_startState = new State();
	State *_endStates = new State();
}

// Constructor with all parameters.
Graph::Graph(vector<State*> states, vector<char> simbols, vector<State::Transition*> transitions, State *startState, State *endState) {
	_states = states;
	_simbols = simbols;
	_transitions = transitions;
	_startState = startState;
	_endState = endState;
}

// General destructor.
Graph::~Graph()
{

}

// This function will build a NFA based on a regular expresion
// in postFix order, using Thompson's construction algorithm.
Graph *Graph::makeNFA(string expression) {
	// Some useful variables.
	char epsilon = 'E';
	vector<State*> states = *new vector<State*>();
	vector<State*> cStates1 = *new vector<State*>();
	vector<State*> cStates2 = *new vector<State*>();
	vector<char> simbols = *new vector<char>();
	vector<State::Transition*> transitions = *new vector<State::Transition*>();
	vector<State::Transition*> copy1 = *new vector<State::Transition*>();
	vector<State::Transition*> copy2 = *new vector<State::Transition*>();
	vector<State::Transition*> copy3 = *new vector<State::Transition*>();
	State::Transition *t11 = new State::Transition();
	State::Transition *t12 = new State::Transition();
	State::Transition *t21 = new State::Transition();
	State::Transition *t22 = new State::Transition();
	State *startState = new State();
	State *endState = new State();
	State *tState1 = new State();
	State *tState2 = new State();
	int endName = 0;
	int startName = 0;

	stack<Graph*> subGraphs = *new stack<Graph*>();
	Graph *tempGraph1 = new Graph();
	Graph *tempGraph2 = new Graph();
	int numberOfStates = 0;

	Graph* NFA;
	// From the postFix we made, we know that the expression is valid.
	for (size_t i = 0; i < expression.size(); i++) {
		// We use a switch to check term by term.
		switch (expression[i])
		{
		case '*':
			// Since Klin is a unary operator we just need to get the top element in the stack. and add 2 transitions, from begining to end(s) and end(s) to begining.
			// First we need to pop the stack.
			tempGraph1 = new Graph();
			tempGraph1->setEnd(subGraphs.top()->getEnd());
			tempGraph1->setStart(subGraphs.top()->getStart());
			tempGraph1->setStates(subGraphs.top()->getStates());
			tempGraph1->setTransitions(subGraphs.top()->getTransitions());
			subGraphs.pop();
			// Then we create our temporary states.
			subGraphs.push(&*new Graph());
			states = *new vector<State*>();
			transitions = *new vector<State::Transition*>();
			numberOfStates++;
			// First create the states.
			tState1 = new State();			// New Start.
			startName = numberOfStates;
			tState1->setName(startName);
			tState2 = new State();			// New End.
			numberOfStates++;
			endName = numberOfStates;
			tState2->setIsFinal(true);
			tState2->setName(endName);
			// Then create transitions.
			t11 = new State::Transition(epsilon, tempGraph1->getStart());	// From new start to old start.
			t12 = new State::Transition(epsilon, tState2);					// From new start to new end.
			t21 = new State::Transition(epsilon, tState2);					// From old end to new end.
			t22 = new State::Transition(epsilon, tempGraph1->getStart());	// From old end to old start.
			// Now we have the states and transitions, we need to add them to the other states.
			tState1->addTransition(t11);
			tState1->addTransition(t12);
			tempGraph1->getEnd()->addTransition(t21);
			tempGraph1->getEnd()->addTransition(t22);
			// Now change end points.
			tempGraph1->getEnd()->setIsFinal(false);
			// No make the transitions vector.
			copy1 = tempGraph1->getTransitions();
			copy2 = tState1->getTransitions();
			cStates1 = tempGraph1->getStates();
			// Create the transitions vector.
			transitions.reserve(copy1.size() + copy2.size() + 2);
			transitions.insert(transitions.end(), copy2.begin(), copy2.end());
			transitions.insert(transitions.end(), copy1.begin(), copy1.end());
			transitions.insert(transitions.end(), t21);
			transitions.insert(transitions.end(), t22);
			// Create the vector of states.
			states.reserve(cStates1.size() + 2);
			states.insert(states.end(), tState1);
			states.insert(states.end(), cStates1.begin(), cStates1.end());
			states.insert(states.end(), tState2);
			// Then we just get everything in the stack.
			subGraphs.top()->setStart(tState1);
			subGraphs.top()->setEnd(tState2);
			subGraphs.top()->setStates(states);
			subGraphs.top()->setTransitions(transitions);

			break;
		case '+':
			// Since + is a unary operator we just need to get the top element in the stack. and add 1 transition, from end(s) to beginings.
			// First we need to pop the stack.
			tempGraph1 = new Graph();
			tempGraph1->setEnd(subGraphs.top()->getEnd());
			tempGraph1->setStart(subGraphs.top()->getStart());
			tempGraph1->setStates(subGraphs.top()->getStates());
			tempGraph1->setTransitions(subGraphs.top()->getTransitions());
			subGraphs.pop();
			// Then we create our temporary states.
			subGraphs.push(&*new Graph());
			states = *new vector<State*>();
			transitions = *new vector<State::Transition*>();
			numberOfStates++;
			// First create the states.
			tState1 = new State();			// New Start.
			startName = numberOfStates;
			tState1->setName(startName);
			tState2 = new State();			// New End.
			numberOfStates++;
			endName = numberOfStates;
			tState2->setIsFinal(true);
			tState2->setName(endName);
			// Then create transitions.
			t11 = new State::Transition(epsilon, tempGraph1->getStart());	// From new start to old start.
			t21 = new State::Transition(epsilon, tState2);					// From old end to new end.
			t22 = new State::Transition(epsilon, tempGraph1->getStart());	// From old end to old start.
			// Now we have the states and transitions, we need to add them to the other states.
			tState1->addTransition(t11);
			tempGraph1->getEnd()->addTransition(t21);
			tempGraph1->getEnd()->addTransition(t22);
			// Now change end points.
			tempGraph1->getEnd()->setIsFinal(false);
			// No make the transitions vector.
			copy1 = tempGraph1->getTransitions();
			copy2 = tState1->getTransitions();
			cStates1 = tempGraph1->getStates();
			// Create the transitions vector.
			transitions.reserve(copy1.size() + copy2.size());
			transitions.insert(transitions.end(), copy2.begin(), copy2.end());
			transitions.insert(transitions.end(), copy1.begin(), copy1.end());
			transitions.insert(transitions.end(), t21);
			transitions.insert(transitions.end(), t22);
			// Create the vector of states.
			states.reserve(cStates1.size() + 2);
			states.insert(states.end(), tState1);
			states.insert(states.end(), cStates1.begin(), cStates1.end());
			states.insert(states.end(), tState2);
			// Then we just get everything in the stack.
			subGraphs.top()->setStart(tState1);
			subGraphs.top()->setEnd(tState2);
			subGraphs.top()->setStates(states);
			subGraphs.top()->setTransitions(transitions);

			break;
		case 'E':
			// Epsilon is diferent, somehow...
			// We need to check if the nex simbol in the string is an or o an and...
			if (expression[i + 1] == '.') {
				// If it's an AND, then, there's nothing to do, just skip to the next simbol.
				i++;
			}
			else if (expression[i + 1] == '|') {
				// If it's and or, then we have stuff to do.
				// First we need to pop the stack.
				tempGraph1 = new Graph();
				tempGraph1->setEnd(subGraphs.top()->getEnd());
				tempGraph1->setStart(subGraphs.top()->getStart());
				tempGraph1->setStates(subGraphs.top()->getStates());
				tempGraph1->setTransitions(subGraphs.top()->getTransitions());
				subGraphs.pop();

				// Then we need to create 1 new State.
				subGraphs.push(&*new Graph());
				states = *new vector<State*>();
				transitions = *new vector<State::Transition*>();
				numberOfStates++;
				// First create the states.
				tState1 = new State();
				startName = numberOfStates;
				tState1->setName(startName);
				// Then create transitions.
				t11 = new State::Transition(epsilon, tempGraph1->getStart());	// One from new start to the old start.
				t12 = new State::Transition(epsilon, tempGraph1->getEnd());	// One from new start to the end.
				// Now we have the states and transitions, we need to add them to the other states.
				tState1->addTransition(t11);
				tState1->addTransition(t12);
				// No make the transitions vector.
				copy1 = tempGraph1->getTransitions();
				copy2 = tState1->getTransitions();
				cStates1 = tempGraph1->getStates();
				// Create the vector with transitions..
				transitions.reserve(copy1.size() + copy2.size());
				transitions.insert(transitions.end(), copy2.begin(), copy2.end());
				transitions.insert(transitions.end(), copy1.begin(), copy1.end());
				// Create the vector of states.
				states.reserve(cStates1.size() + 1);
				states.insert(states.end(), tState1);
				states.insert(states.end(), cStates1.begin(), cStates1.end());
				// Then we just get everything in the stack.
				subGraphs.top()->setStart(tState1);
				subGraphs.top()->setEnd(tempGraph1->getEnd());
				subGraphs.top()->setStates(states);
				subGraphs.top()->setTransitions(transitions);
				// We add 1 to the i.
				i++;
			}
			else {
				// If there's no operator after an epsilon, then it's an error.
				i = 10000;
				cout << "Error en la cadena!\nMal uso de epsilon!" << endl;
			}
			
			break;
		case '|':
			// We need to pop the top 2 elements in the stack and make them 1 graph.
			tempGraph1 = new Graph();
			tempGraph1->setEnd(subGraphs.top()->getEnd());
			tempGraph1->setStart(subGraphs.top()->getStart());
			tempGraph1->setStates(subGraphs.top()->getStates());
			tempGraph1->setTransitions(subGraphs.top()->getTransitions());
			subGraphs.pop();

			tempGraph2 = new Graph();
			tempGraph2->setEnd(subGraphs.top()->getEnd());
			tempGraph2->setStart(subGraphs.top()->getStart());
			tempGraph2->setStates(subGraphs.top()->getStates());
			tempGraph2->setTransitions(subGraphs.top()->getTransitions());
			subGraphs.pop();

			subGraphs.push(&*new Graph());
			states = *new vector<State*>();
			transitions = *new vector<State::Transition*>();
			numberOfStates++;
			// First create the states.
			tState1 = new State();
			startName = numberOfStates;
			tState1->setName(startName);
			tState2 = new State();
			numberOfStates++;
			endName = numberOfStates;
			tState2->setIsFinal(true);
			tState2->setName(endName);
			// Then create transitions.
			t11 = new State::Transition(epsilon, tempGraph2->getStart());
			t12 = new State::Transition(epsilon, tempGraph1->getStart());
			t21 = new State::Transition(epsilon, tState2);
			t22 = new State::Transition(epsilon, tState2);
			// Now we have the states and transitions, we need to add them to the other states.
			tState1->addTransition(t11);
			tState1->addTransition(t12);
			tempGraph2->getEnd()->addTransition(t21);
			tempGraph1->getEnd()->addTransition(t22);
			// Now change end points.
			tempGraph2->getEnd()->setIsFinal(false);
			tempGraph1->getEnd()->setIsFinal(false);
			// No make the transitions vector.
			copy1 = tempGraph1->getTransitions();
			copy2 = tempGraph2->getTransitions();
			copy3 = tState1->getTransitions();
			cStates1 = tempGraph1->getStates();
			cStates2 = tempGraph2->getStates();
			// Creamos el vector con las tranciciones.
			transitions.reserve(copy1.size() + copy2.size() + copy3.size() + 2);
			transitions.insert(transitions.end(), copy3.begin(), copy3.end());
			transitions.insert(transitions.end(), copy2.begin(), copy2.end());
			transitions.insert(transitions.end(), copy1.begin(), copy1.end());
			transitions.insert(transitions.end(), t21);
			transitions.insert(transitions.end(), t22);
			// Create the vector of states.
			states.reserve(cStates1.size() + cStates2.size() + 2);
			states.insert(states.end(), tState1);
			states.insert(states.end(), cStates2.begin(), cStates2.end());
			states.insert(states.end(), cStates1.begin(), cStates1.end());
			states.insert(states.end(), tState2);
			// Then we just get everything in the stack.
			subGraphs.top()->setStart(tState1);
			subGraphs.top()->setEnd(tState2);
			subGraphs.top()->setStates(states);
			subGraphs.top()->setTransitions(transitions);

			break;
		case '.':
			// We need to pop the top 2 elements in the stack and make them 1 graph.
			tempGraph1 = new Graph();
			tempGraph1->setEnd(subGraphs.top()->getEnd());
			tempGraph1->setStart(subGraphs.top()->getStart());
			tempGraph1->setStates(subGraphs.top()->getStates());
			tempGraph1->setTransitions(subGraphs.top()->getTransitions());
			subGraphs.pop();

			tempGraph2 = new Graph();
			tempGraph2->setEnd(subGraphs.top()->getEnd());
			tempGraph2->setStart(subGraphs.top()->getStart());
			tempGraph2->setStates(subGraphs.top()->getStates());
			tempGraph2->setTransitions(subGraphs.top()->getTransitions());
			subGraphs.pop();

			subGraphs.push(&*new Graph());
			states = *new vector<State*>();
			transitions = *new vector<State::Transition*>();

			tempGraph2->getEnd()->setTransitions(tempGraph1->getStart()->getTransitions());
			tempGraph2->getEnd()->setIsFinal(false);
			
			copy1 = tempGraph1->getTransitions();
			copy2 = tempGraph2->getTransitions();
			cStates1 = tempGraph1->getStates();
			cStates2 = tempGraph2->getStates();

			transitions.reserve(copy1.size() + copy2.size());
			transitions.insert(transitions.end(), copy2.begin(), copy2.end());
			transitions.insert(transitions.end(), copy1.begin(), copy1.end());
			states.reserve(cStates1.size() + cStates2.size());
			states.insert(states.end(), cStates2.begin(), cStates2.end());
			states.insert(states.end(), cStates1.begin()+1, cStates1.end());
			
			subGraphs.top()->setStart(tempGraph2->getStart());
			subGraphs.top()->setEnd(tempGraph1->getEnd());
			subGraphs.top()->setStates(states);
			subGraphs.top()->setTransitions(transitions);
			
			break;
		default:
			// Default means that it's a alphanumeric character.
			numberOfStates++;
			subGraphs.push(&*new Graph());
			
			states = *new vector<State*>();
			transitions = *new vector<State::Transition*>();
			endName = numberOfStates;
			endName++;
			endState = new State();
			endState->setIsFinal(true);
			endState->setName(endName);
			State::Transition *t = new State::Transition(expression[i], endState);
			startName = numberOfStates;
			startState = new State();
			startState->addTransition(t);
			startState->setName(startName);

			transitions.push_back(t);
			states.push_back(startState);
			states.push_back(endState);

			subGraphs.top()->setStart(startState);
			subGraphs.top()->setEnd(endState);
			subGraphs.top()->setTransitions(transitions);
			subGraphs.top()->setStates(states);

			if (find(simbols.begin(), simbols.end(), expression[i]) == simbols.end()) {
				simbols.push_back(expression[i]);
			}
			numberOfStates++;
			break;
		}

	}

	NFA = subGraphs.top();
	NFA->setSimbols(simbols);

	return NFA;
}

// We're gonna make some usefull function here to simulate the AFN, the're not necesarry for the Graph and user might never use em.
// e-Closure(s) is a function that returns a set of states from where you can get from state s using only epsilon transitions.
vector<State*> eClosure(State *s) {
	vector<State*> tempStates = *new vector<State*>();
	vector<State*> copy1 = *new vector<State*>();
	vector<State*> copy2 = *new vector<State*>();

	// First states are calculated manually...
	tempStates.insert(tempStates.end(), s);		// Adding the first state, since it has a "epsilon to himself".
	// Then we iterate based on the next states...
	size_t i = 0;
	while (i < tempStates.size()) {
		copy1 = tempStates[i]->getNext('E');
		// We need to know if there's any duplicated element.
		for (size_t k = 0; k < copy1.size(); k++) {
			if (find(tempStates.begin(), tempStates.end(), copy1[k]) == tempStates.end()) {
				// If the copy element k, is NOT in the vector tempState, it returned last,
				// then we must add it to the tempStates subset, meaning that it is a state 
				// that's not been visited.
				copy2.insert(copy2.end(), copy1[k]);
			}
		}
		// Now we insert the copy 2 elements, that are elements that were not in the subset.
		tempStates.insert(tempStates.end(), copy2.begin(), copy2.end());
		// and clean the copy2 subset.
		copy2 = *new vector<State*>();
		i++;
	}

	return tempStates;

}

// e-Closure(T) is a function that returns a set of states from where you can get from the subset of states T using only epsilon transitions.
vector<State*> eClosure(vector<State*> T) {
	vector<State*> copy1 = *new vector<State*>();
	vector<State*> copy2 = *new vector<State*>();
	vector<State*> tempStates = *new vector<State*>();

	// First we add all the elements in T, since they all have epsilon transitions to themselvs.
	tempStates.insert(tempStates.end(), T.begin(), T.end());

	size_t i = 0;
	while (i < tempStates.size()) {
		copy1 = tempStates[i]->getNext('E');
		// We need to know if there's any duplicated element.
		for (size_t j = 0; j < copy1.size(); j++) {
			if (find(tempStates.begin(), tempStates.end(), copy1[j]) == tempStates.end()) {
				// If the copy element k, is NOT in the vector tempState, it returned last,
				// then we must add it to the tempStates subset, meaning that it is a state 
				// that's not been visited.
				copy2.insert(copy2.end(), copy1[j]);
			}
		}
		// Now we insert the copy 2 elements, that are elements that were not in the subset.
		tempStates.insert(tempStates.end(), copy2.begin(), copy2.end());
		// and clean the copy2 subset.
		copy2 = *new vector<State*>();
		i++;
	}

	return tempStates;
}

// Move(T, a) is a function that returns a subset of states from the NFA that have a transition a, from any state from the subset T.
vector<State*> move(vector<State*> T, char a) {
	vector<State*> copy1 = *new vector<State*>();
	vector<State*> copy2 = *new vector<State*>();
	vector<State*> tempStates = *new vector<State*>();

	// The first elements must be searched apart.
	for (size_t i = 0; i < T.size(); i++) {
		copy1 = T[i]->getNext(a);
		// We need to know if there's any duplicated element.
		for (size_t j = 0; j < copy1.size(); j++) {
			if (find(tempStates.begin(), tempStates.end(), copy1[j]) == tempStates.end()) {
				// If the copy element k, is NOT in the vector tempState, it returned last,
				// then we must add it to the tempStates subset, meaning that it is a state 
				// that's not been visited.
				tempStates.insert(tempStates.end(), copy1[j]);
			}
		}
	}

	return tempStates;
}

// Move(T, a) is a function that returns a subset of states from the NFA that have a transition a, from any state from the State T.
vector<State*> move(State* T, char a) {
	vector<State*> tempStates = *new vector<State*>();

	// The first elements must be searched apart.
	tempStates = T->getNext(a);

	return tempStates;
}


void TEST(Graph *NFA, char a) {
	// THIS FUNCTION WILL ONLY BE USED TO TEST SUTFF
	vector<State*> test1 = *new vector<State*>();
	vector<State*> test2 = *new vector<State*>();

	test1.push_back(NFA->getStates()[2]);
	test1.push_back(NFA->getStates()[3]);
	test1.push_back(NFA->getStates()[8]);

	eClosure(NFA->getStart());
	eClosure(test1);
	move(NFA->getStates(), 'a');
}

// This function main purpose is to tell if the given chan is valid acording to the NFA constructed.
bool Graph::simulateNFA(Graph *NFA, string chain) {
	vector<State*> S = *new vector<State*>();

	// First we make e-closur of s_0.
	S = eClosure(NFA->getStart());

	// Now we iterate through the NFA.
	size_t i = 0;
	while (i < chain.size()) {
		S = eClosure(move(S, chain[i]));
		i++;
	}

	// Now we just check if the final state is in S.
	if (find(S.begin(), S.end(), NFA->getEnd()) != S.end()) {
		return true;
	}
	else {
		return false;
	}
}

// This method main purpose is to return the given Graph as a File.
void Graph::asFile(Graph &graph, string &name, int type) {
	// Declaring string variables to hold the values to print.
	string states = "ESTADOS = { ";
	int temp = ' ';
	string simbols = "SIMBOLOS = { ";
	string transitions = "TRANSICIONES = { ";
	string start = "INICIO = { ";
	string end = "ACEPTACION = { ";

	try {
		ofstream outfile(name + ".txt");
		if (type == 0) {
			// Getting the states...
			for (size_t i = 0; i < graph.getStates().size(); i++) {
				temp = graph.getStates()[i]->getName();
				states += to_string(temp) + ", ";
			}
			// Getting the simbols...
			for (size_t i = 0; i < graph.getSimbols().size(); i++) {
				simbols += string(1, graph.getSimbols()[i]) + ", ";
			}
			// Getting the transitions...
			for (size_t i = 0; i < graph.getTransitions().size(); i++) {
				transitions += graph.getTransitions()[i]->toString() + ", ";
			}
			// Getting the Start.
			temp = graph.getStart()->getName();
			start += to_string(temp) + " }";
			// Getting the End.
			for (size_t i = 0; i < graph.getStates().size(); i++) {
				if (graph.getStates()[i]->getIsFinal()) {
					temp = graph.getStates()[i]->getName();
					end += to_string(temp) + ", ";
				}
			}
		}
		else if (type == 1) {
			// Getting the states...
			for (size_t i = 0; i < graph.getStates().size(); i++) {
				temp = graph.getStates()[i]->getName();
				states += string(1, temp) + ", ";
			}
			// Getting the simbols...
			for (size_t i = 0; i < graph.getSimbols().size(); i++) {
				simbols += string(1, graph.getSimbols()[i]) + ", ";
			}
			// Getting the transitions...
			for (size_t i = 0; i < graph.getTransitions().size(); i++) {
				transitions += string(graph.getTransitions()[i]->toString()) + ", ";
			}
			// Getting the Start.
			temp = graph.getStart()->getName();
			start += string(1, temp) + " }";
			// Getting the End.
			for (size_t i = 0; i < graph.getStates().size(); i++) {
				if (graph.getStates()[i]->getIsFinal()) {
					temp = graph.getStates()[i]->getName();
					end += string(1, temp) + ", ";
				}
			}
		}
		// Eding format...
		states += " }";
		simbols += " }";
		transitions += " }";
		end += " }";

		// Printing stuff in the file...
		outfile << states << '\n' << simbols << '\n' << start << '\n' << end << '\n' << transitions << endl;

		outfile.close();

	}
	catch (int e) {
		cout << "Error while making the file, error code: " + e << endl;
	}
}

// Make a DFA base on a NFA with subsuts construction.
Graph* Graph::NFAtoDFA(Graph *NFA) {
	Graph *DFA = new Graph();
	vector<State::Transition*> newTransitions = *new vector<State::Transition*>();

	vector<char> simbols = *new vector<char>();
	vector<State*> temp = *new vector<State*>();
	State::Transition *tempT = new State::Transition();
	char stateName = 'A';
	int t = 0;

	vector<State*> Dtran[24][100];
	vector< vector<State*> > Dstates = *new vector< vector<State*> >();
	vector<State*> U = *new vector<State*>();

	// While there're States unvisited, we must iterate.
	size_t i = 0;
	simbols = NFA->getSimbols();
	
	// First state for Dstate is e-closure(s_0)
	Dstates.push_back(eClosure(NFA->getStates()[0]));
	temp.push_back(&*new State(stateName));
	stateName++;

	// We need to look for states in Dstates that are unmarked.
	while (i < Dstates.size()) {
		// Mark the current state.
		// No need, since we will just move through the size of Dstates, visiting only once each.

		// Iterate for each simbol in the alphabet.
		for (size_t j = 0; j < simbols.size(); j++) {
			// Calculate the e-closure(move()) for current state in the j-simbol.
			U = eClosure(move(Dstates[i], simbols[j]));
			// We check if the state is already in the Dstates.
			if (find(Dstates.begin(), Dstates.end(), U) == Dstates.end()) {
				// If it doesn't, then we must add it and create a new state.
				if (U.size() > 0) {
					Dstates.push_back(U);
					temp.push_back(&*new State(stateName));
					stateName++;
				}
			}
			if (U.size() > 0) {
				Dtran[i][j] = U;
			}
		}

		i++;
	}

	// After we have all the DFA States in Dstates we need to make them states and give them transitions.
	// But first... LET ME TAKE A SELFIE!!... Sorry about that, we need to deal with dead ends... nvm I did it early... 
	for (i = 0; i < Dstates.size(); i++) {
		for (size_t j = 0; j < simbols.size(); j++) {
			// First I need to know if the state has a transition for this simbol...
			if (Dtran[i][j].size() > 0) {
				// If it does, I need to know what transition it is.
				t = (find(Dstates.begin(), Dstates.end(), Dtran[i][j]) - Dstates.begin());
				// Now that i know were the transition takes to...
				tempT = new State::Transition(simbols[j], temp[t]);
				temp[i]->addTransition(tempT);
				newTransitions.push_back(tempT);
				// I must check if the current state is final...
				if (find(Dtran[i][j].begin(), Dtran[i][j].end(), NFA->getEnd()) != Dtran[i][j].end()) {
					temp[t]->setIsFinal(true);
				}
			}
		}
	}

	// Now add everithing to the DFA Graph.
	DFA->setSimbols(simbols);			// Set Simbols...
	DFA->setStates(temp);				// Set States...
	DFA->setStart(temp[0]);				// Set Start node...
	// No need to set end...
	DFA->setTransitions(newTransitions);

	return DFA;
}

// This function will simulate any given DFA.
bool Graph::simulateDFA(Graph *DFA, string chain) {
	vector<State*> S = *new vector<State*>();

	// First we move move from s_0.
	S = move(DFA->getStart(), chain[0]);

	// Now we iterate through the NFA.
	size_t i = 1;
	while (i < chain.size()) {
		S = move(S, chain[i]);
		i++;
	}

	// Now we just check if the final state is in S.
	for (i = 0; i < S.size(); i++) {
		if (S[i]->getIsFinal()) {
			return true;
		}
	}
	return false;
}