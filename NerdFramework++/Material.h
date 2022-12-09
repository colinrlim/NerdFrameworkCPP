#pragma once

#include <string>
#include "Image4.h"

struct Material
{
	enum class IlluminationModel { FLAT, SPECULAR };

	Vector3 ambientColor;
	Vector3 diffuseColor;
	Vector3 specularColor;

	IlluminationModel illuminationModel;

	double shininess;
	double alpha;

	Image4 texture;

private:
	std::string name;

	Material(const std::string& name);

	friend class MaterialManager;
};

