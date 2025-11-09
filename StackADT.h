#ifndef StackADT_h
#define StackADT_h

#include "LinkedListADT.h"

template <typename T>
class DynStackNode : protected LinkedList<T> {
private:
	struct StackNode {
		T value;			 //value in Node
		StackNode * next;	 //pointer to the next Node
	};

	StackNode * top;	//pointer to the stack top
	int counter = 0;

public:
	DynStackNode();
	~DynStackNode();

	/*************************************************************************
	This function adds an element onto the top of the stack

	Pre: T item - Abstract value
	Post: Place the abstact value on top of the stack and increase the counter
	for the number of elements in the stack by one.

	*************************************************************************/
	void push(T item);

	/*************************************************************************
	This function deletes the top element of the stack

	Pre: The stack is not empty
	Post: Top element of the stack is removed and the element counter
	is decreased by one.

	*************************************************************************/
	void pop();


	/*************************************************************************
	This function checks if the stack is empty

	Pre: top - pointer that points to the top of the stack
	Post:
	Return true or false.

	*************************************************************************/
	bool isEmpty();

	/*************************************************************************
	This function gets the top stack value.

	Pre: top - pointer that points to the top of the stack
	Post:
	Return the value at the top of the stack

	*************************************************************************/
	T topVal();

	/*************************************************************************
	This function gets the number of elements in the stack

	Pre: counter - a number that increased everytime a new element in the
	stack was made.

	Post:
	Return the number of elements in the stack.

	*************************************************************************/
	int size();

};




/*************************************************************************
set the stack as empty
set counter to zero

*************************************************************************/
template<typename T>
DynStackNode<T>::DynStackNode() {
	top = nullptr;
	counter = 0;
}

/*************************************************************************
while(top of the stack is not empty)
delete top
move onto the next stack element that is the new top
delete until the stack is empty

*************************************************************************/
template<typename T>
DynStackNode<T>::~DynStackNode() {
	StackNode *nodePtr;
	StackNode *nextNode;

	//position nodePtr at the top of the stack
	nodePtr = top;

	//Transverse the list deleting each element
	while (nodePtr != nullptr) {
		nextNode = nodePtr->next;
		delete nodePtr;
		nodePtr = nextNode;
	}
}


/*************************************************************************
store item in newNode
if (empty)
set newNode as the first element/node
else
set newNode on top of the current stack

*************************************************************************/
template<typename T>
void DynStackNode<T>::push(T item) {
	StackNode *newNode = nullptr; //points to a new node

								  //allocate a new node and store num in there
	newNode = new StackNode;
	newNode->value = item;

	//if there is no nodes in the list, make newNode the first node
	if (isEmpty()) {
		top = newNode;
		newNode->next = nullptr;
	}
	else {
		newNode->next = top;
		top = newNode;
	}
	counter++;
}

/*************************************************************************
if (empty)
tell the user that they can't do it
else
delete top
tell user what was deleted

*************************************************************************/
template<typename T>
void DynStackNode<T>::pop() {
	StackNode *temp = nullptr; //temporary ptr

							   //check if stack is empty
	if (isEmpty()) {
		std::cout << "The stack is empty. Cannot pop." << std::endl;
	}
	else {
		std::cout << top->value << " was popped." << std::endl;
		temp = top->next;
		delete top;
		top = temp;

	}
	counter--;
}

/*************************************************************************
if (top does NOT contain an element)
change status to true
else
change status to false

*************************************************************************/
template<typename T>
bool DynStackNode<T>::isEmpty() {
	bool status;
	if (!top) {
		status = true;
	}
	else {
		status = false;
	}
	return status;
}


/*************************************************************************
return the value in the top element

*************************************************************************/
template<typename T>
T DynStackNode<T>::topVal() {
	return top->value;
}

/*************************************************************************
return the counter that kept track of all the elements/node

*************************************************************************/
template<typename T>
int DynStackNode<T>::size() {
	return counter;
}

#endif 