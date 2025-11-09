#ifndef LINKEDLISTADT_H
#define LINKEDLISTADT_H
#include "NodeADT.h"

template<typename T>
class LinkedList
{
private:

	Node<T> *head;	// head element
	int count;		// number of data nodes in the list

public:

	LinkedList();
	~LinkedList();

	/*************************************************************************
	This function inserts a node at the start of the linked list.

	Pre: T val - Abstract value input for the data member
	Post: Sets the data of the new node and puts it at the start of the list.
	*************************************************************************/
	void insertFirst(T val);

	/*************************************************************************
	This function inserts a node at the end of the linked list.

	Pre: T val - Abstract value input for the data member
	Post: Sets the data of the new node and puts it at the end of the list.
	*************************************************************************/
	void insertLast(T val);

	/*********************************************************************************
	This function inserts a node anywhere in the linked list.

	Pre: T val - Abstract value input for the data member
		 int insertHere - specifies list location to insert
	Post: Sets the data of the new node and puts it at the specified point in the list.
	***********************************************************************************/
	void insertHere(T val, int insertHere);

	/*************************************************************************
	This function searches the list for nodes containing specified data.
	(This function does not work with Currency class lists)

	Pre: T val - Abstract value specification for the search
	Post: Returns the list nodes containing the values
	*************************************************************************/
	void searchByDataForPlace(T val);

	/*************************************************************************
	This function searches the list for nodes containing specified data.
	(This function is only for Currency class lists)

	Pre: T val - Abstract value specification for the search
	Post: Returns the list nodes containing the values
	*************************************************************************/
	void searchByCurrencyDataForPlace(T val);

	/*************************************************************************
	This function searches the list for the data in a specified node.

	Pre: int findData - specifies the node to be searched
	Post: Returns the data in the specified node
	*************************************************************************/
	void searchByPlaceForData(int findData);

	/*************************************************************************
	This function deletes a specified node.

	Pre: int deleteThis - specifies the node to be searched
	Post: Deletes the specified node
	*************************************************************************/
	void deleteNodeByPlace(int deleteThis);

	/*************************************************************************
	This function deletes nodes containing specified data.
	(This function does not work with Currency class lists)

	Pre: T deleteThis - specifies the data for search and deletion
	Post: Deletes all data nodes containing the specified data
	*************************************************************************/
	void deleteNodesByData(T deleteThis);

	/*************************************************************************
	This function deletes data nodes containing specified data.
	(This function is only for Currency class lists)

	Pre: T deleteThis - specifies the data for search and deletion
	Post: Deletes all data nodes containing the specified data
	*************************************************************************/
	void deleteCurrencyNodesByData(T deleteThis);

	/*************************************************************************
	This function deletes all data nodes in the list.

	Pre:
	Post: Deletes all data nodes in the list
	*************************************************************************/
	void deleteAll();

	/*************************************************************************
	This function returns the number of data nodes in the list.

	Pre:
	Post: return count
	*************************************************************************/
	int getCount() { return count; }

	/*************************************************************************
	This function prints all data nodes in the list in list order.

	Pre:
	Post: Prints all data nodes in the list in list order
	*************************************************************************/
	void print();

	//Note: Currency object functions are listed at the bottom of this file (below the print function)
};

/**************************************************
Constructor

Allocate a new Node<T> object to head
Set head pointer to NULL
Set count to 0
***************************************************/
template<typename T>
LinkedList<T>::LinkedList()
{
	head = new Node<T>; // head points to the sentinel node
	head->next = nullptr;
	count = 0;
}


/**************************************************
Destructor - Deletes all nodes

Create pointer Current
Create pointer Next
Point Current to head
While (Current doesn't point to NULL)
{
	Point Next to Current->next
	Delete the node Current is pointing to
	Point Current to Next
}
***************************************************/
template<typename T>
LinkedList<T>::~LinkedList()
{
	Node<T> *pCur;
	Node<T> *pNext;

	pCur = head;

	while (pCur != nullptr) {
		pNext = pCur->next;
		delete pCur;
		pCur = pNext;
	}
}

/**************************************************
Inserts a node at the start of the list

Create pointer newNode
Create pointer Current
Allocate a new Node<T> object to newNode
Set newNode->data to T val
Point Current to head->next
Point head->next to newNode
Point newNode->next to Current
Add 1 to the count counter
***************************************************/
template<typename T>
void LinkedList<T>::insertFirst(T val)
{
	Node<T> *newNode;  // A new node
	Node<T> *pCur;     // To traverse the list

	// Allocate a new node and store value there.
	newNode = new Node<T>;
	newNode->data = val;

	// Insert the new node after head
	pCur = head->next;
	head->next = newNode;
	newNode->next = pCur;

	// Update the counter
	count++;
}

