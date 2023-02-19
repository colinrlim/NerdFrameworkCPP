#include <stack>
#include <queue>
#include "MathParser.h"
#include "MathNode.h"

MathParser::Item MathParser::getNextOperator(const char* string, size_t size) {
	switch (string[0]) {
	case '(':
	case ')':
	case ',':
	case '|':
		return Item(string, 0, 1, 0);
	case '+':
		return Item(string, 1, 1, 1);
	case '-':
		return Item(string, 1, 1, 2);
	case '*':
	case '×':
		return Item(string, 2, 1, 3);
	case '/':
	case '÷':
		return Item(string, 2, 1, 4);
	case '%':
		return Item(string, 2, 1, 5);
	case '^':
		return Item(string, 3, 1, 6);
	case '!':
		return Item(string, 90, 1, 20);
	case '=':
		return Item(string, 99, 1, 99);
	case 'π':
		return Item(string, -1, 1, -4);
	}
	if (size >= 7) {
		if (strncmp(string, "ceiling", 7) == 0)
			return Item(string, 90, 7, 31);
	}
	if (size >= 6) {
		if (strncmp(string, "arc", 3) == 0) {
			if (strncmp(string + 3, "sin", 3) == 0)
				return Item(string, 90, 6, 8);
			else if (strncmp(string + 3, "cos", 3) == 0)
				return Item(string, 90, 6, 9);
			else if (strncmp(string + 3, "tan", 3) == 0)
				return Item(string, 90, 6, 10);
		}
	}
	if (size >= 5) {
		if (strncmp(string, "floor", 5) == 0)
			return Item(string, 90, 5, 32);
	}
	if (size >= 4) {
		if (string[0] == 'a') {
			if (strncmp(string + 1, "sin", 3) == 0)
				return Item(string, 90, 4, 8);
			else if (strncmp(string + 1, "cos", 3) == 0)
				return Item(string, 90, 4, 9);
			else if (strncmp(string + 1, "tan", 3) == 0)
				return Item(string, 90, 4, 10);
		} else if (strncmp(string, "ceil", 3) == 0)
			return Item(string, 90, 4, 31);
	}
	if (size >= 3) {
		if (strncmp(string, "e_0", 3) == 0)
			return Item(string, -1, 3, -5);
		else if (strncmp(string, "sin", 3) == 0)
			return Item(string, 90, 3, 11);
		else if (strncmp(string, "cos", 3) == 0)
			return Item(string, 90, 3, 12);
		else if (strncmp(string, "tan", 3) == 0)
			return Item(string, 90, 3, 13);
		else if (strncmp(string, "csc", 3) == 0)
			return Item(string, 90, 3, 14);
		else if (strncmp(string, "sec", 3) == 0)
			return Item(string, 90, 3, 15);
		else if (strncmp(string, "cot", 3) == 0)
			return Item(string, 90, 3, 16);
		else if (strncmp(string, "log", 3) == 0)
			return Item(string, 90, 3, 17);
		else if (strncmp(string, "abs", 3) == 0)
			return Item(string, 90, 3, 19);
		else if (strncmp(string, "max", 3) == 0)
			return Item(string, 90, 3, 31);
		else if (strncmp(string, "min", 3) == 0)
			return Item(string, 90, 3, 32);
		else if (strncmp(string, "mod", 3) == 0)
			return Item(string, 90, 3, 33);
	}
	if (size >= 2) {
		if (strncmp(string, "pi", 2) == 0)
			return Item(string, -1, 2, -4);
		else if (strncmp(string, "e0", 2) == 0)
			return Item(string, -1, 2, -5);
		else if (strncmp(string, "ln", 2) == 0)
			return Item(string, 90, 2, 18);
	}
	if (size >= 1) {
		if (string[0] == 'e')
			return Item(string, -1, 1, -3);
	}
	size_t i = 0;
	while (i != size && ((string[i] >= '0' && string[i] <= '9') || string[i] == '.' || (i != 0 && (string[i] == 'e' || (string[i] == '-' && string[i-1] == 'e'))))) {
		i++;
	}
	return i == 0 ? Item(string, -1, 1, -2) : Item(string, -1, i, -1);
}

