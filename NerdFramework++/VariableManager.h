#pragma once

#include <string>
#include <map>

class VariableManager {
	std::map<std::string, double> _variables;
public:
	static VariableManager& getInstance() {
		static VariableManager mine;
		return mine;
	}

	double& getVariable(const std::string& name);
	void setVariable(const std::string& name, double value);
	bool exists(const std::string& name);
};