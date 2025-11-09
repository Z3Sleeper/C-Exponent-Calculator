#include "Calculator.h"

Calculator::Calculator() {
}

Calculator::~Calculator() {
}


/************************************************************************************************
for (int i = 0; i < the string size; i++){
if (char selected is a space or a punct)
add the number to the queue
if (char selected is punct)
if (the stack is not empty)
if ')'
pop until )

else
if '('
add it to the stack

else
if (check priority)
add punct to stack

else
add punct onto the stack without any checks

else
combine the number to the previous number to form double digits or triple digits etc.
}
add whatever number is left in the variable to the queue
if anything is left in stack, pop.
put all of queue in a string.
*********************************************************************************************/
std::string Calculator::toPostfix(std::string infix) {
	DynStackNode<std::string> operationStack;
	DynQueue<std::string> postfixQueue;

	std::string postfix;
	std::string groupNum;
	int size = infix.length();

	std::stringstream m;
	std::string temp;

	for (int i = 0; i < size; i++) {
		if (isspace(infix[i]) || ispunct(infix[i])) {
			postfixQueue.enqueue(groupNum);

			if (isspace(infix[i]) && !ispunct(infix[i - 1])) {
				postfixQueue.enqueue(" ");
			}

			if (ispunct(infix[i])) {
				//if the stack is not empty, do a bunch of tests
				if (!operationStack.isEmpty()) {
					if (infix[i] == ')') {
						//pop until (
						while (operationStack.topVal() != "(") {
							postfixQueue.enqueue(operationStack.topVal());
							postfixQueue.enqueue(" ");
							operationStack.pop();
						}
						operationStack.pop(); // pops the (
					}
					else {
						if (infix[i] == '(') {
							m << infix[i];
							m >> temp;
							operationStack.push(temp);
							m.clear();
						}
						else {
							temp = operationStack.topVal();
							for (int j = 0; j < 2; j++) {//only two levels of priority. Only need to check two times.
								if (!operationStack.isEmpty()) {

									if (Priority(infix[i]) <= Priority(temp.at(0))) {
										//if the top of the stack is higher or equal value, the operator can't be push on top. POP !
										postfixQueue.enqueue(operationStack.topVal());
										postfixQueue.enqueue(" ");
										operationStack.pop();
										if (!operationStack.isEmpty()) {
											temp = operationStack.topVal();
										}
									}
								}
							}
							//after checking if it can be place on the stack; add it onto the top of the stack
							m << infix[i];
							m >> temp;
							operationStack.push(temp);
							m.clear();
						}
					}
				}
				//if the stack is empty, just add it onto the stack. No need to check anything
				else {
					m << infix[i];
					m >> temp;
					operationStack.push(temp);
					m.clear();
				}
			}

			groupNum = ""; //resets groupNum
		}
		else {
			groupNum += infix[i];
		}
	}
	postfixQueue.enqueue(groupNum);

	//after going through all the infix; if there is something in the stack still; pop them all
	while (!operationStack.isEmpty()) {
		postfixQueue.enqueue(" ");
		postfixQueue.enqueue(operationStack.topVal());
		operationStack.pop();
	}

	int length = postfixQueue.size();
	for (int i = 0; i < length; i++) {
		postfixQueue.dequeue(temp);
		postfix += temp;
	}

	return postfix;
}






/**********************************************************************************
group all the numbers together
push the numbers onto the stack when a space is reached
if it's an operator; go through switch to calculate the numbers with the selected operator
after calculating it and push the number back on the stack

return the result
**********************************************************************************/
std::string Calculator::evaluatePostfix(std::string postfix) {
	DynStackNode<int> numStack;
	std::stringstream str;
	std::string result;

	int slot1, slot2;
	int temp;
	int size = postfix.length();
	std::string groupNum;

	for (int i = 0; i < size; i++) {
		if (isdigit(postfix[i])) {
			groupNum += postfix[i];
		}
		if (isspace(postfix[i])) {
			if (groupNum != "") {
				str << groupNum;
				str >> temp;
				numStack.push(temp);
				str.clear();
				groupNum = "";
			}
		}
		if (ispunct(postfix[i])) {
			//format: slot1 (operations) slot2 = answer
			slot2 = numStack.topVal();
			numStack.pop();
			slot1 = numStack.topVal();
			numStack.pop();

			switch (postfix[i]) {
			case '-':
				temp = slot1 - slot2;
				numStack.push(temp);
				break;
			case '+':
				temp = slot1 + slot2;
				numStack.push(temp);
				break;
			case '*':
				temp = slot1 * slot2;
				numStack.push(temp);
				break;
			case '/':
				temp = slot1 / slot2;
				numStack.push(temp);
				break;
			case '%':
				temp = slot1 % slot2;
				numStack.push(temp);
				break;
			default:
				break;
			}
		}
	}
	str << numStack.topVal();
	str >> result;

	return result;
}





/******************************************************************
//larger the number, the larger the priority it is

//level one is:		- +
//level two is:		* / %
//level three is:	^
******************************************************************/
int Calculator::Priority(char operations) {
	if (operations == '(') {
		return 0;
	}
	if (operations == '-' || operations == '+') {
		return 1;
	}
	if (operations == '*' || operations == '/' || operations == '%') {
		return 2;
	}
}



