#ifndef __MODEL_POOL_H
#define __MODEL_POOL_H

#include <map>
#include <string>

#include "Model.h"

//this will hold all the models based on their names and give the values a model might want to render if its already created
class ModelPool
{
public:
	ModelPool();

	virtual ~ModelPool();

	//get a model from the pool if there is one and copies it into the passed in model
	bool GetModel(std::string name, std::vector<std::pair<Mesh, Material>>*& model);
private:
	std::map<std::string, std::vector<std::pair<Mesh, Material>>> m_ModelMap;
};

#endif //__MODEL_POOL_H