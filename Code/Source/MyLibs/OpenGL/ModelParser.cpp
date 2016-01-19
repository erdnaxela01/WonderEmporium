#include "ModelParser.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Texture.h"

using namespace std;

ifstream Parser::s_File;
ModelPool Parser::s_Pool;

Paths::Paths(const char* tex, const char* model, const char* file) : texturePath(tex), modelPath(model), fileName(file)
{

}

Attributes::Attributes(const char* pos, const char* norm, const char* tex) : position(pos), normal(norm), texCoord(tex)
{

}

void Parser::Parse(Paths paths, Attributes attrib, Model* model , float width, float height, float depth)
{
    //close the file and open a new one
    if (s_File.is_open())
    {
        s_File.close();
    }
	s_File.open((std::string(paths.modelPath) + paths.fileName));

    //create a vector with data
    std::vector<ParseData> vertices[3];

	Mesh mesh;

	std::string materialName;
	Material material;
    unsigned int count[3] = { 0 };

	std::vector<ParseData> data2;

    std::string line;

	std::vector<std::pair<Mesh, Material>>* modelData;
	if (s_Pool.GetModel(paths.fileName, modelData))
	{
		model->m_Pieces = modelData;
		model->m_Scale[0] = width;
		model->m_Scale[1] = height;
		model->m_Scale[2] = depth;
		return;
	}

    //get a line
    while (getline(s_File, line))
    {

        //if its any of the parses the set their values
        if (line.find("v ") != line.npos)
        {
            AddPosition(&vertices[0], line, &count[0]);
        }
        else if (line.find("vn ") != line.npos)
        {
            AddNormal(&vertices[1], line, &count[1]);
        }
        else if (line.find("vt ") != line.npos)
        {
            AddTextureCoord(&vertices[2], line, &count[2]);
        }
        else if (line.find("f ") != line.npos)
        {
			SetVertices(vertices, &data2, line);
        }
		else if (line.find("mtllib ") != line.npos)
		{
			
			materialName = line.substr(7, line.length());
		}
		else if (line.find("usemtl ") != line.npos)
		{
			if (!modelData->empty())
			{
				modelData->back().first.Create(data2.data(), sizeof(ParseData) * data2.size(), data2.size(),
				{
					Mesh::AttributeData(attrib.position, 3, sizeof(ParseData), 0),
					Mesh::AttributeData(attrib.normal, 3, sizeof(ParseData), sizeof(float) * 3),
					Mesh::AttributeData(attrib.texCoord, 2, sizeof(ParseData), sizeof(float) * 6)
				});
				modelData->back().second = std::move(material);
				
			}
			data2.clear();
			modelData->push_back(std::make_pair(std::move(mesh), std::move(material)));
			SetMaterial(&material, line, paths.modelPath, materialName.c_str(), paths.texturePath);
		}
    }
	if (!modelData->empty())
    {
		modelData->back().first.Create(data2.data(), sizeof(ParseData) * data2.size(), data2.size(),
        {
            Mesh::AttributeData(attrib.position, 3, sizeof(ParseData), 0),
            Mesh::AttributeData(attrib.normal, 3, sizeof(ParseData), sizeof(float) * 3),
            Mesh::AttributeData(attrib.texCoord, 2, sizeof(ParseData), sizeof(float) * 6)
        });
		modelData->back().second = std::move(material);
    }

	model->m_Pieces = modelData;
	model->m_Scale[0] = width;
	model->m_Scale[1] = height;
	model->m_Scale[2] = depth;
	return;


}
void Parser::AddPosition(std::vector<ParseData>* vertices, string& line, unsigned int* count)
{
    //set the value
	vertices->emplace_back();
    sscanf_s(line.c_str(), "v %f%f%f\n", &(*vertices)[*count].x, &(*vertices)[*count].y, &(*vertices)[*count].z);
    ++*count;
}

void Parser::AddNormal(std::vector<ParseData>* vertices, string& line, unsigned int* count)
{
    //set the value
	vertices->emplace_back();
    sscanf_s(line.c_str(), "vn %f %f %f\n", &(*vertices)[*count].nX, &(*vertices)[*count].nY, &(*vertices)[*count].nZ);
    ++*count;
}
void Parser::AddTextureCoord(std::vector<ParseData>* vertices, string& line, unsigned int* count)
{
    //set the value

	vertices->emplace_back();
    sscanf_s(line.c_str(), "vt %f %f\n", &(*vertices)[*count].tX, &(*vertices)[*count].tY);
    ++*count;
}

void Parser::SetVertices(std::vector<ParseData>* vertices, std::vector<ParseData>* allVertices, string& line)
{
    unsigned int pos[3];
    unsigned int norm[3];
    unsigned int tex[3];

	sscanf_s(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d\n", &pos[0], &tex[0], &norm[0], &pos[1], &tex[1], &norm[1], &pos[2], &tex[2], &norm[2]);

    //set all the vertices
    for (int i = 0; i < 3; i++)
    {


        //push the vertices
        allVertices->push_back(
		{ vertices[0][pos[i] - 1].x, vertices[0][pos[i] - 1].y, vertices[0][pos[i] - 1].z,
        vertices[1][norm[i] - 1].nX, vertices[1][norm[i] - 1].nY, vertices[1][norm[i] - 1].nZ,
        vertices[2][tex[i] - 1].tX, vertices[2][tex[i] - 1].tY
        });
    }


}

void Parser::SetMaterial(Material* mat, std::string& line, const char* path, const char* name, const char* texPath)
{
	std::string materialName;
	materialName = line.substr(7, line.length());
	std::ifstream material(std::string(path) + name);

	std::string line2;
	while (getline(material, line2))
	{
		if (line2.find(std::string("newmtl ") + materialName) != line2.npos)
		{
			
			for (int i = 0; i < 7; i++)
			{
				getline(material, line2);
				if (line2.find("Kau") != line2.npos)
				{
                    sscanf_s(line2.c_str(), "Kau %f %f %f", &mat->ambientUpper[0], &mat->ambientUpper[1], &mat->ambientUpper[2]);
				}
                else if (line2.find("Kal") != line2.npos)
                {
                    sscanf_s(line2.c_str(), "Kal %f %f %f", &mat->ambientLower[0], &mat->ambientLower[1], &mat->ambientLower[2]);
                }
				else if (line2.find("Kd") != line2.npos)
				{
					sscanf_s(line2.c_str(), "Kd %f %f %f", &mat->diffuse[0], &mat->diffuse[1], &mat->diffuse[2]);
				}
				else if (line2.find("Ks") != line2.npos)
				{
					sscanf_s(line2.c_str(), "Ks %f %f %f", &mat->specular[0], &mat->specular[1], &mat->specular[2]);
				}
				else if (line2.find("illum") != line2.npos)
				{
					sscanf_s(line2.c_str(), "illum %f", &mat->illumination);
				}
				else if (line2.find("map") != line2.npos)
				{
					std::string texName;
					texName = line2.substr(4, line2.length());
					mat->texture = New Texture((std::string(texPath) + texName).c_str());
				}
			}
		}
	}
	
}