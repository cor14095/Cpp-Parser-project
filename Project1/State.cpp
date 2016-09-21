#include <list>
#include <stack>

#include "State.h"

// General constructor.
State::State() {
	char _name = *new char();
	stack<Transition*> _transitions = *new stack<Transition*>();
	_isVisited = false;
}
// Constructor with only name.
State::State(int name) {
	_name = name;
	stack<Transition*> _transitions = *new stack<Transition*>();
	_isVisited = false;
}
//Constructor with name and 1 or more transitions
State::State(int name, vector<Transition> transitions, int size) {
	_name = name;
	for (int i = 0; i < size; i++) {
		_transitions.push_back(&transitions[i]);
	}
	_isVisited = false;
}

// General destructor.
State::~State() {

}

// Method to add a transition to the transitions stack.
void State::addTransition(Transition *transition) {
	_transitions.push_back(transition);
}

// Function to get next States.
vector<State*> State::getNext(char transition) {
	vector<State*> nextStates;

	// We're gonna move in the list index to don't mess around with stuff
	for (size_t i = 0; i < _transitions.size(); i++) {
		// If the names are the same, then the transition can happend
		// so we save the state for that transition.
		if (_transitions[i]->getName() == transition) {
			nextStates.push_back(_transitions[i]->getState());
		}
	}

	// At the end we should have a list of the states were we can go 
	// with the given token.
	return nextStates;
}