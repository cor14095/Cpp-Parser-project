#pragma once
#include <iostream>
#include <string>
#include <stack>
#include <list>

using namespace std;

/*
<CLASS DESCRIPTION!>
Summary:
- State class will be the states of the graph.

Description:
- State is very usefull because it will make easyer to keep every state 
  in order and give some usefull functions for the given algoriths that
  are been implemented in Graph.

Private Variables:
- Name: Is the name of the state, often a number from 0 to n.
- Transitions: This sub class has the transition for the givem state.
*/

class State
{
protected:
	class Transition {
		/*
		Transitions is just a class that let me save
		in a order way some stuff for each State.
		*/
	public:
		// Constructors....
		Transition() {
			_name = ' ';
			*_next = NULL;
		};
		Transition(char name, State *next) {
			_name = name;
			*_next = next;
		};

		// Setters...
		void setName(char name) { _name = name; };
		void setNext(State *next) { _next = &next; };

		// Getters...
		char getName() { return _name; };
		State *getState() { return *_next; };

	private:
		char _name;
		State* *_next;
	};

public:
	// General constructor.
	State();
	// Constructor with only name.
	State(char name);
	//Constructor with name and 1 or more transitions
	State(char name, Transition transitions[], int size);

	// General destructor.
	~State();

	// Method to add a transition to the transitions stack.
	void addTransition(Transition transition);
	// Function to get next States.
	list<State*> getNext(char transition);

private:
	char _name;
	stack<Transition> *_transitions;

};

