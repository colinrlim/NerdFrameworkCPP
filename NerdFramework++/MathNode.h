#pragma once

#include <functional>
#include <numeric>
#include <string>
#include <cmath>
#include "VariableManager.h"

#undef min
#undef max

struct MathNode {
	struct Term {
		std::map<std::string, double> variables;
		double coefficient;

		Term(std::map<std::string, double> variables, double coefficient = 1.0) :
			variables(variables),
			coefficient(coefficient)
		{ }

		static bool areLikeTerms(Term lhs, Term rhs) {
			if (lhs.variables.size() != rhs.variables.size())
				return false;
			for (const auto& element : lhs.variables) {
				if (rhs.variables[element.first] != element.second)
					return false;
			}
			return true;
		}
	};

	virtual ~MathNode() { };

	virtual double getValue() { return 0.0; }
	virtual std::vector<Term> getExpanded() { return { }; }
	virtual char* toLaTeX() { return nullptr; }

	virtual void traverse(std::function<void(MathNode*)> func) { }
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
	~ContainerNode() {
		delete inner;
	}

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
	~OperatorNode() {
		delete lhs;
		delete rhs;
	}

	void traverse(std::function<void(MathNode*)> func) {
		lhs->traverse(func);
		rhs->traverse(func);
		func(this);
	}
};

struct ValueNode : EndNode {
	double value;

	ValueNode(double value) : value(value) { }

	double getValue() {
		return value;
	}
	std::vector<Term> getExpanded() {
		return { Term({ }, value) };
	}
};
struct VariableNode : EndNode {
	std::string name;

	VariableNode(std::string name) : name(name) { }

	double getValue() {
		return 0;// VariableManager::getInstance().getVariable(name);
	}
	std::vector<Term> getExpanded() {
		return { Term({ {name, 1.0} }, 1.0) };
	}
	void appendUnknowns(std::vector<std::string>& unknowns) { }
};
struct EqualsNode : OperatorNode {
	using OperatorNode::OperatorNode;

	double getValue() {
		return std::abs(rhs->getValue() - lhs->getValue()) < 0.000001;
	}
};
struct GroupNode : ContainerNode {
	using ContainerNode::ContainerNode;

	double getValue() {
		return inner->getValue();
	}
};
struct AddNode : OperatorNode {
	using OperatorNode::OperatorNode;

	double getValue() {
		return lhs->getValue() + rhs->getValue();
	}
};
struct SubtractNode : OperatorNode {
	using OperatorNode::OperatorNode;
	
	double getValue() {
		return lhs->getValue() - rhs->getValue();
	}
};
struct MultiplyNode : OperatorNode {
	using OperatorNode::OperatorNode;

	double getValue() {
		return lhs->getValue() * rhs->getValue();
	}
};
struct DivideNode : OperatorNode {
	using OperatorNode::OperatorNode;

	double getValue() {
		return lhs->getValue() / rhs->getValue();
	}
};
struct FloorDivideNode : OperatorNode {
	using OperatorNode::OperatorNode;

	double getValue() {
		return floor(lhs->getValue() / rhs->getValue());
	}
};
struct ModuloNode : OperatorNode {
	using OperatorNode::OperatorNode;

	double getValue() {
		return std::fmod(lhs->getValue(), rhs->getValue());
	}
};
struct ExponentNode : OperatorNode {
	using OperatorNode::OperatorNode;

	double getValue() {
		return std::pow(lhs->getValue(), rhs->getValue());
	}
};
struct SquareRootNode : ContainerNode {
	using ContainerNode::ContainerNode;

	double getValue() {
		return std::sqrt(inner->getValue());
	}
};
struct FactorialNode : ContainerNode {
	using ContainerNode::ContainerNode;

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
		return 8.854187817e-12;
	}
};
struct COULOUMB_CONSTANT_Node : EndNode {
	double getValue() {
		return 8987551788;
	}
};
struct PROTON_MASS_Node : EndNode {
	double getValue() {
		return 1.67262192e-27;
	}
};
struct NEUTRON_MASS_Node : EndNode {
	double getValue() {
		return 1.67262192e-27;
	}
};
struct ELECTRON_MASS_Node : EndNode {
	double getValue() {
		return 9.1093837e-31;
	}
};
struct ELECTRON_CHARGE_NODE : EndNode {
	double getValue() {
		return 1.60217663e-19;
	}
};
struct LIGHT_SPEED_Node : EndNode {
	double getValue() {
		return 299792458;
	}
};
struct GRAVITATIONAL_CONSTANT_Node : EndNode {
	double getValue() {
		return 6.67428e-11;
	}
};
struct GRAVITY_Node : EndNode {
	double getValue() {
		return 9.80665;
	}
};
struct MU_NAUGHT_Node : EndNode {
	double getValue() {
		return 1.25663706e-6;
	}
};


