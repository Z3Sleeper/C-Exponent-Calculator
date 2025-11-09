#ifndef QueueADT_H
#define QeueueADT_H
#include "LinkedListADT.h"

template <typename T>
class DynQueue : protected LinkedList<T>{
private:
	int numItems; //number of items in queue

	Node<T> *front;
	Node<T> *rear;

public:
	DynQueue();
	~DynQueue();
	
	//Queue operations
	/*************************************************************************
	This function adds a node to the rear of the queue

	Pre: T item - Abstract value input for the data member
	Post: Sets the data of the new node and adds it to the queue
	*************************************************************************/
	void enqueue(T item);

	/*************************************************************************
	This function removes a node from the front of the queue

	Pre: T item - Abstract value to set the data member so that there is an
				is an option to say what value in the node is being removed
	Post: Removed the node in the queue
	*************************************************************************/
	void dequeue(T &item);

	/*************************************************************************
	This function checks if the queue is empty

	Pre: numItems - the counter of the number of elements in the queue
	Post: 
	Return true or false
	*************************************************************************/
	bool isEmpty(); 

	/*************************************************************************
	This function clears all the elements/nodes in the queue

	Pre: The queue is not empty
	Post: All the nodes are removed; the queue is empty
	*************************************************************************/
	void clear();

	/*************************************************************************
	This function returns the value of the front of the queue

	Pre: The queue is not empty
	Post: 
	Return front node's value
	*************************************************************************/
	void frontValue();

	/*************************************************************************
	This function returns the value of the rear of the queue

	Pre: The queue is not empty
	Post:
	Return rear node's value
	*************************************************************************/
	void rearValue();

	/*************************************************************************
	This function returns the size of the queue

	Pre: numItems - the counter of the number of elements in the queue
	Post:
	Return the number of elements in the queue
	*************************************************************************/
	int size();

};


/*************************************************************************
Creates empty queue and sets the number of elements in queue to zero
*************************************************************************/
template <typename T>
DynQueue<T>::DynQueue() {
	front = nullptr;
	rear = nullptr;
	numItems = 0;
}

/*************************************************************************
Clear the entire queue, making it empty
*************************************************************************/
template <typename T>
DynQueue<T>::~DynQueue() {
	clear();
}

/*************************************************************************
create new node and store num in it
if(isEmpty)
set front and rear to the newNode
else
add newNode to the rear end of the queue
set rear as the newNode

counter + 1
*************************************************************************/
template <typename T>
void DynQueue<T>::enqueue(T item) {
	Node<T> *newNode = nullptr;

	//create new node and store num in it
	newNode = new Node<T>;
	newNode->data = item;
	newNode->next = nullptr;

	//adjust front and rear
	if (isEmpty()) {
		front = newNode;
		rear = newNode;
	}
	else {
		rear->next = newNode;
		rear = newNode;
	}
	//update numitems
	numItems++;
}

/*************************************************************************
if (isEmpty)
tell the user that the queue is empty
else
delete the front node
set front pointer to the new front of the queue

count - 1
*************************************************************************/
template <typename T>
void DynQueue<T>::dequeue(T &item) {
	Node<T> *temp = nullptr;

	if (isEmpty()) {
		std::cout << "The queue is empty" << std::endl;
	}
	else {
		//save front node value in num
		item = front->data;

		//remove front node and delete it
		temp = front;
		front = front->next;
		delete temp;

		numItems--;
	}
}

/*************************************************************************
true is queue is empty; else it returns false
*************************************************************************/
template <typename T>
bool DynQueue<T>::isEmpty() {
	if (numItems > 0) {
		return false;
	}
	else {
		return true;
	}
}

/*************************************************************************
while (Queue is not empty)
remove nodes until the queue is empty
reset count
*************************************************************************/
template <typename T>
void DynQueue<T>::clear() {
	T value; //dummy value for dequeue
	while (!isEmpty()) {
		dequeue(value);
	}
	numItems = 0;
}

/*************************************************************************
if (queue is not empty)
tell user the data in the front node
else
tell the user that the queue is empty
*************************************************************************/
template <typename T>
void DynQueue<T>::frontValue() {
	if (front != nullptr) {
		std::cout << front->data << std::endl;
	}
	else {
		std::cout << "There is no elements in the queue" << std::endl;
	}
}

/*************************************************************************
if (queue is not empty)
tell user the data in the rear node
else
tell the user that the queue is empty
*************************************************************************/
template <typename T>
void DynQueue<T>::rearValue() {
	if (rear != nullptr) {
		std::cout << rear->data << std::endl;
	}
	else {
		std::cout << "There is no elements in the queue" << std::endl;
	}
}

/*************************************************************************
return the counter that holds the number of the elements in the queue
*************************************************************************/
template <typename T>
int DynQueue<T>::size() {
	return numItems;
}

#endif 
