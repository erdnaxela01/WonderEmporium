#include "Material.h"

MaterialData::MaterialData(const char* ambU, const char* ambL, const char* diff, const char* spec, const char* ill, const char* tex, unsigned int un) :
diffuse(diff), specular(spec), illumination(ill), texture(tex), unit(un), ambientUpper(ambU), ambientLower(ambL)
{

}

Material::Material() :texture(nullptr)
{

}

Material::~Material()
{
	
    SafeDelete(texture);
	
}

Material& Material::operator=(Material&&m)
{
	texture = m.texture;
	m.texture = nullptr;

	for (int i = 0; i < 3; i++)
	{
        ambientUpper[i] = m.ambientUpper[i];
        ambientLower[i] = m.ambientLower[i];
		diffuse[i] = m.diffuse[i];
		specular[i] = m.specular[i];
	}
	illumination = m.illumination;
	return*this;
}

Material::Material(Material&& m)
{
	texture = m.texture;
	m.texture = nullptr;

	for (int i = 0; i < 3; i++)
	{
        ambientUpper[i] = m.ambientUpper[i];
        ambientLower[i] = m.ambientLower[i];
		specular[i] = m.specular[i];
	}
	illumination = m.illumination;

}

//set the material to active
void Material::SetMaterial(ShaderProgram* program, MaterialData dat)
{
	//set all the materials
	int loc = glGetUniformLocation(program->GetProgram(), dat.ambientUpper);
	if (loc != -1)
	{
        glUniform3f(loc, ambientUpper[0], ambientUpper[1], ambientUpper[2]);
	}
    loc = glGetUniformLocation(program->GetProgram(), dat.ambientLower);
    if (loc != -1)
    {
        glUniform3f(loc, ambientLower[0], ambientLower[1], ambientLower[2]);
    }
	loc = glGetUniformLocation(program->GetProgram(), dat.diffuse);
	if (loc != -1)
	{
		glUniform3f(loc, diffuse[0], diffuse[1], diffuse[2]);
	}
	loc = glGetUniformLocation(program->GetProgram(), dat.specular);
	if (loc != -1)
	{
		glUniform3f(loc, specular[0], specular[1], specular[2]);
	}
	loc = glGetUniformLocation(program->GetProgram(), dat.illumination);
	if (loc != -1)
	{
		glUniform1f(loc, illumination);
	}

	//use a texture if it isnt null
	if (texture != nullptr)
	{
		texture->UseTexture(program, dat.texture, dat.unit);
	}
}