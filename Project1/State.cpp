#include <list>
#include <stack>

#include "State.h"

// General constructor.
State::State() {
	_name = ' ';
	stack<Transition> *_transitions;
}
// Constructor with only name.
State::State(char name) {
	_name = name;
	stack<Transition> *_transitions;
}
//Constructor with name and 1 or more transitions
State::State(char name, Transition transitions[], int size) {
	_name = name;
	for (int i = 0; i < size; i++) {
		_transitions->push(transitions[i]);
	}
}

// General destructor.
State::~State() {

}

// Method to add a transition to the transitions stack.
void State::addTransition(Transition transition) {
	_transitions->push(transition);
}
// Function to get next States.
list<State*> State::getNext(char transition) {
	list<State*> transitions;
	stack<Transition> tempTransitions = *_transitions;

	// We're gonna move in the temp stack to don't mess around with stuff
	while (!tempTransitions.empty()) {
		// If the names are the same, then the transition can happend
		// so we save the state for that transition.
		if (tempTransitions.top().getName() == transition) {
			transitions.push_back(tempTransitions.top().getState());
		}
		// After the check, just pop the stack...
		tempTransitions.pop();
	}

	// At the end we should have a list of the states were we can go 
	// with the given token.
	return transitions;
}