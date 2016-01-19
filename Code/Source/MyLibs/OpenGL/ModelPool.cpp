#include "ModelPool.h"

ModelPool::ModelPool()
{

}

ModelPool::~ModelPool()
{

}

//get a model from the pool if there is one and copies it into the passed in model
bool ModelPool::GetModel(std::string name, std::vector<std::pair<Mesh, Material>>*& model)
{
	bool result = (m_ModelMap.find(name) != m_ModelMap.end());
	model = &m_ModelMap[name];
	return result;
}