MathNode* MathParser::toExpressionTree(const char* string, size_t size) {
	
	/* Transform string to postfix notation, using Shunting-Yard Algorithm */
	std::stack<Item> stack;
	std::queue<Item> queue;

	bool openAbsolute = false;

	size_t i = 0;
	while (i != size) { // Tokenize string, iterate through all tokens
		if (string[i] == ' ') {
			i++;
			continue;
		}
		Item token = getNextOperator(string + i, size - i);
		if (token.precedence < 0) // Token is a number
			queue.push(token); // Push to queue
		else if (token.precedence == 90 || token.ptr[0] == '(') // Token is a function or a left-parentheses
			stack.push(token); // Push to stack
		else if (token.ptr[0] == '|' && !openAbsolute) { // Token is an open-modulus bar
			openAbsolute = true; // Set flag
			stack.push(Item("abs", 90, 3, 19)); // Push modulus function to stack
			stack.push(token); // Push bar to stack
		} else if (token.precedence > 0) { // Token is an operator
			// While top of stack exists and isn't a left-parentheses, and
			//   the top of the stack has a higher precedence than the current token, or
			//   the top of the stack and the current token has the same precedence and is left associative (not ^),
			//   move it to the queue
			// Afterwards, push the token to the stack
			while ((!stack.empty() && stack.top().ptr[0] != '(')
				&& (stack.top().precedence > token.precedence || (stack.top().precedence == token.precedence && token.ptr[0] != '^'))) {
				queue.push(stack.top());
				stack.pop();
			}
			stack.push(token);
		} else if (token.ptr[0] == ')' || token.ptr[0] == ',') { // Token is a right-parentheses or argument delimiter (comma)
			// Disable openAbsolute flag if enabled
			openAbsolute = false;
			// Keep moving the top of stack to the queue until the top of the stack is a left-parentheses
			// Then discard both left and right parentheses
			// If final top of stack is a function, push it to queue too
			while (!stack.empty() && stack.top().ptr[0] != '(') {
				queue.push(stack.top());
				stack.pop();
			}
			if (stack.empty())
				return nullptr;
			if (token.ptr[0] != ',') // Don't discard left-parentheses if token is just an argument delimiter!
				stack.pop();
			if (!stack.empty() && (stack.top().precedence == 90)) {
				queue.push(stack.top());
				stack.pop();
			}
		} else if (token.ptr[0] == '|') { // Token is a close-modulus bar
			// Disable openAbsolute flag
			openAbsolute = false;
			// Keep moving the top of stack to the queue until the top of the stack is an open-modulus bar
			while (!stack.empty() && stack.top().ptr[0] != '|') {
				queue.push(stack.top());
				stack.pop();
			}
			if (stack.empty())
				return nullptr;
			// Then discard both modulus bars
			stack.pop();
			// Push absolute function to the queue afterwards
			queue.push(stack.top());
			stack.pop();
		}
		i += token.size;
	}

	// Move whatever remains in the stack to the queue
	while (!stack.empty()) {
		if (stack.top().ptr[0] == '(')
			return nullptr;
		queue.push(stack.top());
		stack.pop();
	}

	std::stack<MathNode*> treeStack;

	/* Transform postfix notation to expression tree */
	while (!queue.empty()) {
		char* ptr_end = (char*)queue.front().ptr + queue.front().size - 1;
		if (queue.front().precedence < 0) { // Token is a variable or number
			if (queue.front().id == -1) // Token is a number
				treeStack.push(new ValueNode(std::strtod(queue.front().ptr, &ptr_end))); // Parse and push to stack
			/* Token is a constant */
			else if (queue.front().id == -3)
				treeStack.push(new E_Node());
			else if (queue.front().id == -4)
				treeStack.push(new PI_Node());
			else if (queue.front().id == -5)
				treeStack.push(new EPSILON_NAUGHT_Node());
			else // Token is a variable
				treeStack.push(new VariableNode(std::string(queue.front().ptr, queue.front().size)));
		} else { // Token is an operator or function
			if (queue.front().precedence == 90 && queue.front().id <= 30) { // Token is a unary function
				if (treeStack.empty())
					return nullptr;
				// Pop inner argument from stack
				MathNode* inner = treeStack.top();
				treeStack.pop();

				/* Push operator or function node to stack, w/ inner argument */
				switch (queue.front().id) {
				case 8:
					treeStack.push(new ArcSineNode(inner));
					break;
				case 9:
					treeStack.push(new ArcCosineNode(inner));
					break;
				case 10:
					treeStack.push(new ArcTangentNode(inner));
					break;
				case 11:
					treeStack.push(new SineNode(inner));
					break;
				case 12:
					treeStack.push(new CosineNode(inner));
					break;
				case 13:
					treeStack.push(new TangentNode(inner));
					break;
				case 14:
					treeStack.push(new CosecantNode(inner));
					break;
				case 15:
					treeStack.push(new SecantNode(inner));
					break;
				case 16:
					treeStack.push(new CotangentNode(inner));
					break;
				case 17:
					treeStack.push(new LogNode(inner));
					break;
				case 18:
					treeStack.push(new LnNode(inner));
					break;
				case 19:
					treeStack.push(new ModulusNode(inner));
					break;
				case 20:
					treeStack.push(new FactorialNode(inner));
					break;
				}
			} else { // Token is an operator or bivariate function
				if (treeStack.size() < 2)
					return nullptr;
				// Pop lhs and rhs arguments from stack
				MathNode* rhs = treeStack.top();
				treeStack.pop();
				MathNode* lhs = treeStack.top();
				treeStack.pop();

				/* Push operator or function node to stack, w/ inner lhs and rhs arguments */
				switch (queue.front().id) {
				case 1:
					treeStack.push(new AddNode(lhs, rhs));
					break;
				case 2:
					treeStack.push(new SubtractNode(lhs, rhs));
					break;
				case 3:
					treeStack.push(new MultiplyNode(lhs, rhs));
					break;
				case 4:
					treeStack.push(new DivideNode(lhs, rhs));
					break;
				case 5:
					treeStack.push(new ModuloNode(lhs, rhs));
					break;
				case 6:
					treeStack.push(new ExponentNode(lhs, rhs));
					break;
				case 99:
					treeStack.push(new EqualsNode(lhs, rhs));
					break;
				case 31:
					treeStack.push(new MaxNode(lhs, rhs));
					break;
				case 32:
					treeStack.push(new MinNode(lhs, rhs));
					break;
				case 33:
					treeStack.push(new ModuloNode(lhs, rhs));
					break;
				}
			}
		}
		// Iterate to next token in queue
		queue.pop();
	}

	// There should now be only one node left in the stack, which is the head node
	// > We did it boys
	return treeStack.top();
}