#pragma once

#include <functional>
#include <cmath>
#include "VariableManager.h"

struct MathNode {
	virtual double getValue() = 0;
	virtual char* toLaTeX() = 0;

	virtual void traverse(std::function<void(MathNode*)> func) = 0;
};

struct EndNode : MathNode {
	EndNode() = default;

	void traverse(std::function<void(MathNode*)> func) {
		func(this);
	}
};
struct ContainerNode : MathNode {
	MathNode* inner;

	ContainerNode(MathNode* inner) : inner(inner) { }

	void traverse(std::function<void(MathNode*)> func) {
		inner->traverse(func);
		func(this);
	}
};
struct OperatorNode : MathNode {
	MathNode* lhs;
	MathNode* rhs;

	OperatorNode(MathNode* lhs, MathNode* rhs) :
		lhs(lhs),
		rhs(rhs)
	{ }

	void traverse(std::function<void(MathNode*)> func) {
		lhs->traverse(func);
		rhs->traverse(func);
		func(this);
	}
};

struct UnparsedNode : EndNode {
	char* value;
};
struct ValueNode : EndNode {
	double value;

	double getValue() {
		return value;
	}
};
struct VariableNode : EndNode {
	char* name;

	double getValue() {
		return VariableManager::getInstance().getVariable(name);
	}
	void appendUnknowns(std::vector<std::string>& unknowns) { }
};
struct EqualsNode : OperatorNode {

};
struct GroupNode : ContainerNode {
	double getValue() {
		return inner->getValue();
	}
};
struct AddNode : OperatorNode {
	double getValue() {
		return lhs->getValue() + rhs->getValue();
	}
};
struct SubtractNode : OperatorNode {
	double getValue() {
		return lhs->getValue() - rhs->getValue();
	}
};
struct MultiplyNode : OperatorNode {
	double getValue() {
		return lhs->getValue() * rhs->getValue();
	}
};
struct DivideNode : OperatorNode {
	double getValue() {
		return lhs->getValue() / rhs->getValue();
	}
};
struct ExponentNode : OperatorNode {
	double getValue() {
		return std::pow(lhs->getValue(), rhs->getValue());
	}
};
struct SquareRootNode : ContainerNode {
	double getValue() {
		return std::sqrt(inner->getValue());
	}
};
struct FactorialNode : ContainerNode {
	double getValue() {
		int n = (int)inner->getValue();
		int result = 1;
		for (int i = 2; i <= n; i++)
			result *= i;
		return result;
	}
};

struct E_Node : EndNode {
	double getValue() {
		return 2.71828182845904523536;
	}
};
struct PI_Node : EndNode {
	double getValue() {
		return 3.14159265358979323846;
	}
};
struct EPSILON_NAUGHT_Node : EndNode {
	double getValue() {
		return 0.000000000008854187817;
	}
};

struct SineNode : ContainerNode {
	double getValue() {
		return std::sin(inner->getValue());
	}
};
struct CosineNode : ContainerNode {
	double getValue() {
		return std::cos(inner->getValue());
	}
};
struct TangentNode : ContainerNode {
	double getValue() {
		return std::tan(inner->getValue());
	}
};
struct ArcSineNode : ContainerNode {
	double getValue() {
		return std::asin(inner->getValue());
	}
};
struct ArcCosineNode : ContainerNode {
	double getValue() {
		return std::acos(inner->getValue());
	}
};
struct ArcTangentNode : ContainerNode {
	double getValue() {
		return std::atan(inner->getValue());
	}
};
struct CosecantNode : ContainerNode {
	double getValue() {
		return 1 / std::sin(inner->getValue());
	}
};
struct SecantNode : ContainerNode {
	double getValue() {
		return 1 / std::cos(inner->getValue());
	}
};
struct CotangentNode : ContainerNode {
	double getValue() {
		return 1 / std::tan(inner->getValue());
	}
};
