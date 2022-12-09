#include <stdexcept>
#include "MaterialManager.h"

MaterialManager::MaterialManager() : _materials() {
	createMaterial("None");
}

MaterialManager::MaterialManager(const MaterialManager& rhs) : _materials() { }
MaterialManager::~MaterialManager() { }
MaterialManager& MaterialManager::operator=(const MaterialManager& rhs) { return *this;  }

Material* MaterialManager::createMaterial(const std::string& name) {
	Material* newMat = new Material(name);
	_materials.insert({ name, newMat });
	return newMat;
}
Material* MaterialManager::getMaterial(const std::string& name) {
	try {
		return _materials.at(name);
	}
	catch (const std::out_of_range&) {
		return createMaterial(name);
	}
}
void MaterialManager::destroyMaterial(const std::string& name) {
	delete getMaterial(name);
	_materials.erase(name);
}
void MaterialManager::destroyMaterial(Material* material) {
	_materials.erase(material->name);
	delete material;
}