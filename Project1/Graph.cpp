#include <iostream>
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
	State::Transition *t = new State::Transition(&simbol, _endState);
	name--;
	_startState = new State(name);
	_startState->addTransition(t);

	_transitions.push_back(t);
	_states.push_back(_endState);
	_states.push_back(_startState);
}
// Constructor with all parameters.
Graph::Graph(vector<State*> states, vector<char*> simbols, vector<State::Transition*> transitions, State *startState, State *endState) {
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
Graph Graph::makeNFA(string expression) {
	// Some useful variables.
	char epsilon = 'E';
	vector<State*> states = *new vector<State*>();
	vector<State*> cStates1 = *new vector<State*>();
	vector<State*> cStates2 = *new vector<State*>();
	vector<char*> simbols = *new vector<char*>();
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

	Graph NFA;
	// From the postFix we made, we know that the expression is valid.
	for (size_t i = 0; i < expression.size(); i++) {
		// We use a switch to check term by term.
		switch (expression[i])
		{
		case '*':
			// Since Klin is a unary operator we just need to get the top element in the stack. and add 2 transitions, from begining to end(s) and end(s) to begining.

			break;
		case '+':
			// Since + is a unary operator we just need to get the top element in the stack. and add 1 transition, from end(s) to beginings.

			break;
		case 'E':
			// Epsilon is diferent, somehow...
			
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
			t11 = new State::Transition(&epsilon, tempGraph2->getStart());
			t12 = new State::Transition(&epsilon, tempGraph1->getStart());
			t21 = new State::Transition(&epsilon, tState2);
			t22 = new State::Transition(&epsilon, tState2);
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
			// Creamos el vector con los estados.
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
			State::Transition *t = new State::Transition(&expression[i], endState);
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

			simbols.push_back(&expression[i]);
			numberOfStates++;
			break;
		}

	}

	return NFA;
}