/**************************************************
Inserts a node at the end of the list

Create pointer newNode
Create pointer Current
Create pointer Previous
Allocate a new Node<T> object to newNode
Set newNode->data to input value
Point Previous to head
Point Current to head->next
While (Current doesn't point to NULL)
{
	Point Previous to Current
	Point Current to Current->next
}
Point Previous->next to newNode
Point newNode->next to Current
Add 1 to the count counter
***************************************************/
template<typename T>
void LinkedList<T>::insertLast(T val)
{
	Node<T> *newNode;  // A new node
	Node<T> *pCur;     // To traverse the list
	Node<T> *pPre;     // The previous node

					   // Allocate a new node and store value there.
	newNode = new Node<T>;
	newNode->data = val;

	// insert at the end
	pPre = head;
	pCur = head->next;
	while (pCur != nullptr)
	{
		pPre = pCur;
		pCur = pCur->next;
	}

	// Insert the new node between pPre and pCur
	pPre->next = newNode;
	newNode->next = pCur;

	// Update the counter
	count++;
}

/**************************************************
Inserts a node where specified

If (location is head or location out of bounds)
{
	Print "Invalid placement"
	Return
}	
If (location is within bounds of list +1)
{
	Create pointer newNode
	Create pointer Current
	Create pointer Previous
	Allocate a new Node<T> object to newNode
	Set newNode->data to input value
	Point Previous to head
	Point Current to head->next
	For (each node up to target)
	{
		Previous = Current
		Current = Current->next
	}
	Point Previous->next to newNode
	Point newNode->next to Current
	Add 1 to the count counter
}
Else
	Execute insertLast function
***************************************************/
template<typename T>
void LinkedList<T>::insertHere(T val, int insertHere)
{
	if (insertHere < 1 || insertHere > count + 1) {
		std::cout << "Invalid placement" << std::endl;
		return;
	}

	// Insert the new node after specified node
	if (insertHere < count + 1) {
		Node<T> *newNode;  // A new node
		Node<T> *pCur;     // To traverse the list
		Node<T> *pPre;     // The previous node

		// Allocate a new node and store value there.
		newNode = new Node<T>;
		newNode->data = val;


		pPre = head;
		pCur = head->next;
		for (int i = 1; i < insertHere; i++) {
			pPre = pCur;
			pCur = pCur->next;
		}
		pPre->next = newNode;
		newNode->next = pCur;

		// Update the counter
		count++;
	}
	else
		insertLast(val);
}

/*****************************************************
Searches the list by data for placement

Create pointer Previous
Create pointer Current
Initialize int current to 0
Initialize bool found to false
Point Previous to head
Point Current to head->next
Print "Searching for nodes containing: (input value)"
While (Current doesn't point to NULL)
{
	Previous = Current
	Current = Current->next
	Add 1 to the current counter
	If (Previous->data == input value)
	{
		Print "Node (current) contains: (input value)"
		Set found to true
	}
}
If (found is false)
	Print "Could not locate: (input value)"
******************************************************/
template<typename T>
void LinkedList<T>::searchByDataForPlace(T val)
{
	Node<T> *pPre;		// The previous node
	Node<T> *pCur;		// To traverse the list
	int current = 0;	// Keeps track of what node we're on
	bool found = 0;		// To let the user know if it was found

	pPre = head;
	pCur = head->next;

	std::cout << "Searching for nodes containing: " << val << std::endl;

	while (pCur != nullptr)
	{
		pPre = pCur;
		pCur = pPre->next;
		current++;
		if (pPre->data == val) {
			std::cout << "Node (" << current << ") contains: " << val << std::endl;
			found = 1;
		}
	}

	if (!found)
		std::cout << "Could not locate: " << val << std::endl << std::endl;
	else
		std::cout << endl;
}

/*******************************************************
Searches the list by place for data

Print "Searching for data in node (location)"
If (If (location is head or location out of bounds)
{
	Print "Node (location) does not exist in this list."
	Return
}
Create pointer Previous
Create pointer Current
Initialize int current to 0
Point Previous to head
Point Current to head->next
For (each node up to target, update current++ each pass)
{
	Previous = Current
	Current = Current->next
{
Print "Node (current) contains: (input value)"
********************************************************/
template<typename T>
void LinkedList<T>::searchByPlaceForData(int findData)
{
	// See if the node exists
	std::cout << "Searching for data in node (" << findData << ")" << std::endl;
	if (findData < 1 || findData > count) {
		std::cout << "Node (" << findData << ") does not exist in this list.\n" << std::endl;
		return;
	}

	Node<T> *pPre;		// The previous node
	Node<T> *pCur;		// To traverse the list
	int current = 0;	// Keeps track of what node we're on

	pPre = head;
	pCur = head->next;

	// Traverse the list to the specified node
	for (current = 0; current < findData; current++) {
		pPre = pCur;
		pCur = pPre->next;
	}

	std::cout << "Node (" << current << ") contains: " << pPre->data << std::endl << std::endl;
}


