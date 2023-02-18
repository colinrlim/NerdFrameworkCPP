#include <stack>
#include <queue>
#include "MathParser.h"
#include "MathNode.h"
#include <iostream>

MathParser::Item MathParser::getNextOperator(const char* string, size_t size) {
	switch (string[0]) {
	case '(':
	case ')':
		return Item(string, 1, 1, 0);
	case '+':
		return Item(string, 2, 1, 1);
	case '-':
		return Item(string, 2, 1, 2);
	case '*':
		return Item(string, 3, 1, 3);
	case '/':
		return Item(string, 3, 1, 4);
	case '%':
		return Item(string, 3, 1, 5);
	case '^':
		return Item(string, 4, 1, 6);
	case '=':
		return Item(string, 99, 1, 7);
	}
	if (size >= 6) {
		if (string[0] == 'a' && string[1] == 'r' && string[2] == 'c') {
			if (string[3] == 's' && string[4] == 'i' && string[5] == 'n')
				return Item(string, 90, 6, 8);
			else if (string[3] == 'c' && string[4] == 'o' && string[5] == 's')
				return Item(string, 90, 6, 9);
			else if (string[3] == 't' && string[4] == 'a' && string[5] == 'n')
				return Item(string, 90, 6, 10);
		}
	}
	if (size >= 4) {
		if (string[0] == 'a') {
			if (string[1] == 's' && string[2] == 'i' && string[3] == 'n')
				return Item(string, 90, 4, 8);
			else if (string[1] == 'c' && string[2] == 'o' && string[3] == 's')
				return Item(string, 90, 4, 9);
			else if (string[1] == 't' && string[2] == 'a' && string[3] == 'n')
				return Item(string, 90, 4, 10);
		}
	}
	if (size >= 3) {
		if (string[0] == 's' && string[1] == 'i' && string[2] == 'n')
			return Item(string, 90, 3, 11);
		else if (string[0] == 'c' && string[1] == 'o' && string[2] == 's')
			return Item(string, 90, 3, 12);
		else if (string[0] == 't' && string[1] == 'a' && string[2] == 'n')
			return Item(string, 90, 3, 13);
		else if (string[0] == 'c' && string[1] == 's' && string[2] == 'c')
			return Item(string, 90, 3, 14);
		else if (string[0] == 's' && string[1] == 'e' && string[2] == 'c')
			return Item(string, 90, 3, 15);
		else if (string[0] == 'c' && string[1] == 'o' && string[2] == 't')
			return Item(string, 90, 3, 16);
		else if (string[0] == 'l' && string[1] == 'o' && string[2] == 'g')
			return Item(string, 90, 3, 17);
	}
	if (size >= 2) {
		if (string[0] == 'l' && string[1] == 'n')
			return Item(string, 90, 2, 18);
	}
	size_t i = 0;
	while (i != size && ((string[i] >= '0' && string[i] <= '9') || string[i] == '.')) {
		i++;
	}
	return i == 0 ? Item(string, -1, 1, -2) : Item(string, -1, i, -1);
}

MathNode* MathParser::toExpressionTree(const char* string, size_t size) {
	std::stack<Item> stack;
	std::queue<Item> queue;

	size_t i = 0;
	while (i != size) {
		Item op = getNextOperator(string + i, size - i);
		if (op.ptr[0] == '(') {
			stack.push(op);
			i += 1;
			continue;
		}
		if (op.precedence > 0) {
			if (!stack.empty()) {
				if (op.ptr[0] == ')') {
					while (!stack.empty()) {
						if (stack.top().ptr[0] == '(') {
							stack.pop();
							break;
						} else {
							queue.push(stack.top());
							stack.pop();
						}
					}
				} else if (stack.top().precedence >= op.precedence && (stack.top().ptr[0] != '^' || op.ptr[0] != '^')) {
					queue.push(stack.top());
					stack.pop();
				}
			}
			if (op.ptr[0] != ')')
				stack.push(op);
		} else {
			queue.push(op);
		}
		i += op.size;
	}

	while (!stack.empty()) {
		queue.push(stack.top());
		stack.pop();
	}

	std::string result;
	result.reserve(size);

	std::queue<Item> queueCopy(queue);
	while (!queueCopy.empty()) {
		result.append(queueCopy.front().ptr, queueCopy.front().size);
		queueCopy.pop();
	}

	std::cout << std::endl << result << std::endl;

	std::stack<MathNode*> treeStack;

	while (!queue.empty()) {
		char* ptr_end = (char*)queue.front().ptr + queue.front().size - 1;
		if (queue.front().precedence < 0) {
			if (queue.front().precedence == -1)
				treeStack.push(new ValueNode(std::strtod(queue.front().ptr, &ptr_end)));
			else if (queue.front().ptr[0] == 'e')
				treeStack.push(new E_Node());
			else
				treeStack.push(new VariableNode(std::string(queue.front().ptr, queue.front().size)));
		} else {
			if (queue.front().precedence == 90) {
				if (treeStack.empty())
					return nullptr;
				MathNode* inner = treeStack.top();
				treeStack.pop();
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
				}
			} else {
				if (treeStack.size() < 2)
					return nullptr;
				MathNode* rhs = treeStack.top();
				treeStack.pop();
				MathNode* lhs = treeStack.top();
				treeStack.pop();
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
					treeStack.push(new ModulusNode(lhs, rhs));
					break;
				case 6:
					treeStack.push(new ExponentNode(lhs, rhs));
					break;
				case 7:
					treeStack.push(new EqualsNode(lhs, rhs));
					break;
				}
			}
		}
		queue.pop();
	}

	return treeStack.top();
}