struct SineNode : ContainerNode {
	using ContainerNode::ContainerNode;

	double getValue() {
		double result = std::sin(inner->getValue());
		return std::abs(result) < 0.000000001 ? 0 : result;
	}
};
struct CosineNode : ContainerNode {
	using ContainerNode::ContainerNode;

	double getValue() {
		double result = std::cos(inner->getValue());
		return std::abs(result) < 0.000000001 ? 0 : result;
	}
};
struct TangentNode : ContainerNode {
	using ContainerNode::ContainerNode;

	double getValue() {
		double result = std::tan(inner->getValue());
		return std::abs(result) < 0.000000001 ? 0 : result;
	}
};
struct ArcSineNode : ContainerNode {
	using ContainerNode::ContainerNode;

	double getValue() {
		return std::asin(inner->getValue());
	}
};
struct ArcCosineNode : ContainerNode {
	using ContainerNode::ContainerNode;

	double getValue() {
		return std::acos(inner->getValue());
	}
};
struct ArcTangentNode : ContainerNode {
	using ContainerNode::ContainerNode;

	double getValue() {
		return std::atan(inner->getValue());
	}
};
struct CosecantNode : ContainerNode {
	using ContainerNode::ContainerNode;

	double getValue() {
		return 1 / std::sin(inner->getValue());
	}
};
struct SecantNode : ContainerNode {
	using ContainerNode::ContainerNode;

	double getValue() {
		return 1 / std::cos(inner->getValue());
	}
};
struct CotangentNode : ContainerNode {
	using ContainerNode::ContainerNode;

	double getValue() {
		return 1 / std::tan(inner->getValue());
	}
};

struct LogNode : ContainerNode {
	using ContainerNode::ContainerNode;

	double getValue() {
		return std::log10(inner->getValue());
	}
};
struct LnNode : ContainerNode {
	using ContainerNode::ContainerNode;

	double getValue() {
		return std::log(inner->getValue());
	}
};

struct MaxNode : OperatorNode {
	using OperatorNode::OperatorNode;

	double getValue() {
		return std::max(lhs->getValue(), rhs->getValue());
	}
};
struct MinNode : OperatorNode {
	using OperatorNode::OperatorNode;

	double getValue() {
		return std::min(lhs->getValue(), rhs->getValue());
	}
};
struct ModulusNode : ContainerNode {
	using ContainerNode::ContainerNode;

	double getValue() {
		return std::abs(inner->getValue());
	}
};

struct RoundNode : ContainerNode {
	using ContainerNode::ContainerNode;

	double getValue() {
		return std::round(inner->getValue());
	}
};
struct CeilingNode : ContainerNode {
	using ContainerNode::ContainerNode;

	double getValue() {
		return std::ceil(inner->getValue());
	}
};
struct FloorNode : ContainerNode {
	using ContainerNode::ContainerNode;

	double getValue() {
		return std::floor(inner->getValue());
	}
};

struct LCM_Node : OperatorNode {
	using OperatorNode::OperatorNode;

	double getValue() {
		return std::lcm((int)std::round(lhs->getValue()), (int)std::round(rhs->getValue()));
	}
};
struct GCD_Node : OperatorNode {
	using OperatorNode::OperatorNode;

	double getValue() {
		return std::gcd((int)std::round(lhs->getValue()), (int)std::round(rhs->getValue()));
	}
};

/* To add:
* dnorm()
* pnorm()
* qnorm()
* 
* dchisq()
* pchisq()
* qchisq()
* 
* dt()
* pt()
* qt()
* 
* df()
* pf()
* qf()
* 
* rand()
* randInt()
* randNorm()
* randBin()
*/