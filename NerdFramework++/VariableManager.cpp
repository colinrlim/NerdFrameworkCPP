#include "VariableManager.h"

double& VariableManager::getVariable(const std::string& name) {
	return _variables[name];
}
void VariableManager::setVariable(const std::string& name, double value) {
	_variables[name] = value;
}
bool VariableManager::exists(const std::string& name) {
	return _variables.find(name) != _variables.end();
}