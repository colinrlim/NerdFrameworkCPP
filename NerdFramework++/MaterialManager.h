#pragma once

#include <map>
#include "Material.h"

class MaterialManager
{
private:
	std::map<std::string, Material*> _materials;

	MaterialManager();

	MaterialManager(const MaterialManager& rhs);
	~MaterialManager();
	MaterialManager& operator=(const MaterialManager& rhs);
public:
	Material* createMaterial(const std::string& name);
	Material* getMaterial(const std::string& name);
	void destroyMaterial(const std::string& name);
	void destroyMaterial(Material* material);

	static MaterialManager& getInstance() {
		static MaterialManager mine;

		return mine;
	}
};

