#ifndef NODEADT_H
#define NODEADT_H

template<typename T>
struct Node{
	T data;			// object information
	Node<T> *next;	// pointer to the next node element
};

#endif