/********************************************************************
Same thing as toPostfix function but for infix to prefix. Goes
through the string, and checks for punct, parenthesis, and numbers.
Numbers are placed onto the queue; everything else is placed on the
stack. The difference from this function to the toPostfix function
is that instead of equal or higher priority, it tests if it is only
higher priority.

********************************************************************/
std::string Calculator::reverseToPostfix(std::string infix) {
	DynStackNode<std::string> operationStack;
	DynQueue<std::string> postfixQueue;

	std::string postfix;
	std::string groupNum;
	int size = infix.length();

	std::stringstream m;
	std::string temp;

	for (int i = 0; i < size; i++) {
		if (isspace(infix[i]) || ispunct(infix[i])) {
			postfixQueue.enqueue(groupNum);

			if (isspace(infix[i]) && !ispunct(infix[i - 1])) {
				postfixQueue.enqueue(" ");
			}

			if (ispunct(infix[i])) {
				//if the stack is not empty, do a bunch of tests
				if (!operationStack.isEmpty()) {
					if (infix[i] == ')') {
						//pop until (
						while (operationStack.topVal() != "(") {
							postfixQueue.enqueue(operationStack.topVal());
							postfixQueue.enqueue(" ");
							operationStack.pop();
						}
						operationStack.pop(); // pops the (
					}
					else {
						if (infix[i] == '(') {
							m << infix[i];
							m >> temp;
							operationStack.push(temp);
							m.clear();
						}
						else {
							temp = operationStack.topVal();
							for (int j = 0; j < 2; j++) {//only two levels of priority. Only need to check two times.
								if (!operationStack.isEmpty()) {

									if (Priority(infix[i]) < Priority(temp.at(0))) {
										//if the top of the stack is higher value, the operator can't be push on top. POP !
										postfixQueue.enqueue(operationStack.topVal());
										postfixQueue.enqueue(" ");
										operationStack.pop();
										if (!operationStack.isEmpty()) {
											temp = operationStack.topVal();
										}
									}
								}
							}
							//after checking if it can be place on the stack; add it onto the top of the stack
							m << infix[i];
							m >> temp;
							operationStack.push(temp);
							m.clear();
						}
					}
				}
				//if the stack is empty, just add it onto the stack. No need to check anything
				else {
					m << infix[i];
					m >> temp;
					operationStack.push(temp);
					m.clear();
				}
			}
			groupNum = ""; //resets groupNum
		}
		else {
			groupNum += infix[i];
		}
	}
	postfixQueue.enqueue(groupNum);

	//after going through all the infix; if there is something in the stack still; pop them all
	while (!operationStack.isEmpty()) {
		postfixQueue.enqueue(" ");
		postfixQueue.enqueue(operationStack.topVal());
		operationStack.pop();
	}

	int length = postfixQueue.size();
	for (int i = 0; i < length; i++) {
		postfixQueue.dequeue(temp);
		postfix += temp;
	}

	return postfix;
}


/**********************************************************************************
go through the entire string.
push numbers and operators onto the stack.
when there are two numbers stacked ontop of each other, calculate it with the
operator beneath them by using a switch function.
after calculating it and push the number back on the stack

return the result
**********************************************************************************/
std::string Calculator::evaluatePrefix(std::string postfix) {
	DynStackNode<std::string> stack;
	std::stringstream str;
	std::string result;
	std::string temp;
	std::string groupNum;
	int slot1;
	int slot2;
	int size = postfix.length();
	int count = 0;
	char opTemp;
	int length;
	int answer;
	int opCount = 0;

	for (int i = 0; i < size; i++) {

		if (ispunct(postfix[i])) {
			str << postfix[i];
			str >> temp;
			stack.push(temp);
			str.clear();
			count = 0;
			opCount++;
		}

		if (isdigit(postfix[i])) {
			groupNum += postfix[i];
		}

		if (isspace(postfix[i]) || postfix[i + 1] == NULL) {
			if (groupNum != "") {
				str << groupNum;
				str >> temp;
				stack.push(temp);
				str.clear();
				groupNum = "";
				count++;
			}
		}

		while ((count == 2 || postfix[i + 1] == NULL) && opCount >= 1) {
			//format: slot1 (opTemp) slot2 = answer
			temp = stack.topVal();
			str << temp;
			str >> slot2;
			str.clear();
			stack.pop();
			temp = stack.topVal();
			str << temp;
			str >> slot1;
			str.clear();
			stack.pop();
			temp = stack.topVal();
			str << temp;
			str >> opTemp;
			str.clear();
			stack.pop();

			if (postfix[i + 1] != NULL) {
				temp = stack.topVal();
				length = temp.length();
				for (int z = 0; z < length; z++) {
					if (isdigit(temp[z]))
						count++;
				}
			}

			switch (opTemp) {
			case '-':
				answer = slot1 - slot2;
				str << answer;
				str >> temp;
				str.clear();
				stack.push(temp);
				break;
			case '+':
				answer = slot1 + slot2;
				str << answer;
				str >> temp;
				str.clear();
				stack.push(temp);
				break;
			case '*':
				answer = slot1 * slot2;
				str << answer;
				str >> temp;
				str.clear();
				stack.push(temp);
				break;
			case '/':
				answer = slot1 / slot2;
				str << answer;
				str >> temp;
				str.clear();
				stack.push(temp);
				break;
			case '%':
				answer = slot1 % slot2;
				str << answer;
				str >> temp;
				str.clear();
				stack.push(temp);
				break;
			default:
				break;
			}
			count--;
			opCount--;
		}
	}

	str << stack.topVal();
	str >> result;

	return result;
}