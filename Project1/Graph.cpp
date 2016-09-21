#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <stack>
#include <string>

#include "State.h"
#include "Graph.h"

// General constructor.
Graph::Graph() {
	vector<State*> _states = *new vector<State*>();
	vector<char*> _simbols = *new vector<char*>();
	vector<State::Transition*> _transitions = *new vector<State::Transition*>();
	State *_startState = new State();
	State *_endStates = new State();
}
// Constructor for a character.
Graph::Graph(int name, char simbol) {
	char epsilon = 'E';
	vector<State*> _states = *new vector<State*>();
	vector<char*> _simbols = *new vector<char*>();
	vector<State::Transition*> _transitions = *new vector<State::Transition*>();
	State *_startState = new State();
	State *_endStates = new State();

	name++;
	_endState = new State(name);
	_endState->setIsFinal(true);
	State::Transition *t = new State::Transition(simbol, _endState);
	name--;
	_startState = new State(name);
	_startState->addTransition(t);

	_transitions.push_back(t);
	_states.push_back(_endState);
	_states.push_back(_startState);
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

			simbols.push_back(expression[i]);
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

	size_t i = 0;
	while (i < tempStates.size()) {
		copy1 = tempStates[i]->getNext(a);
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
void Graph::asFile(Graph &graph, string &name) {
	// Declaring string variables to hold the values to print.
	string states = "ESTADOS = { ";
	int state = 0;
	string simbols = "SIMBOLOS = { ";
	string transitions = "TRANSICIONES = { ";
	string start = "INICIO = { ";
	string end = "ACEPTACION = { ";

	try {
		ofstream outfile(name + ".txt");

		// Getting the states...
		for (size_t i = 0; i < _states.size(); i++) {
			state = _states[i]->getName();
			states += to_string(state) + ", ";
			//cout << _states[i]->getName() + ", " << endl;
		}
		// Getting the simbols...
		for (size_t i = 0; i < _simbols.size(); i++) {
			simbols += string(1, _simbols[i]) + ", ";
		}
		// Getting the transitions...
		for (size_t i = 0; i < _transitions.size(); i++) {
			transitions += _transitions[i]->toString() + ", ";
		}
		// Getting the Start.
		start += to_string(_startState->getName()) + " }";
		// Getting the End.
		end += to_string(_endState->getName()) + " }";
		// Eding format...
		states += " }";
		simbols += " }";
		transitions += " }";

		// Printing stuff in the file...
		outfile << states << '\n' << simbols << '\n' << start << '\n' << end << '\n' << transitions << endl;

		outfile.close();

	}
	catch (int e) {
		cout << "Error while making the file, error code: " + e << endl;
	}
}