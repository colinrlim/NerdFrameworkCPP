#include "Material.h"

Material::Material(const std::string& name) :
	name(name),

	ambientColor(Vector3::one),
	diffuseColor(Vector3::one),
	specularColor(Vector3::one),

	illuminationModel(Material::IlluminationModel::FLAT), 

	shininess(0.0),
	alpha(1.0),
	texture(Image4::none)
{}