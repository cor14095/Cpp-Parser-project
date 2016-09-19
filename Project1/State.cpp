#include <list>
#include <stack>

#include "State.h"

// General constructor.
State::State() {
	_name = ' ';
	stack<Transition>_transitions;
}
// Constructor with only name.
State::State(char name) {

}
//Constructor with name and 1 or more transitions
State::State(char name, Transition transitions[]) {

}

// General destructor.
State::~State() {

}

// Method to add a transition to the transitions stack.
void State::addTransition(Transition transition) {

}
// Function to get next States.
list<State*> State::getNext(char transition) {
	list<State*> transitions;

	return transitions;
}