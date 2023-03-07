#include <stack>
#include <queue>
#include "MathParser.h"
#include "MathNode.h"

MathParser::Item MathParser::getNextOperator(const char* string, size_t size) {
	if (size >= 2) {
		if (substreq(string, "//", 2))
			return Item(string, 3, 2, 7);
		if (substreq(string, "**", 2))
			return Item(string, 4, 2, 6);
	}
	switch (string[0]) {
	case '(':
	case ')':
	case ',':
	case '|':
		return Item(string, 0, 1, 0);
	case '+':
		return Item(string, 2, 1, 1);
	case '-':
		return Item(string, 2, 1, 2);
	case '*':
	case '×':
		return Item(string, 3, 1, 3);
	case '/':
	case '÷':
		return Item(string, 3, 1, 4);
	case '%':
		return Item(string, 3, 1, 5);
	case '^':
		return Item(string, 4, 1, 6);
	case '!':
		return Item(string, 90, 1, 20);
	case '=':
		return Item(string, 1, 1, 99);
	case 'π':
		return Item(string, -1, 1, -4);
	case 'G':
		return Item(string, -1, 1, -12);
	}
	int alphaLength = 0;
	while (string[alphaLength] >= '_' && string[alphaLength] <= 'z' || string[alphaLength] >= '0' && string[alphaLength] <= '9') {
		alphaLength++;
	}
	if (alphaLength >= 7) {
		if (substreq(string, "ceiling", 7))
			return Item(string, 90, 7, 22);
	}
	if (alphaLength >= 6) {
		if (substreq(string, "arc", 3)) {
			if (substreq(string + 3, "sin", 3))
				return Item(string, 90, 6, 8);
			else if (substreq(string + 3, "cos", 3))
				return Item(string, 90, 6, 9);
			else if (substreq(string + 3, "tan", 3))
				return Item(string, 90, 6, 10);
		}
	}
	if (alphaLength >= 5) {
		if (substreq(string, "floor", 5))
			return Item(string, 90, 5, 23);
		else if (substreq(string, "round", 5))
			return Item(string, 90, 5, 21);
	}
	if (alphaLength >= 4) {
		if (string[0] == 'a') {
			if (substreq(string + 1, "sin", 3))
				return Item(string, 90, 4, 8);
			else if (substreq(string + 1, "cos", 3))
				return Item(string, 90, 4, 9);
			else if (substreq(string + 1, "tan", 3))
				return Item(string, 90, 4, 10);
		}
		else if (substreq(string, "ceil", 3))
			return Item(string, 90, 4, 22);
	}
	if (alphaLength >= 3) {
		if (substreq(string, "e_0", 3))
			return Item(string, -1, 3, -5);
		else if (substreq(string, "sin", 3))
			return Item(string, 90, 3, 11);
		else if (substreq(string, "cos", 3))
			return Item(string, 90, 3, 12);
		else if (substreq(string, "tan", 3))
			return Item(string, 90, 3, 13);
		else if (substreq(string, "csc", 3))
			return Item(string, 90, 3, 14);
		else if (substreq(string, "sec", 3))
			return Item(string, 90, 3, 15);
		else if (substreq(string, "cot", 3))
			return Item(string, 90, 3, 16);
		else if (substreq(string, "log", 3))
			return Item(string, 90, 3, 17);
		else if (substreq(string, "abs", 3))
			return Item(string, 90, 3, 19);
		else if (substreq(string, "max", 3))
			return Item(string, 90, 3, 31);
		else if (substreq(string, "min", 3))
			return Item(string, 90, 3, 32);
		else if (substreq(string, "mod", 3))
			return Item(string, 90, 3, 33);
		else if (substreq(string, "lcm", 3))
			return Item(string, 90, 3, 34);
		else if (substreq(string, "gcd", 3))
			return Item(string, 90, 3, 35);
		else if (substreq(string, "m_p", 3))
			return Item(string, -1, 3, -7);
		else if (substreq(string, "m_n", 3))
			return Item(string, -1, 3, -8);
		else if (substreq(string, "m_e", 3))
			return Item(string, -1, 3, -9);
		else if (substreq(string, "q_e", 3))
			return Item(string, -1, 3, -10);
		else if (substreq(string, "m_0", 3))
			return Item(string, -1, 3, -14);
	}
	if (alphaLength >= 2) {
		if (substreq(string, "pi", 2))
			return Item(string, -1, 2, -4);
		else if (substreq(string, "e0", 2))
			return Item(string, -1, 2, -5);
		else if (substreq(string, "m0", 2))
			return Item(string, -1, 2, -14);
		else if (substreq(string, "ln", 2))
			return Item(string, 90, 2, 18);
	}
	if (alphaLength >= 1) {
		switch (string[0]) {
		case 'e':
			return Item(string, -1, 1, -3);
		case 'k':
			return Item(string, -1, 1, -6);
		case 'c':
			return Item(string, -1, 1, -11);
		case 'g':
			return Item(string, -1, 1, -13);
		}
	}
	size_t i = 0;
	while (i != size && ((string[i] >= '0' && string[i] <= '9') || string[i] == '.' || (i != 0 && ((string[i] == 'e' && i+1 != size && (string[i+1] == '-' || (string[i+1] >= '0' && string[i+1] <= '9'))) || (string[i] == '-' && string[i - 1] == 'e'))))) {
		i++;
	}
	if (i > 0)
		return Item(string, -1, i, -1);
	if (alphaLength > 2 && string[1] == '_')
		return Item(string, -1, alphaLength, -2);
	return Item(string, -1, 1, -2);
}

