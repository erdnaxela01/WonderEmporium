#include "Model.h"

Model::Model()
{

}

Model::~Model()
{

}

//void Model::AddPiece(Mesh& mes, Material& mat)
//{
//	//add pieces to the model
//	m_Pieces.push_back(std::make_pair(std::move(mes), std::move(mat)));
//}

void Model::Render(ShaderProgram* program, MaterialData dat)
{
	//render all the pieces of the model
	int loc = glGetUniformLocation(program->GetProgram(), "u_BaseScale");
	glUniform3f(loc, m_Scale[0], m_Scale[1], m_Scale[2]);
	if (m_Pieces != nullptr)
	{
		for (unsigned int i = 0; i < m_Pieces->size(); i++)
		{
			(*m_Pieces)[i].second.SetMaterial(program, dat);
			(*m_Pieces)[i].first.DrawMesh(program);
            CheckForGLErrors();

		}
	}
}

//std::pair<Mesh, Material>& Model::BackPiece()
//{
//	return m_Pieces.back();
//}

unsigned int Model::NumberOfPieces()
{
	return m_Pieces->size();
}