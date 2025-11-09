/******************************************************************

CIS 22C

Lab 3: This program demonstrates the abilities of Calculator with
the help of lab 2's and 2b's files. It takes a user-input
expression and evaluates the post-fix and pre-fix of the expression
by using the appropriate stack or queue operations.

Authors: Alexandria Liu
		 Stuart James Granville

Date: 5/10/19

*******************************************************************/
#include <iostream>
#include <string>
#include "Calculator.h"

using namespace std;

bool inputCheck(string expression); //Checks to make sure the expression can be evaluated in Calculator
string reverseFix(string forward); //Reverses the expression while keeping multiple digit numbers together and flips parenthesis

int main() {
	Calculator calc;
	string a;
	string expression;
	char response;
	bool check = 1;

	do {
		cout << "Enter a mathematical expression below (no exponents or roots).\nYou must use spaces after every operand and operator except the final one.\nMultiplication must be input with a *, you cannot use ( 2 ) ( 3 ) for example." << endl;
		getline(cin, expression);
		check = inputCheck(expression);
	} while (check == 0);

	do {
		cout << "\nChoose an option for this equation\na) Post-fix\nb) Pre-fix\nc) Enter a new equation\nq) Quit" << endl;
		cin >> response;
		cin.ignore(256, '\n');
		cin.clear();
		cout << endl;
		switch (response) {
		case 'a':
			cout << "Infix: " << expression << endl;
			a = expression;
			a = calc.toPostfix(a);
			cout << endl <<  "Postfix: " << a << endl << endl;
			cout << "Evaluation: " << calc.evaluatePostfix(a) << endl << endl;
			break;
		case 'b':
			cout << "Infix: " << expression << endl;
			a = reverseFix(expression);
			cout << endl << "Infix Backwards: " << a << endl;
			cout << endl << "Postfix: " << calc.reverseToPostfix(a) << endl;
			a = calc.reverseToPostfix(a);
			a = reverseFix(a);
			cout << "Prefix: " << a << endl << endl;
			cout << "Evaluation: " << calc.evaluatePrefix(a) << endl << endl;
			break;
		case 'c':
			do {
				cout << "Enter a mathematical expression below (no exponents or roots).\nYou must use spaces after every operand and operator except the final one.\nMultiplication must be input with a *, you cannot use ( 2 ) ( 3 ) for example." << endl;
				getline(cin, expression);
				check = inputCheck(expression);
			} while (check == 0);
			break;
		case 'q':
			break;
		default:
			cout << "You did not select an option." << endl;
			break;
		}
	} while (response != 'q');

	system("pause");
	return 0;
}

/*******************************************************************************************************************
Take string expression from input
Create bool check preset to true
Create separate counts for open and close parenthesis

If the expression does not start with a number or open parenthesis
	Set check to false

If the check is false, skip the following loop
Run a scan through the string expression { 
	For each digit,
		check if there is a digit after, a space after or if the expression ends
			if none of those are the case, set check to false

	For each close parenthesis,
		add one to the count of close parenthesis
		check if there is a space after or if the expression ends
			if neither is the case, set check to false
		else if either is the case, check if the expression is followed by a space followed by a closed parenthesis
			if true, set check to false (cannot multiply by using parenthesis next to parenthesis)

	For each operator,
		check if it is a valid operator
			if it is not, set check to false
		else if it is, check if there is a space after
			if there is not, set check to false
		else if there is, check if there is a digit or open parenthesis following the space after it
			if there is not, set check to false
		else if there is, check if the operator is an open parenthesis
			if it is, add one to the count of open parenthesis
}

Check if the counts of open and close parenthesis are equal
	if they aren't, set check to false

If the check is false, tell the user the expression is mal-formed

Return check
*******************************************************************************************************************/
bool inputCheck(string expression)
{
	bool check = 1;
	int closeCount = 0;
	int openCount = 0;

	if (!isdigit(expression[0]) && expression[0] != '(') {
		cout << "You cannot start the equation with a space or operator.\nValid starting characters are numbers or an open parenthesis." << endl;
		check = 0;
	}

	if (check != 0) {
		for (unsigned int i = 0; i < expression.length(); i++) {
			if (isdigit(expression[i])) {
				if (!isdigit(expression[i + 1]) && !isspace(expression[i + 1]) && expression[i + 1] != NULL) {
					cout << "You did not put a space after one of the numbers inputted." << endl;
					check = 0;
				}
			}
			else if (expression[i] == ')') {
				closeCount++;
				if (!isspace(expression[i + 1]) && expression[i + 1] != NULL) {
					cout << "You did not put a space after the closed parenthesis." << endl;
					check = 0;
				}
				else if (expression[i + 1] != NULL) {
					if (expression[i + 2] == '(') {
						cout << "Multiplication must be input with a *, you cannot use ( 2 ) ( 3 ) for example." << endl;
						check = 0;
					}
				}
			}
			else if (ispunct(expression[i])) {
				if (expression[i] != '+' && expression[i] != '-' && expression[i] != '*' && expression[i] != '/' && expression[i] != '%' && expression[i] != '(') {
					cout << "You input an invalid operator." << endl;
					check = 0;
				}
				else if (!isspace(expression[i + 1])) {
					cout << "You did not put a space after the operator or open parenthesis." << endl;
					check = 0;
				}
				else if (expression[i + 2] != '(' && !isdigit(expression[i + 2])) {
					cout << "You did not put a digit or open parenthesis following the space after the operator/open parenthesis." << endl;
					check = 0;
				}
				if (expression[i] == '(')
					openCount++;
			}
			else if (isspace(expression[i])) {
				if (!isdigit(expression[i + 1]) && !ispunct(expression[i + 1])) {
					cout << "You input two or more spaces consecutively." << endl;
					check = 0;
				}
			}
		}
	}

	if (closeCount != openCount) {
		cout << "You did not close your parenthesis." << endl;
		check = 0;
	}

	if (check == 0) {
		cout << endl << "Expression mal-formed, try again." << endl << endl;
	}

	return check;
}

/********************************************************************************************************
Take string expression from input (referred to as forward in this function)
Create string backward
Create string groupNum to group numbers containing 2 or more digits

Run a for loop through the characters of string forward {
	if the character is a number, add it to groupNum
	else if there is a space
		if groupNum is not empty
			add groupNum to the start of the backward expression
			if the forward expression isn't empty, add a space to the start of the backward expression
			set groupNum to ""
		else if the forward expression isn't empty
			add a space to the start of the backward expression
	else if the character is an open parenthesis,
		flip it and add it to the start of the backward expression
	else if the character is a close parenthesis,
		flip it and add it to the start of the backward expression
	else if the character is an operator
		add it to the start backward expression
}
********************************************************************************************************/
string reverseFix(string forward)
{
	string backward;
	string groupNum;

	for (unsigned int i = 0; i <= forward.length(); i++) {
		if (isdigit(forward[i])) {
			groupNum += forward[i];
		}
		else if (isspace(forward[i]) || forward[i] == NULL) {
			if (groupNum != "") {
				backward.insert(0, groupNum);
				if (forward[i] != NULL) {
					backward.insert(0, 1, forward[i]);
				}
				groupNum = "";
			}
			else if (forward[i] != NULL) {
				backward.insert(0, 1, forward[i]);
			}
		}
		else if (forward[i] == ')') {
			backward.insert(0, "(");
		}
		else if (forward[i] == '(') {
			backward.insert(0, ")");
		}
		else if (ispunct(forward[i])) {
			backward.insert(0, 1, forward[i]);
		}
	}

	return backward;
}