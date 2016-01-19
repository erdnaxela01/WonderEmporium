#ifndef __MODEL_H
#define __MODEL_H

#include "Mesh.h"
#include "Material.h"

#include <vector>

//this is a container class for pieces of a model, it will hold
//meshes and materials
class Model
{
public:
	Model();

	virtual ~Model();


	unsigned int NumberOfPieces();

	void Render(ShaderProgram* program, MaterialData data);

	float m_Scale[3];
	std::vector<std::pair<Mesh, Material>>* m_Pieces;
private:



    



};

#endif //__MODEL_H