MathNode* MathParser::toExpressionTree(const char* string, size_t size) {
	
	/* Token flags */
	bool openAbsolute = false;

	/* Transform string to postfix notation, using Shunting-Yard Algorithm */
	std::stack<Item> stack;
	std::queue<Item> queue;

	char lastToken = '(';
	char lastTokenPrecedence = 0;

	size_t i = 0;
	while (i != size) { // Tokenize string, iterate through all tokens
		if (string[i] == ' ') {
			i++;
			continue;
		}
		const char* tokenStart = string + i;
		const Item token = getNextOperator(tokenStart, size - i);

		/* Allow implicit multiplication*/
		if ((lastToken == ')' || (lastToken == '|' && !openAbsolute) || lastTokenPrecedence < 0)
			&& (token.ptr[0] == '(' || (token.ptr[0] == '|' && !openAbsolute) || token.precedence < 0 || token.precedence == 90)) {
			while ((!stack.empty() && stack.top().ptr[0] != '(' && stack.top().ptr[0] != '|')
				&& (stack.top().precedence >= 2)) {
				queue.push(stack.top());
				stack.pop();
			}
			stack.push(Item("*", 2, 1, 3));
		}
		
		/* Allow negative starting numbers */
		if (lastToken == '(' || (lastToken == '|' && openAbsolute) || (lastTokenPrecedence > 0 && lastTokenPrecedence != 90)) {
			if (token.id == 2) {
				queue.push(Item("-1", -1, 2, -1));
				stack.push(Item("*", 80, 1, 3));
				i += token.size;
				continue;
			}
		}

		if (token.precedence < 0) { // Token is a number
			queue.push(token); // Push number to queue
		} else if (token.precedence == 90 || token.ptr[0] == '(') { // Token is a function or a left-parentheses
			stack.push(token); // Push to stack
		} else if (token.ptr[0] == '|' && !openAbsolute) { // Token is an open-modulus bar
			openAbsolute = true; // Set flag
			stack.push(Item("abs", 90, 3, 19)); // Push modulus function to stack
			stack.push(token); // Push bar to stack
		} else if (token.precedence > 0) { // Token is an operator
			// While top of stack exists and isn't a left-parentheses, and
			//   the top of the stack has a higher precedence than the current token, or
			//   the top of the stack and the current token has the same precedence and is left associative (not ^),
			//   move it to the queue
			// Afterwards, push the token to the stack
			while ((!stack.empty() && stack.top().ptr[0] != '(' && stack.top().ptr[0] != '|')
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
		lastToken = token.ptr[0];
		lastTokenPrecedence = token.precedence;
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
			switch (queue.front().id) {
			case -1: // Token is a number
				treeStack.push(new ValueNode(std::strtod(queue.front().ptr, &ptr_end))); // Parse and push to stack
				break;
			/* Token is a constant */
			case -3:
				treeStack.push(new E_Node());
				break;
			case -4:
				treeStack.push(new PI_Node());
				break;
			case -5:
				treeStack.push(new EPSILON_NAUGHT_Node());
				break;
			case -6:
				treeStack.push(new COULOUMB_CONSTANT_Node());
				break;
			case -7:
				treeStack.push(new PROTON_MASS_Node());
				break;
			case -8:
				treeStack.push(new NEUTRON_MASS_Node());
				break;
			case -9:
				treeStack.push(new ELECTRON_MASS_Node());
				break;
			case -10:
				treeStack.push(new ELECTRON_CHARGE_NODE());
				break;
			case -11:
				treeStack.push(new LIGHT_SPEED_Node());
				break;
			case -12:
				treeStack.push(new GRAVITATIONAL_CONSTANT_Node());
				break;
			case -13:
				treeStack.push(new GRAVITY_Node());
				break;
			case -14:
				treeStack.push(new MU_NAUGHT_Node());
				break;
			default: // Token is a variable
				treeStack.push(new VariableNode(std::string(queue.front().ptr, queue.front().size)));
				break;
			}
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
				case 21:
					treeStack.push(new RoundNode(inner));
					break;
				case 22:
					treeStack.push(new CeilingNode(inner));
					break;
				case 23:
					treeStack.push(new FloorNode(inner));
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
				case 7:
					treeStack.push(new FloorDivideNode(lhs, rhs));
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
				case 34:
					treeStack.push(new LCM_Node(lhs, rhs));
					break;
				case 35:
					treeStack.push(new GCD_Node(lhs, rhs));
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