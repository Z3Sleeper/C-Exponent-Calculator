#ifndef Calculator_h
#define Calculator_h
#include <string>
#include <iostream>
#include <cctype>
#include <sstream>
#include "StackADT.h"
#include "QueueADT.h"

class Calculator {
private:


public:
	Calculator();
	~Calculator();

	/*************************************************************************
	This function changes the infix expression to postfix

	Pre: string infix - a math expression in the infix format
	Post:
	Return: math expression in postfix format
	*************************************************************************/
	std::string toPostfix(std::string infix);

	/*************************************************************************
	This function solves the math expression that is in the postfix format

	Pre: string postfix - a math expression in the postfix format
	Post:
	Return: answer to the math expression
	*************************************************************************/
	std::string evaluatePostfix(std::string postfix);

	/*************************************************************************
	This function is used to help change infix to prefix. It does it by
	changing the reversed infix expression to a postfix format.

	Pre: string infix - a math expression in the infix form
	Post:
	Return: math expression in postfix form
	*************************************************************************/
	std::string reverseToPostfix(std::string infix);

	/*************************************************************************
	This function solves the math expression in the prefix format

	Pre: string postfix - a reversed math expression in the postfix form
	Post:
	Return: answer to the math expression
	*************************************************************************/
	std::string evaluatePrefix(std::string postfix);

	/*************************************************************************
	This function determines the priority of operators.

	Pre: char operations - operator
	Post:
	Return: 0, 1, or 2 depending on the operator.
	*************************************************************************/
	int Priority(char operations);
};

#endif