/********************************************************************
Deletes node specified by place in the list

Print "Searching for node (location) to be deleted..."
If (If (location is head or location out of bounds)
{
	Print "Node (location) does not exist in this list."
	Return
}
Create pointer Previous
Create pointer Current
Initialize int current to 0
Point Previous to head
Point Current to head->next
For (each node to location, update current++ each pass)
{
	Previous = Current
	Current = Current->next
{
Point Previous->next to Current->next
Print "Deleting node (location) containing the data: (Current->data)"
Delete the node Current is pointing to
Subtract 1 from count counter
*********************************************************************/
template<typename T>
void LinkedList<T>::deleteNodeByPlace(int deleteThis)
{
	// See if the node exists
	std::cout << "Searching for node (" << deleteThis << ") to be deleted..." << std::endl;
	if (deleteThis < 1 || deleteThis > count) {
		std::cout << "Node (" << deleteThis << ") does not exist in this list.\n" << std::endl;
		return;
	}

	Node<T> *pPre;		// The previous node
	Node<T> *pCur;		// To traverse the list
	int current = 0;	// Keeps track of what node we're on

	pPre = head;
	pCur = head->next;

	// Traverse the list to the specified node
	for (current = 1; current < deleteThis; current++) {
		pPre = pCur;
		pCur = pPre->next;
	}

	// Connect previous node to next node
	pPre->next = pCur->next;
	std::cout << "Deleting node (" << deleteThis << ") containing the data: " << pCur->data << std::endl << std::endl;

	// Delete it
	delete pCur;
	count--;
}

/***************************************************************************
Deletes all nodes containing the specified data

Print "Deleting nodes containing: (input value)"
Create pointer Previous
Create pointer Current
Initialize int current to 1
Initialize bool deleted to false
Point Previous to head
Point Current to head->next
While (Current doesn't point to NULL)
{
	If (Current->data == input value)
	{
		Previous->next = Current->next
		Print "Deleting node (current) containing the data: (Current->data)"
		Delete the node Current is pointing to
		Point Current to Previous->next
		Subtract 1 from the count counter
		Add 1 to the current counter
	}
	Else
	{
		Point Previous to Current
		Point Current to Previous->next
		Add 1 to the current counter
	}
}
If (deleted is false)
	Print "No node found containing: (input value)"
****************************************************************************/
template<typename T>
void LinkedList<T>::deleteNodesByData(T deleteThis)
{
	// See if the node exists
	std::cout << "Deleting nodes containing: " << deleteThis << std::endl;

	Node<T> *pPre;		// The previous node
	Node<T> *pCur;		// To traverse the list
	int  current = 1;	// Keeps track of what node we're on
	bool deleted = 0;	// To tell the user if anything was deleted

	pPre = head;
	pCur = head->next;

	// Traverse the list to the specified node
	while (pCur != nullptr) {
		if (pCur->data == deleteThis) {
			// Connect previous node to next node
			pPre->next = pCur->next;
			std::cout << "Deleting node (" << current << ") containing the data: " << pCur->data << std::endl;

			// Delete it
			delete pCur;
			pCur = pPre->next;
			count--;
			deleted = 1;
			current++;
		}
		else {
			pPre = pCur;
			pCur = pPre->next;
			current++;
		}
	}
	if (!deleted)
		std::cout << "No node found containing: " << deleteThis << std::endl << std::endl;
	else
		std::cout << std::endl;
}

/***************************************************************************
Deletes all data nodes

If (list is empty)
{
	Print "There is nothing in the list!"
	Return
}
Print "Deleting all data nodes..."
Create pointer Current
Create pointer Next
Initialize int current to 1
Point Current to head->next
While (Current doesn't point to NULL)
{
	Point Next to Current->next
	Print "Deleting node (current) containing the data: (Current->data)"
	Delete the node Current is pointing to
	Point Current to Next->next
	Add 1 to the current counter
	Subtract 1 from the count counter
}
Point head->next to NULL
****************************************************************************/
template<typename T>
void LinkedList<T>::deleteAll()
{
	if (count == 0) {
		std::cout << "There is nothing in the list!\n" << std::endl;
		return;
	}

	std::cout << "Deleting all data nodes..." << std::endl;

	Node<T> *pCur;		// To traverse the list
	Node<T> *pNext;		// The node after pCur
	int current = 1;	// Keeps track of what node we're on

	pCur = head->next;

	while (pCur != nullptr) {
		pNext = pCur->next;
		std::cout << "Deleting node (" << current << ") containing the data: " << pCur->data << std::endl;
		delete pCur;
		pCur = pNext;
		current++;
		count--;
	}
	head->next = nullptr;

	std::cout << std::endl;
}

