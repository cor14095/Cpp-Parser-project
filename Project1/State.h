#pragma once
#include <iostream>
#include <string>
#include <vector>

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
public:
	// Transition must be public to be used in the graph.
	class Transition {
		/*
		Transitions is just a class that let me save
		in a order way some stuff for each State.
		*/
	public:
		// Constructors....
		Transition() {
			char *_name = NULL;
			State *_next = NULL;
		};
		Transition(char *name, State *next) {
			_name = name;
			_next = next;
		};

		// Setters...
		void setName(char *name) { _name = name; };
		void setNext(State *next) { _next = next; };

		// Getters...
		char *getName() { return _name; };
		State *getState() { return _next; };

	private:
		char *_name;
		State *_next;
	};

	// General constructor.
	State();
	// Constructor with only name.
	State(int name);
	//Constructor with name and 1 or more transitions
	State(int name, vector<Transition> transitions, int size);

	// General destructor.
	~State();

	// Setter for isFinal.
	void setIsFinal(bool isFinal) { _isFinal = isFinal; };
	// Setter for transition.
	void setTransitions(vector<Transition*> transitions) { _transitions = transitions; };
	void setName(int name) { _name = name; };
	
	// Getters...
	int getName() { return _name; };
	vector<Transition*> getTransitions() { return _transitions; };

	// Method to add a transition to the transitions stack.
	void addTransition(Transition *transition);
	// Function to get next States.
	vector<State*> getNext(char transition);

private:
	int _name;
	vector<Transition*> _transitions;
	bool _isFinal;

};

