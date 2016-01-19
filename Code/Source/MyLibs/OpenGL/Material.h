#ifndef __MATERIAL_H
#define __MATERIAL_H

#include "Texture.h"
#include "ShaderProgram.h"

//this is data for materials
struct MaterialData
{
	MaterialData(const char* ambientUp, const char* ambientLow, const char* diffuse, const char* specular, const char* illum, const char* tex, unsigned int unit = 0);

	const char* ambientUpper;
    const char* ambientLower;
	const char* diffuse;
	const char* specular;
	const char* illumination;
	const char* texture;
	unsigned int unit;
};

//this class will hold data such as textures and lighting values
struct Material
{
public:
	Material();

	Material(Material&& m);
	Material(Material&) = delete;
	Material& operator=(Material&) = delete;
	Material& operator=(Material&&);

	virtual ~Material();

	//set the material to active
	void SetMaterial(ShaderProgram* program, MaterialData data);

	float ambientLower[3];
	float diffuse[3];
	float specular[3];
    float ambientUpper[3];
	float illumination;
	Texture* texture;
private:

};

#endif //__MATERIAL_H