/***************************************************************************
Prints the list

If (list is empty)
{
	Print "There is nothing in the list!"
	Return
}
Create pointer Current
Initialize int current to 1
Point Current to head->next
While (Current doesn't point to NULL)
{
	Print "Node (current) contains: (Current->data)"
	Point Current to Current->next
	Add 1 to the current counter
}
****************************************************************************/
template<typename T>
void LinkedList<T>::print()
{
	if (count == 0) {
		std::cout << "There is nothing in the list!\n" << std::endl;
		return;
	}

	Node<T> *pCur;		// To move through the list
	int current = 1;	// Keeps track of what node we're on

						// Position pCur: skip the head of the list.
	pCur = head->next;

	// While pCur points to a node, traverse the list.
	while (pCur != nullptr)
	{
		// Display the value in this node.
		std::cout << "Node (" << current << ") contains: " << pCur->data << std::endl;

		// Move to the next node.
		pCur = pCur->next;
		current++;
	}
	std::cout << std::endl;
}

/*****************************************************************
Searches the list by data for placement (Currency)

Create pointer Previous
Create pointer Current
Initialize int current to 0
Initialize bool found to false
Point Previous to head
Point Current to head->next
Print "Searching for nodes containing: (input value)"
While (Current doesn't point to NULL)
{
	Previous = Current
	Current = Current->next
	Add 1 to the current counter
	If (Previous->data(Currency total) == input value(Currency Total)
	{
		Print "Node (current) contains: (input value)"
		Set found to true
	}
}
If (found is false)
	Print "Could not locate: (input value)"
******************************************************************/
template<typename T>
void LinkedList<T>::searchByCurrencyDataForPlace(T val)
{
	Node<T> *pPre;		// The previous node
	Node<T> *pCur;		// To traverse the list
	int current = 0;	// Keeps track of what node we're on
	bool found = 0;		// To let the user know if it was found

	pPre = head;
	pCur = head->next;

	std::cout << "Searching for nodes containing: " << val;

	while (pCur != nullptr)
	{
		pPre = pCur;
		pCur = pPre->next;
		current++;
		if (pPre->data.getTotal() == val.getTotal()) {
			std::cout << "Node (" << current << ") contains: " << val;
			found = 1;
		}
	}

	if (!found)
		std::cout << "Could not locate: " << val << std::endl;
	else
		std::cout << endl;
}

/***************************************************************************
Deletes all nodes containing the specified data (Currency)

Print "Deleting nodes containing: (input value)"
Create pointer Previous
Create pointer Current
Initialize int current to 1
Initialize bool deleted to false
Point Previous to head
Point Current to head->next
While (Current doesn't point to NULL)
{
	If (Current->data(Currency total) == input value(Currency total)
	{
		Previous->next = Current->next
		Print "Deleting node (current) containing the data: (Current->data)"
		Delete the node Current is pointing to
		Point Current to Previous->next
		Subtract 1 from the count counter
		Add 1 to the current counter
	}
	Else
	{
		Point Previous to Current
		Point Current to Previous->next
		Add 1 to the current counter
	}
}
If (deleted is false)
	Print "No node found containing: (input value)"
****************************************************************************/
template<typename T>
void LinkedList<T>::deleteCurrencyNodesByData(T deleteThis)
{
	// See if the node exists
	std::cout << "Deleting nodes containing: " << deleteThis;

	Node<T> *pPre;		// The previous node
	Node<T> *pCur;		// To traverse the list
	int  current = 1;	// Keeps track of what node we're on
	bool deleted = 0;	// To tell the user if anything was deleted

	pPre = head;
	pCur = head->next;

	// Traverse the list to the specified node
	while (pCur != nullptr) {
		if (pCur->data.getTotal() == deleteThis.getTotal()) {
			// Connect previous node to next node
			pPre->next = pCur->next;
			std::cout << "Deleting node (" << current << ") containing the data: " << pCur->data;

			// Delete it
			delete pCur;
			pCur = pPre->next;
			count--;
			deleted = 1;
			current++;
		}
		else {
			pPre = pCur;
			pCur = pPre->next;
			current++;
		}
	}
	if (!deleted)
		std::cout << "No node found containing: " << deleteThis << std::endl << std::endl;
	else
		std::cout << std::endl;
}

#endif